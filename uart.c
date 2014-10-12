#ifndef UART_C
#define UART_C

#include "uart.h"
AT91S_USART * pUSART = AT91C_BASE_US0;      /* Global Pointer to USART0 */


// *****************************************************************************
// usart0_isr.c

#include "board.h"

#define IRQ_MASK 0x00000080
#define FIQ_MASK 0x00000040
#define INT_MASK (IRQ_MASK | FIQ_MASK)

struct FIFO{
	char bffr[BUFFER_LENGTH]; // holds characters
	int nChars; // counts number of received chars
	char *wr_bffr;// = &bffr[0];  pointer into Buffer
	char *rd_bffr;//= &bffr[0]; // points to position which needs to be read
}rx;


void Usart0IrqHandler (void) {

	volatile AT91PS_USART pUsart0 = AT91C_BASE_US0; // create a pointer to USART0 structure
	// determine which interrupt has occurred
	// assume half-duplex operation here, only one interrupt type at a time
	if ((pUsart0->US_CSR & AT91C_US_RXRDY) == AT91C_US_RXRDY) {
		if (rx.nChars < BUFFER_LENGTH){
			// we have a receive interrupt,
			// remove it from Receiver Holding Register and place into buffer[]
			*rx.wr_bffr++ = pUsart0->US_RHR;
			rx.nChars++;
			// check if 10 characters have been received
			if(rx.wr_bffr > &rx.bffr[BUFFER_LENGTH]){
				rx.wr_bffr = &rx.bffr[0];
			}
		}
		else{
			//USART_puts("recieve Buffer is Full\n\r");
			//clear interupt anyway!
			pUsart0->US_RHR;
		}

	}
	/* else if ((pUsart0->US_CSR & AT91C_US_TXEMPTY) == AT91C_US_TXEMPTY) {
	//USART_puts("transmit interupt\r");
	// we have a transmit interrupt (previous char has clocked out)
	// check if 10 characters have been transmitted
	if (nChars >= BUFFER_LENGTH) {
	// yes, redirect buffer pointer to beginning
	pBuffer = &Buffer[0];
	nChars = 0;
	// enable receive interrupt, disable the transmit interrupt
	pUsart0->US_IER = AT91C_US_RXRDY; // enable RXRDY usart0 receive interrupt
	pUsart0->US_IDR = ~AT91C_US_RXRDY; // disable all interrupts except RXRDY
	}
	else {
	// no, send next character
	pUsart0->US_THR = *pBuffer++;
	nChars++;
	}
	}*/
}
// *******************************************************
// Function Prototypes
// *******************************************************
//void Usart0IrqHandler(void);
void USART0Setup(void) {
	// enable the usart0 peripheral clock
	volatile AT91PS_PMC pPMC = AT91C_BASE_PMC; // pointer to PMC data structure
	pPMC->PMC_PCER = (1<<AT91C_ID_US0); // enable usart0 peripheral clock
	// set up PIO to enable USART0 peripheral control of pins
	volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA; // pointer to PIO data structure
	pPIO->PIO_PDR = AT91C_PA5_RXD0 | AT91C_PA6_TXD0; // enable peripheral control of PA0,PA1 (RXD0 and TXD0)
	pPIO->PIO_ASR = AT91C_PIO_PA0 | AT91C_PIO_PA1; // assigns the 2 I/O lines to peripheral A function
	pPIO->PIO_BSR = 0; // peripheral B function set to "no effect"
	// set up the USART0 registers
	volatile AT91PS_USART pUSART0 = AT91C_BASE_US0; // create a pointer to USART0 structure
	pUSART0->US_CR = AT91C_US_RSTRX | // reset receiver
		AT91C_US_RSTTX | // reset transmitter
		AT91C_US_RXDIS | // disable receiver
		AT91C_US_TXDIS; // disable transmitter
	pUSART0->US_MR = AT91C_US_PAR_NONE | // no parity
		0x3 << 6; // 8-bit characters
	//
	pUSART0->US_IER = 0x00; // no usart0 interrupts enabled (no effect)
	//
	pUSART0->US_IDR = 0xFFFF; // disable all USART0 interrupts
	pUSART0->US_BRGR = 0x139; // CD = 0x139 (313 from above calculation) FP=0 (not used) -->9600 baud
	//
	pUSART0->US_RTOR = 0; // receiver time-out (disabled)
	pUSART0->US_TTGR = 0; // transmitter timeguard (disabled)
	//Set up the Advanced Interrupt Controller (AIC) registers for USART0
	volatile AT91PS_AIC pAIC = AT91C_BASE_AIC; // pointer to AIC data structure
	pAIC->AIC_IDCR = (1<<AT91C_ID_US0); // Disable USART0 interrupt in AIC
	pAIC->AIC_SVR[AT91C_ID_US0] = // Set the USART0 IRQ handler address in AIC Source
		(unsigned int)Usart0IrqHandler; // Vector Register[6]
	pAIC->AIC_SMR[AT91C_ID_US0] = // Set the interrupt source type(level-sensitive) and
		(/*AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL*/AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL  | 0x4 ); // priority (4) in AIC Source Mode Register[6] // AIC_SMR7 = 0xFFFFF01C
	pAIC->AIC_IECR = (1<<AT91C_ID_US0); // Enable the USART0 interrupt in AIC
	//enable the USART0 receiver and transmitter
	pUSART0->US_CR = AT91C_US_RXEN | AT91C_US_TXEN;
	// enable the USART0 receive interrupt
	pUSART0->US_IER = AT91C_US_RXRDY; // enable RXRDY usart0 receive interrupt
	pUSART0->US_IDR = ~AT91C_US_RXRDY; // disable all interrupts except RXRDY
	// set up buffer pointer and character counter
	struct FIFO rx;
	rx.wr_bffr = (char *)&rx.bffr;
	rx.rd_bffr = (char *)&rx.bffr;
	rx.nChars = 0;
	// enable IRQ interrupts
	enableIRQ();
	// at this point, only the USART0 receive interrupt is armed!
}


void USART_putchar(char c)
{
	static int first = 1;

	if(!first) while(!(pUSART->US_CSR & AT91C_US_TXRDY));
	pUSART->US_THR = c;
	first = 0;
}

char USART_getchar()
{
	if(rx.nChars == 0){
		return 0;
	}
	unsigned char ret_val = *rx.rd_bffr;
	rx.nChars--;
	rx.rd_bffr += sizeof(unsigned char);
	if(rx.rd_bffr > &rx.bffr[BUFFER_LENGTH]){
		rx.rd_bffr = &rx.bffr[0];
	}
	return ret_val;
}

int USART_RXavailable()
{
	return (pUSART->US_CSR & AT91C_US_RXRDY);
}

void USART_puts(char *s)
{
	while(*s != 0x00)
	{
		USART_putchar(*s);
		s++;
	}
}

static inline unsigned __get_cpsr(void)
{
	unsigned long retval;
	asm volatile (" mrs  %0, cpsr" : "=r" (retval) :   );
	return retval;
}

static inline void __set_cpsr(unsigned val)
{
	asm volatile (" msr  cpsr, %0" :  : "r" (val)  );
}

unsigned disableIRQ(void)
{
	unsigned _cpsr;

	_cpsr = __get_cpsr();
	__set_cpsr(_cpsr | IRQ_MASK);
	return _cpsr;
}

unsigned restoreIRQ(unsigned oldCPSR)
{
	unsigned _cpsr;

	_cpsr = __get_cpsr();
	__set_cpsr((_cpsr & ~IRQ_MASK) | (oldCPSR & IRQ_MASK));
	return _cpsr;
}

unsigned enableIRQ(void)
{
	unsigned _cpsr;

	_cpsr = __get_cpsr();
	__set_cpsr(_cpsr & ~IRQ_MASK);
	return _cpsr;
}

unsigned disableFIQ(void)
{
	unsigned _cpsr;

	_cpsr = __get_cpsr();
	__set_cpsr(_cpsr | FIQ_MASK);
	return _cpsr;
}

unsigned restoreFIQ(unsigned oldCPSR)
{
	unsigned _cpsr;

	_cpsr = __get_cpsr();
	__set_cpsr((_cpsr & ~FIQ_MASK) | (oldCPSR & FIQ_MASK));
	return _cpsr;
}

unsigned enableFIQ(void)
{
	unsigned _cpsr;

	_cpsr = __get_cpsr();
	__set_cpsr(_cpsr & ~FIQ_MASK);
	return _cpsr;
}


#endif // UART_C

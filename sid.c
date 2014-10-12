#include "sid.h"
#include "board.h"
#include "pio/pio.h"

static const Pin SID_D_OUT_PIN_7	= {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_D_OUT_PIN_6	= {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_D_OUT_PIN_5	= {1 << 30, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_D_OUT_PIN_4	= {1 << 28, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_D_OUT_PIN_3	= {1 << 4, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_D_OUT_PIN_2	= {1 << 6, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_D_OUT_PIN_1	= {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_D_OUT_PIN_0	= {1 << 10, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_D_IN_PIN_0		= {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_D_IN_PIN_1		= {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_D_IN_PIN_2		= {1 << 30, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_D_IN_PIN_3		= {1 << 28, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_D_IN_PIN_4		= {1 << 4, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_D_IN_PIN_5		= {1 << 6, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_D_IN_PIN_6		= {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_D_IN_PIN_7		= {1 << 10, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_APIN_4		= {1 << 12, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_APIN_3		= {1 << 25, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_APIN_2		= {1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_APIN_1		= {1 << 15, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_APIN_0		= {1 << 20, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_CS_PIN		= {1 << 22, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_RW_PIN		= {1 << 21, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
static const Pin SID_RESET_PIN		= {1 << 17, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};

static const Pin SID_READ_CLK   = {1 << 9, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT};
static const Pin SID_CLK_PIN = {1 << 11, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT};
//#define SID_CLK_PIN	AT91C_PA11_PWM0

/*    PWM Clock source Domain */
#define         MCKtoPWM      0
#define         MCK_2toPWM    1
#define         MCK_4toPWM    2
#define         MCK_8toPWM    3
#define         MCK_16toPWM   4
#define         MCK_32toPWM   5
#define         MCK_64toPWM   6
#define         MCK_128toPWM  7
#define         MCK_256toPWM  8
#define         MCK_512toPWM  9
#define         MCK_1024toPWM 10
#define         CLHAtoPWM     11
#define         CLHBtoPWM     12

#define         CALG_OFF       0
#define         CALG_ON       1<<8  // The period is center aligned (OFF, left aligned)
#define         CPOL_OFF      0<<0  // The ouput waveform starts at a high level (OFF, low level)
#define         CPOL_ON       1<<9  // The ouput waveform starts at a high level (OFF, low level)
#define         CPD_ON        1<<10 // The period will be modified at the next period start event
#define         CPD_OFF       0<<10

#define   PWM_PERIOD_VALUE            (MCK/(1*1000000))

void sid_clr_cs()
{
	PIO_Clear(&SID_CS_PIN);
}

void sid_set_cs()
{
	PIO_Set(&SID_CS_PIN);
}

void sid_set_read()
{
	PIO_Set(&SID_RW_PIN);
}

void sid_set_write()
{
	PIO_Clear(&SID_RW_PIN);
}

void sid_reset(void) {
	PIO_Clear(&SID_RESET_PIN);
	delay_ms(10);
	PIO_Set(&SID_RESET_PIN);
	delay_ms(50);
	return;
}

void sid_setaddr(unsigned char addr) {
	PIO_Clear(&SID_APIN_0);
	PIO_Clear(&SID_APIN_1);
	PIO_Clear(&SID_APIN_2);
	PIO_Clear(&SID_APIN_3);
	PIO_Clear(&SID_APIN_4);

	if(addr & 0x01) PIO_Set(&SID_APIN_0);
	if(addr & 0x02) PIO_Set(&SID_APIN_1);
	if(addr & 0x04) PIO_Set(&SID_APIN_2);
	if(addr & 0x08) PIO_Set(&SID_APIN_3);
	if(addr & 0x10) PIO_Set(&SID_APIN_4);
	return;
}

void sid_wait_for_low()
{
	while(PIO_Get(&SID_READ_CLK));
}

void sid_wait_for_high()
{
	while(!PIO_Get(&SID_READ_CLK));
}

unsigned char sid_read(unsigned char sid_register) {
	unsigned char sid_data;
	PIO_Configure(&SID_D_IN_PIN_0, 1);
	PIO_Configure(&SID_D_IN_PIN_1, 1);
	PIO_Configure(&SID_D_IN_PIN_2, 1);
	PIO_Configure(&SID_D_IN_PIN_3, 1);
	PIO_Configure(&SID_D_IN_PIN_4, 1);
	PIO_Configure(&SID_D_IN_PIN_5, 1);
	PIO_Configure(&SID_D_IN_PIN_6, 1);
	PIO_Configure(&SID_D_IN_PIN_7, 1);
	sid_setaddr(sid_register);
	sid_set_read();
	sid_clr_cs();
	sid_wait_for_high();
	char p0 = PIO_Get(&SID_D_IN_PIN_0);
	char p1 = PIO_Get(&SID_D_IN_PIN_1);
	char p2 = PIO_Get(&SID_D_IN_PIN_2);
	char p3 = PIO_Get(&SID_D_IN_PIN_3);
	char p4 = PIO_Get(&SID_D_IN_PIN_4);
	char p5 = PIO_Get(&SID_D_IN_PIN_5);
	char p6 = PIO_Get(&SID_D_IN_PIN_6);
	char p7 = PIO_Get(&SID_D_IN_PIN_7);
	sid_set_cs();
	PIO_Configure(&SID_D_OUT_PIN_0, 1);
	PIO_Configure(&SID_D_OUT_PIN_1, 1);
	PIO_Configure(&SID_D_OUT_PIN_2, 1);
	PIO_Configure(&SID_D_OUT_PIN_3, 1);
	PIO_Configure(&SID_D_OUT_PIN_4, 1);
	PIO_Configure(&SID_D_OUT_PIN_5, 1);
	PIO_Configure(&SID_D_OUT_PIN_6, 1);
	PIO_Configure(&SID_D_OUT_PIN_7, 1);
	sid_data = (p0<<0)|(p1<<1)|(p2<<2)|(p3<<3)|(p4<<4)|(p5<<5)|(p6<<6)|(p7<<7);
	return sid_data;
}

void sid_write(unsigned char sid_register, unsigned char sid_data)
{
	sid_setaddr(sid_register);
	sid_set_write();
	if(sid_data & 0x01)	 PIO_Set(&SID_D_OUT_PIN_0);
	else	PIO_Clear(&SID_D_OUT_PIN_0);
	if(sid_data & 0x02)	 PIO_Set(&SID_D_OUT_PIN_1);
	else	PIO_Clear(&SID_D_OUT_PIN_1);
	if(sid_data & 0x04)	 PIO_Set(&SID_D_OUT_PIN_2);
	else	PIO_Clear(&SID_D_OUT_PIN_2);
	if(sid_data & 0x08)	 PIO_Set(&SID_D_OUT_PIN_3);
	else	PIO_Clear(&SID_D_OUT_PIN_3);
	if(sid_data & 0x10)	 PIO_Set(&SID_D_OUT_PIN_4);
	else	PIO_Clear(&SID_D_OUT_PIN_4);
	if(sid_data & 0x20)	 PIO_Set(&SID_D_OUT_PIN_5);
	else	PIO_Clear(&SID_D_OUT_PIN_5);
	if(sid_data & 0x40)	 PIO_Set(&SID_D_OUT_PIN_6);
	else	PIO_Clear(&SID_D_OUT_PIN_6);
	if(sid_data & 0x80)	 PIO_Set(&SID_D_OUT_PIN_7);
	else PIO_Clear(&SID_D_OUT_PIN_7);
	sid_wait_for_high();
	sid_wait_for_low();
	asm("nop");
	asm("nop");
	asm("nop");
	sid_clr_cs();
	//	sid_wait_for_high();
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	//	sid_wait_for_low();
	sid_set_cs();
	return;
}

void sid_clear(void)
{
	for(int i = 0; i < 27; i++) sid_write(i, 0);
}

void play_song()
{
	int ptr = 0;
	while(song[ptr] != 99) {
		int length = song[ptr++];
		for(int i = 0; i < length; i++) {
			sid_write(song[ptr], song[ptr+1]);
			ptr += 2;
		}
		delay_ms(19);
	}
	sid_clear();
}

void sid_init()
{
	PIO_Configure(&SID_APIN_0, 1);
	PIO_Configure(&SID_APIN_1, 1);
	PIO_Configure(&SID_APIN_2, 1);
	PIO_Configure(&SID_APIN_3, 1);
	PIO_Configure(&SID_APIN_4, 1);
	PIO_Configure(&SID_D_OUT_PIN_0, 1);
	PIO_Configure(&SID_D_OUT_PIN_1, 1);
	PIO_Configure(&SID_D_OUT_PIN_2, 1);
	PIO_Configure(&SID_D_OUT_PIN_3, 1);
	PIO_Configure(&SID_D_OUT_PIN_4, 1);
	PIO_Configure(&SID_D_OUT_PIN_5, 1);
	PIO_Configure(&SID_D_OUT_PIN_6, 1);
	PIO_Configure(&SID_D_OUT_PIN_7, 1);
	PIO_Configure(&SID_READ_CLK, 1);
	PIO_Configure(&SID_RESET_PIN, 1);
	PIO_Configure(&SID_RW_PIN, 1);
	PIO_Configure(&SID_CS_PIN, 1);

	/* Valid the PWM's Clock at PMC level */
	AT91F_PMC_EnablePeriphClock(AT91C_BASE_PMC,1<<AT91C_ID_PWMC);

	/* Disable the PWM the channel 0 */
	AT91C_BASE_PWMC->PWMC_DIS = 0x1;

	/* Enabling a PWM output through the PA11: PWM Channel 0*/
	AT91F_PIO_CfgPeriph(AT91C_BASE_PIOA, 0, AT91C_PA11_PWM0);

	/* Period Updating */
	AT91C_BASE_PWMC_CH0->PWMC_CMR = (CPD_ON | CPOL_OFF | CALG_OFF | MCKtoPWM);
	AT91C_BASE_PWMC_CH0->PWMC_CPRDR=PWM_PERIOD_VALUE;

	/* Duty Cycle Updating */
	AT91C_BASE_PWMC_CH0->PWMC_CMR = (CPD_OFF | CPOL_OFF | CALG_OFF | MCKtoPWM);
	AT91C_BASE_PWMC_CH0->PWMC_CDTYR = 0x0FFF; //duty cycle 0xFFFF/2 => 50%

	/* Interrupt enabling at peripheral level only in order to have synchronisation between
	   Software and the UP-DATE Register (to avoid over writting) */
	AT91C_BASE_PWMC->PWMC_IER = 1;

	/* Enable the PWM the channel 0*/
	AT91C_BASE_PWMC->PWMC_ENA = 0x1;

	sid_set_cs();
	sid_reset();
	sid_clear();
}

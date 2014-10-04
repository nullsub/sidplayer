#ifndef UART_H
#define UART_H

#include "board.h"

#define BR      9600 //115200                       /* Baud Rate */

#define BRD  (MCK/16/BR)                    /* Baud Rate Divisor */

#define BUFFER_LENGTH 50 // recieve buffer lenght
// *******************************************************
// Global Variables
// *******************************************************
extern char Buffer[]; // holds received characters
extern unsigned long nChars; // counts number of received chars
extern char *pBuffer; // pointer into Buffer

void Usart0IrqHandler (void);
void USART0Setup(void);
void USART_putchar(char c);
char USART_getchar();
void USART_puts(char *s);

unsigned disableIRQ(void);
unsigned restoreIRQ(unsigned oldCPSR);
unsigned enableIRQ(void);
unsigned disableFIQ(void);
unsigned restoreFIQ(unsigned oldCPSR);
unsigned enableFIQ(void);

#endif // UART_H

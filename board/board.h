/*----------------------------------------------------------------------------
*         ATMEL Microcontroller Software Support  -  ROUSSET  -
*----------------------------------------------------------------------------
* The software is delivered "AS IS" without warranty or condition of any
* kind, either express, implied or statutory. This includes without
* limitation any warranty or condition with respect to merchantability or
* fitness for any particular purpose, or against the infringements of
* intellectual property rights of others.
*----------------------------------------------------------------------------
* File Name           : Board.h
* Object              : AT91SAM7S Evaluation Board Features Definition File.
*
* Creation            : JPP   16/Jun/2004
* V 1.0 21/Feb/05 JPP : Define __ramfunc
* V 1.1 21/Feb/05 JPP : add Lib definition
* V 1.2 22/Feb/05 JPP : Add DBGU inline definition
*----------------------------------------------------------------------------
*/
#ifndef Board_h
#define Board_h

#include "AT91SAM7S256.h"
//#define __inline extern inline
#include "lib_AT91SAM7S256.h"
//* inline definition

#define __ramfunc

#define AT91C_US_ASYNC_MODE ( AT91C_US_USMODE_NORMAL + AT91C_US_NBSTOP_1_BIT + AT91C_US_PAR_NONE + AT91C_US_CHRL_8_BITS + AT91C_US_CLKS_CLOCK )

#define true	-1
#define false	0

void delay_ms(int);
void delay_us(int);

/*-------------------------------*/
/* SAM7Board Memories Definition */
/*-------------------------------*/
// The AT91SAM7S64 embeds a 16-Kbyte SRAM bank, and 64 K-Byte Flash

#define  INT_SARM           0x00200000
#define  INT_SARM_REMAP	    0x00000000

#define  INT_FLASH          0x00000000
#define  INT_FLASH_REMAP    0x01000000

#define  FLASH_PAGE_NB	    512
#define  FLASH_PAGE_LOCK    32
#define  FLASH_PAGE_SIZE    128

/*-----------------*/
/* Leds Definition */
/*-----------------*/
/*
 *      PIO   Flash    PA    PB   PIN */
#if 0
#define LED1            (1<<0)	/* PA0 / PGMEN0 & PWM0 TIOA0  48 */
#define LED2            (1<<1)	/* PA1 / PGMEN1 & PWM1 TIOB0  47 */
#define LED3            0xFF//(1<<2)	/* PA2          & PWM2 SCK0   44 */
#define LED4            (1<<3)	/* PA3          & TWD  NPCS3  43 */
#define NB_LEB			4

#define LED_MASK        (LED1|LED2|LED3|LED4)
#endif
/*-------------------------*/
/* Push Buttons Definition */
/*-------------------------*/
/*                                 PIO    Flash    PA    PB   PIN */
#define SW1_MASK        (1<<19)	/* PA19 / PGMD7  & RK   FIQ     13 */
#define SW2_MASK        (1<<20)	/* PA20 / PGMD8  & RF   IRQ0    16 */
#define SW3_MASK        (1<<15)	/* PA15 / PGM3   & TF   TIOA1   20 */
#define SW4_MASK        (1<<14)	/* PA14 / PGMD2  & SPCK PWM3    21 */
#define SW_MASK         (SW1_MASK|SW2_MASK|SW3_MASK|SW4_MASK)


#define SW1 	(1<<19)	// PA19
#define SW2 	(1<<20)	// PA20
#define SW3 	(1<<15)	// PA15
#define SW4 	(1<<14)	// PA14

/*------------------*/
/* USART Definition */
/*------------------*/
/* SUB-D 9 points J3 DBGU*/
#define DBGU_RXD		AT91C_PA9_DRXD	  /* JP11 must be close */
#define DBGU_TXD		AT91C_PA10_DTXD	  /* JP12 must be close */
#define AT91C_DBGU_BAUD	   115200   // Baud rate

#define US_RXD_PIN		AT91C_PA5_RXD0    /* JP9 must be close */
#define US_TXD_PIN		AT91C_PA6_TXD0    /* JP7 must be close */
#define US_RTS_PIN		AT91C_PA7_RTS0    /* JP8 must be close */
#define US_CTS_PIN		AT91C_PA8_CTS0    /* JP6 must be close */

/*--------------*/
/* Master Clock */
/*--------------*/

#define EXT_OC          18432000   // Exetrnal ocilator MAINCK
#define MCK             47923200   // MCK (PLLRC div by 2)  47.9232 MHZ
#define MCKKHz          (MCK/1000) //

//------------------------------------------------------------------------------
//         Global Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Board
//------------------------------------------------------------------------------
/// String containing the name of the board.
#define BOARD_NAME      "AT91SAM7S-EK"
/// Board definition.
#define at91sam7sek
/// Family definition.
#define at91sam7s
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Clocks
//------------------------------------------------------------------------------
/// Frequency of the board main oscillator, in Hz.
#define BOARD_MAINOSC           18432000

/// Master clock frequency (when using board_lowlevel.c), in Hz.
#define BOARD_MCK               48000000
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// ADC
//------------------------------------------------------------------------------
/// ADC clock frequency, at 10-bit resolution (in Hz)
#define ADC_MAX_CK_10BIT         5000000
/// ADC clock frequency, at 8-bit resolution (in Hz)
#define ADC_MAX_CK_8BIT          8000000
/// Startup time max, return from Idle mode (in �s)
#define ADC_STARTUP_TIME_MAX       20
/// Track and hold Acquisition Time min (in ns)
#define ADC_TRACK_HOLD_TIME_MIN   600

//------------------------------------------------------------------------------
// USB
//------------------------------------------------------------------------------
/// Indicates the chip has a UDP controller.
#define BOARD_USB_UDP

/// Indicates the D+ pull-up is externally controlled.
#define BOARD_USB_PULLUP_EXTERNAL

/// Number of endpoints in the USB controller.
#define BOARD_USB_NUMENDPOINTS                  4

/// Returns the maximum packet size of the given endpoint.
/// \param i  Endpoint number.
/// \return Maximum packet size in bytes of endpoint.
#define BOARD_USB_ENDPOINTS_MAXPACKETSIZE(i)    ((i == 0) ? 8 : 64)

/// Returns the number of FIFO banks for the given endpoint.
/// \param i  Endpoint number.
/// \return Number of FIFO banks for the endpoint.
#define BOARD_USB_ENDPOINTS_BANKS(i)            (((i == 0) || (i == 3)) ? 1 : 2)

/// USB attributes configuration descriptor (bus or self powered, remote wakeup)
#define BOARD_USB_BMATTRIBUTES                  USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP
//#define BOARD_USB_BMATTRIBUTES                  USBConfigurationDescriptor_BUSPOWERED_NORWAKEUP
//#define BOARD_USB_BMATTRIBUTES                  USBConfigurationDescriptor_SELFPOWERED_RWAKEUP
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Pins
//------------------------------------------------------------------------------
/// DBGU pins definition. Contains DRXD (PA9) and DTXD (PA10).
#define PINS_DBGU  {0x00000600, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// LED #0 pin definition (PA0).
#define PIN_LED_DS1   {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #1 pin definition (PA1).
#define PIN_LED_DS2   {1 << 1, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #2 pin definition (PA2).
#define PIN_LED_DS3   {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// LED #3 pin definition (PA3).
#define PIN_LED_DS4   {1 << 3, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
/// List of the four LED pin definitions (PA0, PA1, PA2 & PA3)
#define PINS_LEDS   PIN_LED_DS1, PIN_LED_DS2, PIN_LED_DS3, PIN_LED_DS4

/// Push button #0 definition (PA19).
#define PIN_PUSHBUTTON_1    {1 << 19, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEGLITCH | PIO_PULLUP}
/// Push button #1 definition (PA20).
#define PIN_PUSHBUTTON_2    {1 << 20, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEGLITCH | PIO_PULLUP}
/// Push button #2 definition (PA15).
#define PIN_PUSHBUTTON_3    {1 << 15, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEGLITCH | PIO_PULLUP}
/// Push button #3 definition (PA14).
#define PIN_PUSHBUTTON_4    {1 << 14, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEGLITCH | PIO_PULLUP}
/// List of all push button definitions (PA19, PA20, PA15 & PA14).
#define PINS_PUSHBUTTONS    PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2, PIN_PUSHBUTTON_3, PIN_PUSHBUTTON_4
/// Push button #1 index.
#define PUSHBUTTON_BP1      0
/// Push button #2 index.
#define PUSHBUTTON_BP2      1
/// Push button #1 index.
#define PUSHBUTTON_BP3      2
/// Push button #2 index.
#define PUSHBUTTON_BP4      3
/// Simulated joystick LEFT index.
#define JOYSTICK_LEFT       0
/// Simulated joystick RIGHT index.
#define JOYSTICK_RIGHT      1

/// USART0 TXD pin definition (PA5).
#define PIN_USART0_RXD  {1 << 5, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 RXD pin definition (PA6).
#define PIN_USART0_TXD  {1 << 6, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 RTS pin definition.
#define PIN_USART0_RTS  {1 << 7, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 CTS pin definition.
#define PIN_USART0_CTS  {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// USART0 SCK pin definition.
#define PIN_USART0_SCK  {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}

/// SPI MISO pin definition (PA12).
#define PIN_SPI_MISO   {1 << 12, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}
/// SPI MOSI pin definition (PA13).
#define PIN_SPI_MOSI   {1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI SPCK pin definition (PA14).
#define PIN_SPI_SPCK   {1 << 14, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI pins definition. Contains MISO, MOSI & SPCK (PA12, PA13 & PA14).
#define PINS_SPI       PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_SPCK
/// SPI chip select 0 pin definition (PA11).
#define PIN_SPI_NPCS0  {1 << 11, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI chip select 1
#define PIN_SPI_NPCS1  {1 << 31, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// SPI chip select 2
#define PIN_SPI_NPCS2  {1 << 10, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}
/// SPI chip select 3
#define PIN_SPI_NPCS3  {1 <<  3, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT}

/// PWMC PWM0 pin definition (PA0).
#define PIN_PWMC_PWM0  {1 << 0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// PWMC PWM0 pin definition (PA1).
#define PIN_PWMC_PWM1  {1 << 1, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/// PWMC PWM0 pin definition (PA2).
#define PIN_PWMC_PWM2  {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// PWM pin definition for LED0
#define PIN_PWM_LED0 PIN_PWMC_PWM1
/// PWM pin definition for LED1
#define PIN_PWM_LED1 PIN_PWMC_PWM2
/// PWM channel for LED0
#define CHANNEL_PWM_LED0 1
/// PWM channel for LED1
#define CHANNEL_PWM_LED1 2

/// TWI pins definition. Contains TWD (PA3) and TWCK (PA4).
#define PINS_TWI  {0x00000018, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// ADC_AD0 pin definition.
#define PIN_ADC_AD0 {1 << 17, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD1 pin definition.
#define PIN_ADC_AD1 {1 << 18, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD2 pin definition. (mixed with PIN_PUSHBUTTON_1)
#define PIN_ADC_AD2 {1 << 19, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// ADC_AD3 pin definition. (mixed with PIN_PUSHBUTTON_2)
#define PIN_ADC_AD3 {1 << 20, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// Pins ADC
#define PINS_ADC PIN_ADC_AD0, PIN_ADC_AD1, PIN_ADC_AD2, PIN_ADC_AD3

/// USB VBus monitoring pin definition (PA13).
#define PIN_USB_VBUS    {1 << 13, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// USB pull-up control pin definition (PA16).
#define PIN_USB_PULLUP  {1 << 16, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_1, PIO_DEFAULT}
//------------------------------------------------------------------------------

/// !SD Card SPI
/// - BOARD_SD_SPI_BASE
/// - BOARD_SD_SPI_ID
/// - BOARD_SD_SPI_PINS
/// - BOARD_SD_NPCS

/// Not define in our board, but customer can add this feature
/// Base address of the SPI peripheral connected to the SD card.
#define BOARD_SD_SPI_BASE   AT91C_BASE_SPI
/// Identifier of the SPI peripheral connected to the SD card.
#define BOARD_SD_SPI_ID     AT91C_ID_SPI
/// List of pins to configure to access the SD card
#define BOARD_SD_SPI_PINS   PINS_SPI, PIN_SPI_NPCS1
/// NPCS number
#define BOARD_SD_NPCS       1

//------------------------------------------------------------------------------
// Flash
//------------------------------------------------------------------------------
/// Indicates chip has an EFC.
#define BOARD_FLASH_EFC
/// Address of the IAP function in ROM.
#define BOARD_FLASH_IAP_ADDRESS         0x300E08
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SAM7S-EK - External components"
/// This page lists the definitions related to external on-board components
/// located in the board.h file for the SAM7S-EK.
///
/// !ISO7816
/// - PIN_SMARTCARD_CONNECT
/// - PIN_ISO7816_RSTMC
/// - PINS_ISO7816

/// Smartcard detection pin
#define PIN_SMARTCARD_CONNECT   {1 << 5, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_DEFAULT}
/// PIN used for reset the smartcard
#define PIN_ISO7816_RSTMC       {1 << 7, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
/// Pins used for connect the smartcard
#define PINS_ISO7816            PIN_USART0_TXD, PIN_USART0_SCK, PIN_ISO7816_RSTMC
//------------------------------------------------------------------------------

#endif /* Board_h */

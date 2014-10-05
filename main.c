#include "board.h"
#include "pio/pio.h"
#include "uart.h"
#include "sid.h"
#include "led.h"

int main(void) {

//	AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1 << AT91C_ID_PIOA );
//	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, LED_MASK );

	AT91PS_AIC     pAic;
	//* Load System pAic Base address
	pAic = AT91C_BASE_AIC;

	//* Enable User Reset and set its minimal assertion to 960 us
	AT91C_BASE_RSTC->RSTC_RMR = AT91C_RSTC_URSTEN | (0x4<<8) | (unsigned int)(0xA5<<24);
	// First, enable the clock of the PIOB
	AT91F_PMC_EnablePeriphClock ( AT91C_BASE_PMC, 1 << AT91C_ID_PIOA ) ;
	// mt: added reset enable to make the board reset-button "useful"
	AT91F_RSTSetMode( AT91C_BASE_RSTC , AT91C_RSTC_URSTEN );

//	USART0Setup();
//	USART_puts("Device init\n");
		delay_ms(1000);
	sid_init();

		delay_ms(3000);
		sid_michael();
	while(1){
		delay_ms(3000);
		play_song();
	}
}


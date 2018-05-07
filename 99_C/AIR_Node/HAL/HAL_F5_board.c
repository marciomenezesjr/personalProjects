#include "HAL_F5_board.h"

uint8_t sws_stat = 0x00;

void hal_board_init(void){
	leds_init();
	sws_init();
}

void leds_init(void){
	LED1_DIR |= LED1_BIT;
	LED2_DIR |= LED2_BIT;
	LED1_OFF;
	LED2_OFF;
}


void sws_init(void){
	SW1_DIR &= ~SW1_BIT;
	SW2_DIR &= ~SW2_BIT;

	SW1_EXT_CFG;
	SW2_EXT_CFG;

#ifdef SW1_PORT_IE
	SW1_IFG = 0x00;
	SW1_IE |= SW1_BIT;
	SW1_IES |= SW1_BIT;

#endif
#ifdef SW2_PORT_IE
	SW2_IFG = 0x00;
	SW2_IE |= SW2_BIT;
	SW2_IES |= SW2_BIT;
#endif
}

#ifdef SW1_PORT_IE
#pragma vector=PORT2_VECTOR
__interrupt void SW1_ISR(void)
{
	sws_stat ^= BIT0;
	SW1_IFG &= ~SW1_BIT;
//	SW1_IFG = 0;
}
#endif

#ifdef SW2_PORT_IE
#pragma vector=PORT1_VECTOR
__interrupt void SW2_ISR(void)
{
	sws_stat ^= BIT1;
	SW2_IFG &= ~SW2_BIT;
}
#endif

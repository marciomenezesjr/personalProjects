#include "HAL_serial.h"

//************************************************************************************
// Function: 	uca1_cfg
// Description: configures MSP430's UCA1 as UART for RS485 communication.
//************************************************************************************
void uca1_cfg(void){
	P4SEL = BIT4 + BIT5;
	UCA1CTL1 |= UCSWRST;
	UCA1CTL1 |= UCSSEL_2;
	UCA1BR0 = 0x68;
	UCA1BR1 = 0x00;
	UCA1MCTL = UCBRS_4 + UCBRF_0;
	UCA1CTL1 &= ~UCSWRST;
}

/*******************************************************************************
 Function: 		uca1_wait_transmission
 Description: 	waits until the tx buffer is empty
*******************************************************************************/
void uca1_cfg_wait_transmission(void){
	while(UCA1STAT & UCBUSY);
}

/*******************************************************************************
 Function: 		uca1_sendMessage
 Description: 	sends a message through UCA1 (RS485)
*******************************************************************************/
void uca1_sendMessage(uint8_t *ucBuffer_Tx, uint8_t size){
	int16_t count;

	__disable_interrupt();
	for(count=0; count<size; count++){
		UCA1TXBUF = ucBuffer_Tx[count];              // Load data into the transmission buffer
		uca1_cfg_wait_transmission();
	}

	__enable_interrupt();
}

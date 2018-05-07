#include "AIR_Gateway.h"

// Global variables
uint8_t 	radio_success = false;
uint8_t 	radio_status = false;
uint32_t 	msgs_error = 0;
uint8_t 	rx_length = 0;

uint8_t radio_tx_buffer[RTX_BUFFER_LENGTH];
uint8_t radio_rx_buffer[RRX_BUFFER_LENGTH];

void main(void){
	device_startup();
	uca1_cfg();
	radio_status = radio_init();
	radio_wait_join_link();
	os_timer_start();
	while(1){
		__no_operation();
		__bis_SR_register(LPM0_bits + GIE);
		LED1_TOGGLE;
		if(sPeerFrameSem){
			sPeerFrameSem = 0;
		}
		radio_success = radio_rx(radio_rx_buffer, rx_length);
		uca1_sendMessage(radio_rx_buffer, sizeof(radio_rx_buffer));
	}
}

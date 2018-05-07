#include "AIR_Node.h"

uint8_t radio_status = false;
uint8_t radio_update = false;
uint8_t radio_success = false;
uint8_t radio_tx_buffer[RTX_BUFFER_LENGTH];
uint8_t radio_rx_buffer[RRX_BUFFER_LENGTH];

uint16_t missed_acks = 0x0000;

void main(void){
	uint16_t i;
	device_startup();
	radio_status = radio_init();
	os_timer_start();

	for(i=0; i<RTX_BUFFER_LENGTH; i++)
		radio_tx_buffer[i] = 33;
	i = 0;
	while(1){
		radio_tx_buffer[i]++;
		if(radio_tx_buffer[i] == 126){
			i++;
			radio_tx_buffer[i] = 33;
			if(i >= RTX_BUFFER_LENGTH){
				i = 0;
			}
		}
		radio_success = radio_tx(radio_tx_buffer);
		__bis_SR_register(LPM0_bits + GIE);
		__no_operation();

	}
}

#include "compass.h"

struct sensor_data data;
struct sensor_offsets offset;

uint8_t 	radio_status = false;
uint32_t 	msgs_error = 0;
uint32_t	frame_count = 0;

uint8_t radio_tx_buffer[RTX_BUFFER_LENGTH];
uint8_t radio_rx_buffer[RRX_BUFFER_LENGTH];

void timer_b_cfg(void);

void main(void){
	device_startup();
	sensors_init();
	radio_status = radio_init();

	//os_timer_start();
	EN_MAG_IR;
	//EN_SMCLK_OUT;
	while(1){
		read_magnetometer();
		read_accelerometer();
		read_magnetometer_temperature();
		//data_conversion();
		transmit_structure();
		__no_operation();
		__bis_SR_register(LPM0_bits + GIE);
		TEST_TOGGLE;
		frame_count++;
	}
}

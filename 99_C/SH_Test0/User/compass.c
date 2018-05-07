#include "compass.h"

uint8_t sensors_tx_buffer[RTX_BUFFER_LENGTH];

void sensors_init(void){
	sensors_reset();
	I2C_Master_Init(I2C_SOURCE_CLOCK, I2C_SOURCE_CLOCK_FREQ, I2C_CLOCK_FREQ);
	init_accelerometer();
	init_magnetometer();
	//calibrate_sensors();
}

// Sensor calibration setup
void calibrate_sensors(void){
	offset.accel_offset[0] = 0;
	offset.accel_offset[1] = 0;
	offset.accel_offset[2] = 0;

	offset.magnetom_offset[0] = 0;
	offset.magnetom_offset[1] = 0;
	offset.magnetom_offset[2] = 0;
}

void transmit_structure(void){
	//sprintf(OutputString,"!%d,%d,%d,%d,%d,%d,%d;", frame_count, data.mag_x,data.mag_y,data.mag_z,data.accel_x,data.accel_y,data.accel_z);
	//stringLength = strlen(OutputString);
	radio_tx_buffer[0] = return_lsb(frame_count);
	radio_tx_buffer[1] = return_msb(frame_count);
	radio_tx_buffer[2] = return_lsb(frame_count>>16);
	radio_tx_buffer[3] = return_msb(frame_count>>16);
	radio_tx_buffer[4] = return_lsb(data.mag_x_raw);
	radio_tx_buffer[5] = return_msb(data.mag_x_raw);
	radio_tx_buffer[6] = return_lsb(data.mag_y_raw);
	radio_tx_buffer[7] = return_msb(data.mag_y_raw);
	radio_tx_buffer[8] = return_lsb(data.mag_z_raw);
	radio_tx_buffer[9] = return_msb(data.mag_z_raw);
	radio_tx_buffer[10] = return_lsb(data.accel_x_raw);
	radio_tx_buffer[11] = return_msb(data.accel_x_raw);
	radio_tx_buffer[12] = return_lsb(data.accel_y_raw);
	radio_tx_buffer[13] = return_msb(data.accel_y_raw);
	radio_tx_buffer[14] = return_lsb(data.accel_z_raw);
	radio_tx_buffer[15] = return_msb(data.accel_z_raw);

	radio_tx(radio_tx_buffer, (uint8_t)RTX_BUFFER_LENGTH);
}


int8_t return_lsb(int16_t data){
	return (int8_t)data;
}

int8_t return_msb(int16_t data){
	//int8_t tmp;
	//tmp = int8_t(data>>8);
	return (int8_t)(data>>8);
}

void data_conversion(void){
	data.mag_x = (int16_t)(data.mag_x_raw*MAG_Resolution*10);
	data.mag_y = (int16_t)(data.mag_y_raw*MAG_Resolution*10);
	data.mag_z = (int16_t)(data.mag_z_raw*MAG_Resolution*10);

	data.accel_x = (int16_t)(data.accel_x_raw*ACCEL_Resolution*100);
	data.accel_y = (int16_t)(data.accel_y_raw*ACCEL_Resolution*100);
	data.accel_z = (int16_t)(data.accel_z_raw*ACCEL_Resolution*100);
}


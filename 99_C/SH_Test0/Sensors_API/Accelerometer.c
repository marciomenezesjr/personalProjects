#include "Accelerometer.h"

uint8_t accel_data_status = 0x00;

void init_accelerometer(void){
	I2C_Set_Slave_Address(MMA8451Q_ACCEL_ADDR);

	sensors_tx_buffer[0] = ACCEL_CTRL_REG1;		// Control Register 1
	sensors_tx_buffer[1] = 0x69; 				// Measurement Mode + Resolution

	I2C_Write_Packet_To_Sensor(&sensors_tx_buffer[0],2);
	__delay_cycles(200000);

	sensors_tx_buffer[0] = ACCEL_CTRL_REG2;	// Control Register 2
	sensors_tx_buffer[1] = 0x00; 				// Range (+-4g) + High resolution mode
	
	I2C_Write_Packet_To_Sensor(&sensors_tx_buffer[0],2);
	__delay_cycles(200000);
}


void read_accelerometer(void){
	uint8_t rx_temp_buffer[6];

	I2C_Set_Slave_Address(MMA8451Q_ACCEL_ADDR);

#ifdef ENABLE_SENSOR_DATA_STATUS
	rx_temp_buffer[0] = ACCEL_DATA_STATUS;		// Start Address
	I2C_Read_Packet_From_Sensor(&rx_temp_buffer[0],1);
	accel_data_status = rx_temp_buffer[0];
#endif

	rx_temp_buffer[0] = ACCEL_DATA_START;		// Start Address
	I2C_Read_Packet_From_Sensor(&rx_temp_buffer[0],6);


	data.accel_x_raw = ( ((int16_t)rx_temp_buffer[0]) << 8) | rx_temp_buffer[1];
	data.accel_y_raw = ( ((int16_t)rx_temp_buffer[2]) << 8) | rx_temp_buffer[3];
	data.accel_z_raw = ( ((int16_t)rx_temp_buffer[4]) << 8) | rx_temp_buffer[5];
}

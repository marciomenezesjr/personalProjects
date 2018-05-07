#include "Magnetometer.h"

uint8_t mag_data_status = 0x00;

void init_magnetometer(){
	I2C_Set_Slave_Address(MAG3110_ADDR);
	__delay_cycles(200000);
  
	/*************************** Initialization *********************************/
	sensors_tx_buffer[0] = MAG_CTRL_REG2;
	sensors_tx_buffer[1] = 0x80;
  	I2C_Write_Packet_To_Sensor(&sensors_tx_buffer[0],2);
  	__delay_cycles(200000);
  
  	sensors_tx_buffer[0] = MAG_CTRL_REG1;	// Register
  	sensors_tx_buffer[1] = 0x49;
  	I2C_Write_Packet_To_Sensor(&sensors_tx_buffer[0],2);
  	__delay_cycles(200000);
}

void read_magnetometer(void){
	uint8_t rx_temp_buffer[6];

	I2C_Set_Slave_Address(MAG3110_ADDR);

#ifdef ENABLE_SENSOR_DATA_STATUS
	rx_temp_buffer[0] = MAG_DATA_STATUS;
	I2C_Read_Packet_From_Sensor(&rx_temp_buffer[0],1);
	mag_data_status = rx_temp_buffer[0];
#endif

	rx_temp_buffer[0] = MAG_DATA_START;
	I2C_Read_Packet_From_Sensor(&rx_temp_buffer[0],6);

	// read out the 3 values, 2 bytes each.
	data.mag_x_raw = (rx_temp_buffer[0] << 8) | rx_temp_buffer[1];
	data.mag_z_raw = (rx_temp_buffer[2] << 8) | rx_temp_buffer[3];
	data.mag_y_raw = (rx_temp_buffer[4] << 8) | rx_temp_buffer[5];
}

void read_magnetometer_temperature(void){
	uint8_t rx_temp_buffer[2];
	I2C_Set_Slave_Address(MAG3110_ADDR);

	rx_temp_buffer[0] = MAG_DIE_TEMP;
	I2C_Read_Packet_From_Sensor(&rx_temp_buffer[0],1);
	data.mag_die_temp = rx_temp_buffer[0];
}

void Compass_Heading(void){
	__no_operation();
}

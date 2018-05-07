#include "SH_Gateway.h"

struct sensor_data data;

char uart_tx_buffer[UART_TX_BUFFER];
uint16_t stringLength;

uint8_t radio_rx(uint8_t *r_rx_buffer, uint8_t length){
	if(SMPL_SUCCESS == SMPL_Receive(sLinkID1, r_rx_buffer, &length))
		return true;
	else
		return false;
}

uint8_t radio_tx(uint8_t *r_tx_buffer){
	// get radio ready...awakens in idle state
	SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);
	if(SMPL_SUCCESS == SMPL_SendOpt(sLinkID1, r_tx_buffer, sizeof(r_tx_buffer), SMPL_TXOPTION_ACKREQ)){
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
		return true;
	}
	else{
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
		return false;
	}
}

uint16_t data_format(uint8_t *r_tx_buffer){
	data.frame_count = r_tx_buffer[3];
	data.frame_count <<= 8;
	data.frame_count += r_tx_buffer[2];
	data.frame_count <<= 8;
	data.frame_count += r_tx_buffer[1];
	data.frame_count <<= 8;
	data.frame_count += r_tx_buffer[0];

	data.mag_x = r_tx_buffer[5];
	data.mag_x <<= 8;
	data.mag_x += r_tx_buffer[4];
	data.mag_x_f = data.mag_x*MAG_Resolution;

	data.mag_y = r_tx_buffer[7];
	data.mag_y <<= 8;
	data.mag_y += r_tx_buffer[6];
	data.mag_y_f = data.mag_y*MAG_Resolution;

	data.mag_z = r_tx_buffer[9];
	data.mag_z <<= 8;
	data.mag_z += r_tx_buffer[8];
	data.mag_z_f = data.mag_z*MAG_Resolution;

	data.accel_x = r_tx_buffer[11];
	data.accel_x <<= 8;
	data.accel_x += r_tx_buffer[10];
	data.accel_x_f = data.accel_x*ACCEL_Resolution;

	data.accel_y = r_tx_buffer[13];
	data.accel_y <<= 8;
	data.accel_y += r_tx_buffer[12];
	data.accel_y_f = data.accel_y*ACCEL_Resolution;

	data.accel_z = r_tx_buffer[15];
	data.accel_z <<= 8;
	data.accel_z += r_tx_buffer[14];
	data.accel_z_f = data.accel_z*ACCEL_Resolution;

	__disable_interrupt();
	clear_uart_tx_buffer();
	sprintf(uart_tx_buffer,"!%ld,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f",data.frame_count,data.mag_x_f,data.mag_y_f,data.mag_z_f,data.accel_x_f,data.accel_y_f,data.accel_z_f);
	__enable_interrupt();
	stringLength = strlen(uart_tx_buffer);
	return stringLength;
}

void clear_uart_tx_buffer(void){
	uint16_t i;
	for(i=0;i<UART_TX_BUFFER;i++)
		uart_tx_buffer[i] = 0x00;
}


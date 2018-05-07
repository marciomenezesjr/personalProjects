#ifndef SH_GATEWAY_H_
#define SH_GATEWAY_H_

// Includes
#include <string.h>
#include "Gateway_Radio_interface.h"
#include "HAL_device.h"

// Defines
#define RTX_BUFFER_LENGTH	0x08
#define RRX_BUFFER_LENGTH	0x10
#define UART_TX_BUFFER		0x80

#define MAG_Resolution		0.10f
#define ACCEL_Resolution	0.00006104f

extern uint8_t radio_tx(uint8_t *);
extern uint16_t data_format(uint8_t *);
extern void clear_uart_tx_buffer(void);
extern uint8_t radio_rx(uint8_t *, uint8_t);

// Sensor Variables
struct sensor_data{
    float accel_x_f;
    float accel_y_f;
    float accel_z_f;
    float mag_x_f;
    float mag_y_f;
    float mag_z_f;

	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
	uint32_t frame_count;
};

// Global shared variables
extern char uart_tx_buffer[];


#endif

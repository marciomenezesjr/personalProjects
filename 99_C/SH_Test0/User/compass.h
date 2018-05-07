#ifndef COMPASS_H_
#define COMPASS_H_

// Defines
#define MAG_Resolution		0.10f
#define ACCEL_Resolution	0.00006104f

// Includes
#include <string.h>
#include "HAL_device.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "Node_Radio_Interface.h"

// Sensor Variables
struct sensor_data{
    int16_t accel_x_raw;
    int16_t accel_y_raw;
    int16_t accel_z_raw;
    int16_t mag_x_raw;
    int16_t mag_y_raw;
    int16_t mag_z_raw;

    int16_t V_int_raw;
	int16_t T_mcu_raw;
	int8_t mag_die_temp;

	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
};

struct sensor_offsets{
    int16_t accel_offset[3];
    int16_t gyro_offset[3];
    int16_t magnetom_offset[3];
    int16_t magnetom_XY_Theta;
    int16_t magnetom_XY_Scale;
    int16_t magnetom_YZ_Theta;
    int16_t magnetom_YZ_Scale;
}sensor_data;

// Prototypes
extern void sensors_init(void);
extern void data_conversion(void);
extern void calibrate_sensors(void);
extern void transmit_structure(void);
extern int8_t return_lsb(int16_t);
extern int8_t return_msb(int16_t);

//Global shared variables
extern struct sensor_data data;
extern struct sensor_offsets offset;

extern uint32_t	frame_count;
extern uint8_t sensors_tx_buffer[];


#endif

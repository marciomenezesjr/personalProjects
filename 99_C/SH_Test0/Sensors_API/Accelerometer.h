#include "HAL_I2C.h"
#include "compass.h"

#define MMA8451Q_ACCEL_ADDR 	0x1C // 7 bit address of the ADXL345
#define ACCEL_CTRL_REG1			0x2A
#define ACCEL_CTRL_REG2			0x2B
#define ACCEL_DATA_START		0x01
#define ACCEL_DATA_STATUS		0x00

extern void init_accelerometer(void);
extern void read_accelerometer(void);

#include "HAL_I2C.h"
#include "compass.h"

#define MAG3110_ADDR			0x0E
#define MAG_CTRL_REG1			0x10
#define MAG_CTRL_REG2			0x11
#define MAG_DATA_START			0x01
#define MAG_DATA_STATUS			0x00
#define MAG_DIE_TEMP			0x0F

extern void init_magnetometer(void);
extern void read_magnetometer(void);
extern void read_magnetometer_temperature(void);
extern void Compass_Heading(void);
extern void Calibrate(void);

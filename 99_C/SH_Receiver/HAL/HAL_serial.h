#ifndef HAL_SERIAL_H_
#define HAL_SERIAL_H_

// Includes
#include "HAL_device.h"

// Defines
#define START_CHAR		'!'
#define DELIMITER_CHAR	';'

// Function prototypes
extern void uca1_cfg(void);
extern void uca1_sendMessage(uint16_t size);
extern void uca1_cfg_wait_transmission(void);



#endif

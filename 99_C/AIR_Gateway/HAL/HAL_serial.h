#ifndef HAL_SERIAL_H_
#define HAL_SERIAL_H_

#include "HAL_device.h"

extern void uca1_cfg(void);
extern void uca1_sendMessage(uint8_t *,uint8_t size);
extern void uca1_cfg_wait_transmission(void);



#endif

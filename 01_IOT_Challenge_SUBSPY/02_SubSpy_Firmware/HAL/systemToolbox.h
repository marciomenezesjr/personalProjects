/*
 * systemToolbox.h
 *
 *  Created on: 20.05.2017
 *      Author: marcio
 */

#ifndef HAL_SYSTEMTOOLBOX_H_
#define HAL_SYSTEMTOOLBOX_H_


// Includes
#include "driverlib.h"
#include "USB_API/USB_Common/usb.h"


// Defines
#define UCS_XT1_TIMEOUT             50000               // XT1 initialization timeout
#define UCS_XT2_TIMEOUT             50000               // XT2 initialization timeout
#define UCS_XT1_CRYSTAL_FREQUENCY   32768               // XT1 frequency
#define UCS_XT2_CRYSTAL_FREQUENCY   4000000             // XT2 frequency
#define OS_TIMER_REFERENCE          33                  // Global time counter reference
#define GPIO_ALL                    GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7


// Function prototypes
extern uint8_t sysInit(void);
extern uint32_t sysGetGTime(void);
extern void sysDelayMs(uint16_t);

// Global shared variables
extern volatile uint32_t wakeMeUpAt;
extern volatile bool forceEnable;






#endif /* HAL_SYSTEMTOOLBOX_H_ */

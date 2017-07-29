/*
 * spi.h
 *
 *  Created on: 20.05.2017
 *      Author: marcio
 */

#ifndef HAL_PERIPHERALACCESS_H_
#define HAL_PERIPHERALACCESS_H_

// Include section
#include "driverlib.h"
#include "systemToolbox.h"

// Function prototypes
extern void spiInit(void);
extern void spiSlaveEnable(void);
extern void spiSlaveDisable(void);
extern uint8_t spiReceiveByte(uint8_t byte);
extern void spiTransmitByte(uint8_t byte);
extern uint8_t spiReadReg(uint8_t addr);
extern void spiWriteReg(uint8_t addr, uint8_t txData);
extern void gpioSelectPinInterruptEdge(uint8_t port, uint16_t pin, uint8_t edge);
extern void gpioEnablePinInterrupt(uint8_t port, uint16_t pin);
extern void gpioDisablePinInterrupt(uint8_t port, uint16_t pin);
extern void gpioClearPinInterrupt(uint8_t port, uint16_t pin);
extern void gpioSetAsInputPin(uint8_t port, uint16_t pin);
extern uint8_t gpioReadPinStatus(uint8_t port, uint16_t pin);



// Global shared variables
extern volatile uint8_t pinInterrupt;

#endif /* HAL_PERIPHERALACCESS_H_ */

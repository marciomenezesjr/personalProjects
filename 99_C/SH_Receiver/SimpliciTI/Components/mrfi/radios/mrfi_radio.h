#ifndef MRFI_RADIO_H_
#define MRFI_RADIO_H_

#include "bsp.h"

// Global shared variables
extern uint8_t mrfiRadioState;

// Global function prototypes
extern void MRFI_GpioIsr(void);
extern void Mrfi_RxModeOn(void);
extern void Mrfi_RxModeOff(void);


#endif

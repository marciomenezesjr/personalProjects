#ifndef AIR_NODE_H_
#define AIR_NODE_H_

// Includes
#include "Radio_interface.h"
#include "HAL_device.h"

// Defines
#define RTX_BUFFER_LENGTH	0x08
#define RRX_BUFFER_LENGTH	0x08

extern uint8_t radio_tx_buffer[];
extern uint8_t radio_rx_buffer[];

extern uint8_t radio_tx(uint8_t *);
extern uint8_t radio_rx(uint8_t *, uint8_t);

#endif

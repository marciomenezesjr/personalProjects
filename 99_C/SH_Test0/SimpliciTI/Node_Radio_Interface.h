#ifndef NODE_RADIO_INTERFACE_H_
#define NODE_RADIO_INTERFACE_H_

// Includes
#include <string.h>
#include "nwk.h"
#include "mrfi.h"
#include "nwk_api.h"
#include "nwk_frame.h"
#include "nwk_types.h"
#include "bsp_glue.h"

// Defines
#define RTX_BUFFER_LENGTH	0x10
#define RRX_BUFFER_LENGTH	0x08

// Function prototypes
extern uint8_t radio_init(void);

// Global shared variables
extern linkID_t sLinkID1;

extern uint8_t radio_tx_buffer[];
extern uint8_t radio_rx_buffer[];

extern uint8_t radio_tx(uint8_t *, uint8_t);
extern uint8_t radio_rx(uint8_t *, uint8_t);

#endif

#ifndef RADIO_INTERFACE_H_
#define RADIO_INTERFACE_H_

// Includes
#include <string.h>
#include "nwk.h"
#include "mrfi.h"
#include "nwk_api.h"
#include "nwk_frame.h"
#include "nwk_types.h"
#include "bsp_glue.h"

// Defines
#define RTX_BUFFER_LENGTH	0x08
#define RRX_BUFFER_LENGTH	0x08

// Function prototypes
extern uint8_t radio_init(void);

// Global shared variables
extern linkID_t sLinkID1;

#endif

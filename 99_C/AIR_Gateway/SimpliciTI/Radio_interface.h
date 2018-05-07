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

// Function prototypes
extern uint8_t radio_init(void);
extern void radio_wait_join_link(void);


// Global shared variables
extern volatile uint8_t sPeerFrameSem;
extern linkID_t sLinkID1;

#endif

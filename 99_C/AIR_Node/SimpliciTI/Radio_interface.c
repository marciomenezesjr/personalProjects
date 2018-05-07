// Includes
#include "Radio_interface.h"

// Defines
#define SPIN_ABOUT_A_SECOND   			NWK_DELAY(1000)
#define SPIN_ABOUT_A_QUARTER_SECOND   	NWK_DELAY(250)

// How many times to try a Tx and miss an acknowledge before doing a scan
#define MISSES_IN_A_ROW  	2

// Globals
linkID_t sLinkID1 = 0;
uint8_t      noAck, done, misses;
smplStatus_t rc;

static void linkTo(void);

uint8_t radio_init(void){
	/* Keep trying to join (a side effect of successful initialization) until
	 * successful. Toggle LEDS to indicate that joining has not occurred.
	 */
	while(SMPL_SUCCESS != SMPL_Init(0)){
		LED2_TOGGLE;
		SPIN_ABOUT_A_QUARTER_SECOND;
	}

	// Unconditional link to AP which is listening due to successful join.
	linkTo();

	// Turn on green LED.
	LED2_ON;

	return true;
}

static void linkTo(void){
	// Keep trying to link...
	while(SMPL_SUCCESS != SMPL_Link(&sLinkID1)){
		LED2_TOGGLE;
		SPIN_ABOUT_A_SECOND;
		LED2_TOGGLE;
	}
	// Put the radio to sleep
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
}

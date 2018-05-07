// Includes
#include "Node_Radio_Interface.h"

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
		GREEN_TOGGLE;
		SPIN_ABOUT_A_QUARTER_SECOND;
	}

	// Unconditional link to AP which is listening due to successful join.
	linkTo();

	// Turn on green LED.
	GREEN_ON;

	return true;
}

static void linkTo(void){
	// Keep trying to link...
	while(SMPL_SUCCESS != SMPL_Link(&sLinkID1)){
		GREEN_TOGGLE;
		SPIN_ABOUT_A_SECOND;
		GREEN_TOGGLE;
	}
	// Put the radio to sleep
	SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
}

uint8_t radio_rx(uint8_t *r_rx_buffer, uint8_t length){
	if(SMPL_SUCCESS == SMPL_Receive(sLinkID1, r_rx_buffer, &length))
		return false;
	else
		return true;
}

uint8_t radio_tx(uint8_t *r_tx_buffer, uint8_t tx_buffer_size){
	// get radio ready...awakens in idle state
	SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);
	if(SMPL_SUCCESS == SMPL_SendOpt(sLinkID1, r_tx_buffer, tx_buffer_size, SMPL_TXOPTION_ACKREQ)){
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
		return true;
	}
	else{
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
		return false;
	}
}

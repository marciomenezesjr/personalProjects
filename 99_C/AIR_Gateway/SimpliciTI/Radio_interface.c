#include "Radio_interface.h"

// reserve space for the maximum possible peer Link IDs
linkID_t sLinkID1 = 0x00;

// callback handler
static uint8_t sCB(linkID_t);

// received message handler
//static void processMessage(linkID_t, uint8_t *, uint8_t);

// Frequency Agility helper functions
//static void changeChannel(void);
//static void checkChangeChannel(void);

// work loop semaphores
volatile uint8_t sPeerFrameSem = 0;
volatile uint8_t sJoinSem = 0;

#ifdef FREQUENCY_AGILITY
// BEGIN interference detection support
#define INTERFERNCE_THRESHOLD_DBM (-70)
#define SSIZE    25
#define IN_A_ROW  3
static int8_t  sSample[SSIZE];
//static uint8_t sChannel = 0;
#endif  // FREQUENCY_AGILITY

// Variable to save the interrupt enable flag state
bspIState_t intState;

// END interference detection support

#define SPIN_ABOUT_A_QUARTER_SECOND   NWK_DELAY(250)

uint8_t radio_init(void){
	memset(sSample, 0x0, sizeof(sSample));
	SMPL_Init(sCB);

	// Green LED on solid to indicate waiting for a Join
	LED2_ON;
	return true;
}

void radio_wait_join_link(void){
	while(1){
		if(SMPL_SUCCESS == SMPL_LinkListen(&sLinkID1)){
			break;
		}
	}
	BSP_ENTER_CRITICAL_SECTION(intState);
	sJoinSem--;
	BSP_EXIT_CRITICAL_SECTION(intState);
}

/* Runs in ISR context. Reading the frame should be done in the */
/* application thread not in the ISR thread. */
static uint8_t sCB(linkID_t lid){
	LED1_TOGGLE;
	if(lid){
		sPeerFrameSem++;
		//radio_read_msg();
	}
	else{
		sJoinSem++;
	}
	__bic_SR_register(LPM0_bits);
	// leave frame to be read by application.
	return 0;
}

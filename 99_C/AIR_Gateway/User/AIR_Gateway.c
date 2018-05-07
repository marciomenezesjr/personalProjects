#include "AIR_Gateway.h"

uint8_t radio_rx(uint8_t *r_rx_buffer, uint8_t length){
	if(SMPL_SUCCESS == SMPL_Receive(sLinkID1, r_rx_buffer, &length))
		return true;
	else
		return false;
}

uint8_t radio_tx(uint8_t *r_tx_buffer){
	// get radio ready...awakens in idle state
	SMPL_Ioctl(IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_AWAKE, 0);
	if(SMPL_SUCCESS == SMPL_SendOpt(sLinkID1, r_tx_buffer, sizeof(r_tx_buffer), SMPL_TXOPTION_ACKREQ)){
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
		return true;
	}
	else{
		SMPL_Ioctl( IOCTL_OBJ_RADIO, IOCTL_ACT_RADIO_SLEEP, 0);
		return false;
	}
}



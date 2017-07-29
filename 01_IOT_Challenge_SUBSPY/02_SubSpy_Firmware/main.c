#include "rfm69.h"
#include "peripheralAccess.h"
#include "systemToolbox.h"
#include "rfm69Gateway.h"

/*
 * main.c
 *
 *  Created on: 27.05.2017
 *      Author: marcio
 */

 void main(void) {
    sysInit();				// Performs sytems initialization (RTC, clocks, timers, gpios, vcore and USB)
    gatewayInit();			// Initializes the RFM69CW radio transceiver

    while(1){
        wakeMeUpAt = sysGetGTime() + devConfig.sweepPeriod;
        __bis_SR_register(LPM0_bits + GIE);         // Host MCU waits in LPM0 for either data or rtc expiration

        gatewayReceiveCmd();						// If there is a new CMD available from USB, process it
        if(spyEnable || forceEnable){				// If spy is enabled, proceed to promiscuous listening operation
            gatewayPassiveListen();
        }
    }
}

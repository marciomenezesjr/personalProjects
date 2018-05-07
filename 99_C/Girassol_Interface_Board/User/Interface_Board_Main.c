#include "Interface_Board_Routines.h"

void main(void){
    device_init();
    RED_ON;
    SOLAR_ON;
    DAC_ENABLE;
    device_os_timer_start();
    while(1){
    	ib_read_adc();
    	ib_data_process();
    	ib_discretes_update();
    	if(CHECK_SW){					// Update Tx vector for transmission
    		ib_load_tx_data();
			ib_reset_integrators();
			CLEAR_SW;
    	}
    	if(CHECK_UPDATE){				// Online update parameters
    		ib_params_update();
    		CLEAR_UPDATE;
    	}
    	if(CHECK_CAL){					// Calibrates ADC
    		ib_offset_calculation();
			CLEAR_CAL;
		}
    	ib_mppt_update();
    	frame_counter++;
    	__bis_SR_register(LPM0_bits + GIE);
    	__no_operation();
    }
}

#include "bsp_glue.h"

void BSP_DELAY_USECS(uint16_t delay){
	os_usdelay_timer_init(delay);
}




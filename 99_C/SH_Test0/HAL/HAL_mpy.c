#include "HAL_mpy.h"

int16_t q15_mult(int16_t a, int16_t b){
  	MPY32CTL0 = MPYFRAC;                      	// Set fractional mode
  	MPYS = (int16_t)a;                       	// Load first operand
  	OP2 = (int16_t)b;                			// Load second operand
  	MPY32CTL0 &= ~MPYFRAC;
	return  RESHI;
}




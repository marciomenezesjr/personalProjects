#include "Interface_Board_Routines.h"

// Configuration parameters
uint16_t word0 = 0;
uint16_t word1 = 0;
uint16_t word2 = 0;
uint16_t word3 = 0;

// Variables using on moving window filter
uint16_t tmp_iosense = 0;
uint16_t tmp_vosense = 0;
uint16_t tmp_iisense = 0;
uint16_t tmp_visense = 0;
uint16_t tmp_light = 0;
uint16_t tmp_temp = 0;
uint16_t tmp_vsys = 0;
uint16_t tmp_int_temp = 0;

float int_in_power = 0;
float int_out_power = 0;
float input_product = 0;
float output_product = 0;
float avg_product = 0;
float prev_avg_product = 0;

uint32_t int_avg_vsys = 0;
uint32_t int_avg_temp = 0;
uint32_t int_avg_light = 0;
uint32_t int_avg_int_temp = 0;

int16_t iosense = 0;
int16_t vosense = 0;
int16_t iisense = 0;
int16_t visense = 0;
uint16_t light = 0;
uint16_t temp = 0;
uint16_t vsys = 0;
uint16_t int_temp = 0;
uint16_t vmppt = VMPPT_START;

uint16_t iisense_offset = 0;
uint16_t iosense_offset = 0;
uint16_t visense_offset = 0;
uint16_t vosense_offset = 0;

uint32_t in_power = 0;
uint32_t out_power = 0;
uint32_t avg_vsys = 0;
uint32_t avg_vin = 0;
uint32_t avg_iin = 0;
uint32_t avg_vout = 0;
uint32_t avg_iout = 0;

uint32_t avg_temp = 0;
uint32_t avg_light = 0;
uint32_t avg_int_temp = 0;

volatile uint16_t ib_discretes = 0;


uint8_t spv_cnt = 0;
uint16_t avg_cnt = 0;


int16_t mppt_cnt = True;
uint8_t mppt_flag = False;


float float_iin = 0;
float float_iout = 0;
float float_vin = 0;
float float_vout = 0;

float aux_var = 0;

void ib_read_adc(void){
	uint16_t i;
	for(i=0;i<SPV;i++){
		device_sample_adc();
		tmp_iisense += adc_buffer[IISENSE];
		tmp_iosense += adc_buffer[IOSENSE];
		tmp_visense += adc_buffer[VISENSE];
		tmp_vosense += adc_buffer[VOSENSE];
		tmp_light += adc_buffer[LIGHT];
		tmp_temp += adc_buffer[TEMP];
		tmp_vsys += adc_buffer[VSYS];
		tmp_int_temp += adc_buffer[INT_TEMP];
	}
	iisense = tmp_iisense>>SPV_SHIFT;
	iosense = tmp_iosense>>SPV_SHIFT;
	visense = tmp_visense>>SPV_SHIFT;
	vosense = tmp_vosense>>SPV_SHIFT;
	light = tmp_light>>SPV_SHIFT;
	temp = tmp_temp>>SPV_SHIFT;
	vsys = tmp_vsys>>SPV_SHIFT;
	int_temp = tmp_int_temp>>SPV_SHIFT;
	ib_reset_filter();
	ib_offset_compensation();
}

void ib_data_process(void){
	calculate_energy();
	int_avg_light += light;
	int_avg_temp += temp;
	int_avg_vsys += vsys;
	int_avg_int_temp += int_temp;
	avg_cnt++;

	if(avg_cnt == AVG_FRAMES){
		in_power = (uint32_t)(int_in_power/avg_cnt);
		out_power = (uint32_t)(int_out_power/avg_cnt);
		avg_light = int_avg_light/avg_cnt;
		avg_temp = int_avg_temp/avg_cnt;
		avg_vsys = int_avg_vsys/avg_cnt;
		avg_int_temp = int_avg_int_temp/avg_cnt;
		avg_vin /= avg_cnt;
		avg_iin /= avg_cnt;
		avg_vout /= avg_cnt;
		avg_iout /= avg_cnt;
		ib_2_eng_unit();
		avg_cnt = 0;
		TRIGGER_SW;
	}
}

void calculate_energy(void){
	float_vin =  visense*V_REF_MV*V_FACTOR/ADC_RESOLUTION;
	float_iin = (iisense*V_REF_MV/ADC_RESOLUTION)/(I_FACTOR);
	input_product = float_vin*float_iin;
	int_in_power += input_product;

	float_vout =  vosense*V_REF_MV*V_FACTOR/ADC_RESOLUTION;
	float_iout = (iosense*V_REF_MV/ADC_RESOLUTION)/(I_FACTOR);
	output_product = float_vout*float_iout;
	int_out_power += output_product;

	avg_vin += (uint32_t)(float_vin*100);
	avg_iin += (uint32_t)(float_iin*100);
	avg_vout += (uint32_t)(float_vout*100);
	avg_iout += (uint32_t)(float_iout*100);
}

void ib_reset_integrators(void){
	int_in_power = 0;
	int_out_power = 0;
	int_avg_light = 0;
	int_avg_temp = 0;
	int_avg_vsys = 0;
	int_avg_int_temp = 0;
	avg_vin = 0;
	avg_iin = 0;
	avg_vout = 0;
	avg_iout = 0;
}

void ib_reset_filter(void){
	tmp_iisense = 0;
	tmp_iosense = 0;
	tmp_visense = 0;
	tmp_vosense = 0;
	tmp_light = 0;
	tmp_temp = 0;
	tmp_vsys = 0;
	tmp_int_temp = 0;
}

void ib_load_tx_data(void){
	__disable_interrupt();
	//ib_debug_fake_data();						// Load test data
	ib_load_tx(in_power,IN_POWER_OFFSET,LONG);
	ib_load_tx(out_power,OUT_POWER_OFFSET,LONG);
	ib_load_tx(avg_vin,AVG_VIN_OFFSET,LONG);
	ib_load_tx(avg_iin,AVG_IIN_OFFSET,LONG);
	ib_load_tx(avg_vout,AVG_VOUT_OFFSET,LONG);
	ib_load_tx(avg_iout,AVG_IOUT_OFFSET,LONG);
	ib_load_tx(avg_temp,AVG_TEMP_OFFSET,LONG);
	ib_load_tx(avg_light,AVG_LIGHT_OFFSET,LONG);
	ib_load_tx(avg_vsys,AVG_VSYS_OFFSET,LONG);
	ib_load_tx(ib_discretes,IB_DISCRETES_OFFSET,SHORT);
	ib_load_tx(frame_counter,IB_FRAME_COUNTER_OFFSET,LONG);
	if(DAC_STAT){													// Enable/Disable DAC via software
		ib_load_tx(vmppt,VMPPT_OFFSET,SHORT);
	}
	else{
		ib_load_tx(DAC_DISABLE_CODE,VMPPT_OFFSET,SHORT);
	}

	__enable_interrupt();
}

void ib_params_update(void){
	word0 = ib_read_rx_buffer(WORD0_OFFSET);
	word1 = ib_read_rx_buffer(WORD1_OFFSET);
	word2 = ib_read_rx_buffer(WORD2_OFFSET);
	word3 = ib_read_rx_buffer(WORD3_OFFSET);
}

uint16_t ib_read_rx_buffer(uint8_t offset){
	uint16_t tmp;
	tmp = i2c_rx_buffer[offset+1];
	tmp <<= 8;
	tmp += i2c_rx_buffer[offset];
	return tmp;
}

void ib_load_tx(uint32_t data, uint8_t offset, uint8_t size){
	if(size==LONG){
		i2c_tx_buffer[offset] = (uint8_t)data;
		data >>= 8;
		i2c_tx_buffer[offset+1] = (uint8_t)data;
		data >>= 8;
		i2c_tx_buffer[offset+2] = (uint8_t)data;
		data >>= 8;
		i2c_tx_buffer[offset+3] = (uint8_t)data;
	}
	else{
		i2c_tx_buffer[offset] = (uint8_t)data;
		data >>= 8;
		i2c_tx_buffer[offset+1]  = (uint8_t)data;
	}
}

void ib_2_eng_unit(void){
	// Internal System Voltagem (mV)
	aux_var = (avg_vsys*V_REF/ADC_RESOLUTION)*200000;
	avg_vsys = (uint32_t)aux_var;

	// Internal System Temperature (degC)
	aux_var = ((avg_int_temp*0.6877) - 277.7465)*100;
	avg_int_temp = (uint32_t)aux_var;

	// External Thermistor Temperature
	aux_var = (avg_temp*V_REF/ADC_RESOLUTION)*100000;
	avg_temp = (uint32_t)aux_var;
	aux_var = 200000.0*(avg_vsys/100.0 - avg_temp/100.0)/(avg_temp/100.0);
	//aux_var = (BETA*TK)/((log(aux_var/RT25)*TK)+BETA);					// Overhead too high, moved to main board!
	avg_temp = (uint32_t)aux_var;

	aux_var = (avg_light*1100.0/ADC_RESOLUTION)*100;
	avg_light = (uint32_t)aux_var;
}

void ib_calibrate_int_data(void){
	avg_int_temp = (avg_int_temp - ADC_25T30)*(55/(ADC_25T85 - ADC_25T30)) + 30;
	avg_vsys = (ADC_25VREF*avg_vsys)>>15;
}

void ib_offset_calculation(void){
	uint16_t i;
	for(i=0;i<OFFSET_SAMPLES;i++){
		device_sample_adc();
		tmp_iisense += adc_buffer[IISENSE];
		tmp_iosense += adc_buffer[IOSENSE];
		tmp_visense += adc_buffer[VISENSE];
		tmp_vosense += adc_buffer[VOSENSE];
		__bis_SR_register(LPM0_bits + GIE);
	}
	iisense_offset = tmp_iisense/OFFSET_SAMPLES;
	iosense_offset = tmp_iosense/OFFSET_SAMPLES;
	visense_offset = tmp_visense/OFFSET_SAMPLES;
	vosense_offset = tmp_vosense/OFFSET_SAMPLES;
	visense_offset += 1;								// Takes care of LSB oscillation
	vosense_offset += 1;								// Takes care of LSB oscillation
	ib_reset_filter();
}

void ib_offset_compensation(void){
	iisense -= iisense_offset;
	iosense -= iosense_offset;
	visense -= visense_offset;
	vosense -= vosense_offset;
}

void ib_mppt_update(void){
	avg_product += input_product;
	if(mppt_cnt>MPPT_SAMPLES){
		if(avg_product < MPPT_ERR_HYST)		// Takes care of floating point math errors
			avg_product = 0;

		if(avg_product<prev_avg_product){
			mppt_flag ^= BIT0;
		}
		ib_vmppt_refresh(mppt_flag);
		prev_avg_product = avg_product;
		avg_product = 0;
		mppt_cnt = 0;
		ib_load_vmppt();
	}
	mppt_cnt++;
}

void ib_vmppt_refresh(uint8_t direction){
	if(direction){
		ib_inc_vmppt();
	}
	else{
		ib_dec_vmppt();
	}
}

void ib_inc_vmppt(void){
	vmppt += VMPPT_STEP;
	if(vmppt > VMPPT_UP_LMT){
		mppt_flag ^= BIT0;
		vmppt = VMPPT_START;
	}
}

void ib_dec_vmppt(void){
	vmppt -= VMPPT_STEP;
	if(vmppt < VMPPT_LW_LMT){
		mppt_flag ^= BIT0;
		vmppt = VMPPT_START;
	}
}

void ib_load_vmppt(void){
	__disable_interrupt();
	ib_load_tx(vmppt,VMPPT_OFFSET,SHORT);
	__enable_interrupt();
}

void ib_discretes_update(void){
	if(DIO1_STAT){
		ib_discretes |= LIFE_FAULT;
	}
	else{
		ib_discretes &= ~LIFE_FAULT;
	}

	if(DIO2_STAT){
		ib_discretes |= LIFE_CHRG;
	}
	else{
		ib_discretes &= ~LIFE_CHRG;
	}

	if(SOLAR_STAT){
		ib_discretes |= LTC_EN;
	}
	else{
		ib_discretes &= ~LTC_EN;
	}

	if(DAC_STAT){
		ib_discretes |= DAC_EN;
	}
	else{
		ib_discretes &= ~DAC_EN;
	}
}

/* Test data */
void ib_debug_fake_data(void){
	in_power = 1020;
	out_power = 3040;
	avg_vin = 5060;
	avg_iin = 7080;
	avg_vout = 9010;
	avg_iout = 1122;
	avg_temp = 998811;
	avg_light = 5566;
	avg_vsys = 7788;
}


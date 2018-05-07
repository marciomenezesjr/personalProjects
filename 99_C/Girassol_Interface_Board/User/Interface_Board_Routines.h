#ifndef INTERFACE_BOARD_MAIN_H_
#define INTERFACE_BOARD_MAIN_H_

// Includes
#include "Device.h"
#include "Interface_Board_Time.h"
#include <math.h>

// Defines
#define INA_GAIN		100.0
#define R_SHUNT			0.25
#define I_FACTOR		INA_GAIN*R_SHUNT
#define V_FACTOR		3.0
#define ADC_RESOLUTION	1024.0

#define VMPPT_STEP		0x39 		// 1mu = 0.0034 so vmppt step = ~50mV
#define VMPPT_UP_LMT	0xC6F		// Vmppt Upper Limit = 2800.0 mV
#define VMPPT_LW_LMT	0x1C7		// Vmppt Lower Limit = 400.0 mV
#define VMPPT_START		0x6A9		// Vmppt Start Voltage = 1500.0 mV
#define MPPT_ERR_HYST	10

#define TRIGGER_SW		cmd_idx |= BIT7
#define CLEAR_SW		cmd_idx &= ~BIT7
#define CHECK_SW		cmd_idx&BIT7

#define TRIGGER_UPDATE	cmd_idx |= BIT1
#define CLEAR_UPDATE	cmd_idx &= ~BIT1
#define CHECK_UPDATE	cmd_idx&BIT1

#define TRIGGER_CAL		cmd_idx |= BIT2
#define CLEAR_CAL		cmd_idx &= ~BIT2
#define CHECK_CAL		cmd_idx&BIT2

#define DAC_ENABLE		cmd_idx |= BIT3
#define DAC_DISABLE		cmd_idx &= ~BIT3
#define DAC_STAT		cmd_idx&BIT3

// I2C address offsets
#define IN_POWER_OFFSET        	0x24
#define OUT_POWER_OFFSET       	0x04
#define AVG_VIN_OFFSET          0x08
#define AVG_IIN_OFFSET          0x0C
#define AVG_VOUT_OFFSET         0x10
#define AVG_IOUT_OFFSET         0x14
#define AVG_TEMP_OFFSET         0x18
#define AVG_LIGHT_OFFSET        0x1C
#define AVG_VSYS_OFFSET         0x20
#define IB_FRAME_COUNTER_OFFSET 0x00
#define IB_DISCRETES_OFFSET     0x28
#define VMPPT_OFFSET     		0x2A
#define WORD0_OFFSET            0x00
#define WORD1_OFFSET            0x02
#define WORD2_OFFSET            0x04
#define WORD3_OFFSET            0x06
#define LONG					0x04
#define SHORT					0x02
#define DAC_DISABLE_CODE		0x3000

// Status message bits definition
#define LIFE_FAULT				BIT0
#define LIFE_CHRG				BIT1
#define DAC_EN					BIT2
#define LTC_EN					BIT3


// Function Prototypes
extern void ib_read_adc(void);
extern void ib_inc_vmppt(void);
extern void ib_dec_vmppt(void);
extern void ib_2_eng_unit(void);
extern void ib_load_vmppt(void);
extern void ib_update_leds(void);
extern void ib_mppt_update(void);
extern void ib_reset_filter(void);
extern void ib_data_process(void);
extern void ib_data_receive(void);
extern void ib_load_tx_data(void);
extern void ib_params_update(void);
extern void calculate_energy(void);
extern void ib_discretes_update(void);
extern void ib_reset_integrators(void);
extern void ib_calibrate_int_data(void);
extern void ib_vmppt_refresh(uint8_t);
extern void ib_load_tx(uint32_t, uint8_t, uint8_t);
extern void ib_offset_calculation(void);
extern void ib_offset_compensation(void);
extern uint16_t ib_read_rx_buffer(uint8_t);

// Temporary debug function
extern void ib_debug_fake_data(void);



// Global shared variables
extern volatile uint16_t ib_discretes;

#endif

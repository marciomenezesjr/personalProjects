#ifndef DEVICE_H_
#define DEVICE_H_

// Includes
#include <msp430.h>
#include <stdint.h>
#include "Interface_Board_Routines.h"

// Defines
#define True		0x01
#define False		0x00

// Output Definitions
#define OUTPUT_PORT	P2DIR
#define OUTPUT_OUT	P2OUT
#define OUTPUT_REN	P2REN
#define OUTPUT_IN	P2IN
#define RED_BIT		BIT0
#define BLUE_BIT	BIT1
#define GREEN_BIT	BIT2
#define SHDN_BIT	BIT4

#define SOLAR_ON	OUTPUT_OUT |= SHDN_BIT
#define SOLAR_OFF	OUTPUT_OUT &= ~SHDN_BIT
#define SOLAR_STAT	OUTPUT_IN&SHDN_BIT

#define RED_OFF		OUTPUT_OUT |= RED_BIT
#define GREEN_OFF	OUTPUT_OUT |= GREEN_BIT
#define BLUE_OFF	OUTPUT_OUT |= BLUE_BIT
#define RED_ON		OUTPUT_OUT &= ~RED_BIT
#define GREEN_ON	OUTPUT_OUT &= ~GREEN_BIT
#define BLUE_ON		OUTPUT_OUT &= ~BLUE_BIT
#define RED_TG		OUTPUT_OUT ^= RED_BIT
#define GREEN_TG	OUTPUT_OUT ^= GREEN_BIT
#define BLUE_TG		OUTPUT_OUT ^= BLUE_BIT


// Input Definitions
#define INPUT_DIR	P2DIR
#define INPUT_REN	P2REN
#define INPUT_OUT	P2OUT
#define INPUT_IFG	P2IFG
#define INPUT_SEL	P2SEL
#define INPUT_IE	P2IE
#define INPUT_IN	P2IN
#define PGOOD_BIT	BIT5
#define SW_BIT		BIT3
#define DIO1_BIT	BIT6
#define DIO2_BIT	BIT7
#define DIO1_STAT	INPUT_IN&DIO1_BIT
#define DIO2_STAT	INPUT_IN&DIO2_BIT

// I2C Interface
#define I2C_PORT	P1DIR
#define I2C_SEL		P1SEL
#define I2C_SEL2	P1SEL2
#define SDA_BIT		BIT7
#define SCL_BIT		BIT6
#define I2C_RX_IV	USCIAB0RX_VECTOR
#define I2C_TX_IV	USCIAB0TX_VECTOR
#define DATA_READ	0xEA
#define DATA_WRITE	0xAE
#define I2C_BF_SIZE 0x30
#define I2C_R_BYTES 0x08
#define IB_I2C_ADDR 0x24
#define SHORT_BYTES 0x02
#define LONG_BYTES  0x04

// ADC
#define IOSENSE 	0x0B
#define VOSENSE 	0x0A
#define IISENSE 	0x09
#define VISENSE 	0x08
#define LIGHT		0x07
#define TEMP		0x06
#define INT_TEMP	0x01
#define VSYS		0x00
#define ADC_SIZE	0x0C
#define V_REF		2.5
#define V_REF_MV	2500.0
#define ADC_25T30	0x01BD
#define ADC_25T85	0x020F
#define ADC_25VREF	0x7FE7



// Function prototypes
extern void device_init(void);
extern void device_adc_init(void);
extern void device_i2c_init(void);

extern void device_load_nvm(void);
extern void device_save_nvm(void);
extern void device_input_init(void);
extern void device_output_init(void);
extern void device_clock_init(void);
extern void device_sample_adc(void);
extern void device_os_timer_init(void);
extern void device_os_timer_stop(void);
extern void device_os_timer_start(void);

extern void device_i2c_rx_buffer(void);
extern void device_i2c_tx_buffer(void);

// Global shared variables
extern uint8_t cmd_idx;
extern uint32_t frame_counter;
extern uint16_t adc_buffer[];

extern uint8_t i2c_tx_buffer[];
extern uint8_t i2c_rx_buffer[];

#endif

#include "Device.h"

uint16_t adc_buffer[ADC_SIZE];
uint8_t cmd_idx = 0x00;
uint32_t frame_counter = 0;

uint8_t i2c_tx_buffer[I2C_BF_SIZE];
uint8_t i2c_rx_buffer[I2C_R_BYTES];

uint8_t RPT_Flag = 0;
uint8_t TXByteCtr = 0;
uint8_t RXByteCtr = 0;
uint8_t *PTxData;                     // Pointer to TX data
uint8_t *PRxData;                     // Pointer to RX data
uint8_t i2c_rx_flag = False;
uint8_t i2c_tx_flag = False;

void device_init(void){
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	device_clock_init();
	device_input_init();
	device_output_init();
	device_load_nvm();
	device_adc_init();
	device_i2c_init();
	device_os_timer_init();
	__enable_interrupt();
}

void device_os_timer_init(void){
	TA0CTL = TASSEL_2 + ID_1;
	TA0CCR0 = TIMER_CCR0;
	TA0CCTL0 = CCIE;
}

void device_os_timer_start(void){
	TA0CTL |= MC_1 + TACLR;
}

void device_os_timer_stop(void){
	TA0CTL &= ~MC_1;
}

void device_clock_init(void){
	if(CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF){
	    while(1);                               // If calibration constants erased, do not load, trap CPU!
	}
	if(SYSTEM_MCLK == __1MHz__){
		BCSCTL1 = CALBC1_1MHZ;                    // Set range
		DCOCTL = CALDCO_1MHZ;                     // Set DCO step + modulation
	}
	else if(SYSTEM_MCLK == __8MHz__){
		BCSCTL1 = CALBC1_8MHZ;
		DCOCTL = CALDCO_8MHZ;
	}
	else if(SYSTEM_MCLK == __12MHz__){
		BCSCTL1 = CALBC1_12MHZ;
		DCOCTL = CALDCO_12MHZ;
	}
	else if(SYSTEM_MCLK == __16MHz__){
		BCSCTL1 = CALBC1_16MHZ;
		DCOCTL = CALDCO_16MHZ;
		BCSCTL2 = DIVS_1;
	}
	else{
		while(1);
	}
}

void device_load_nvm(void){
	__no_operation();
}

void device_save_nvm(void){
	__no_operation();
}

void device_adc_init(void){
	ADC10CTL1 = INCH_11 + CONSEQ_1 + SHS_0 + ADC10SSEL_3;           // A0 through A11, single sequence
	ADC10CTL0 = ADC10SHT_3 + MSC + ADC10ON + ADC10IE + REFON + SREF_1 + REF2_5V;
	ADC10DTC1 = 0x0C;                         						// 11 conversions
	ADC10AE0 |= 0x3F;                         						// Selects channels A0 through A5
}

void device_i2c_init(void){
	I2C_SEL  |= SDA_BIT + SCL_BIT;
	I2C_SEL2 |= SDA_BIT + SCL_BIT;

	IE2 &= ~(UCB0TXIE + UCB0RXIE);
	IFG2 &= ~(UCB0TXIFG + UCB0RXIFG);
	UCB0CTL1 |= UCSWRST;                   	// Enable SW reset
	UCB0CTL0 = UCMODE_3 + UCSYNC;  			// I2C slave, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;         	// Use SMCLK, keep SW reset
	UCB0I2COA = IB_I2C_ADDR;          		// Slave Address is 048h
	UCB0CTL1 &= ~UCSWRST;                  	// Clear SW reset, resume operation
	UCB0I2CIE |= UCSTPIE + UCSTTIE;         // Enable STT and STP interrupt
	IE2 |= UCB0RXIE + UCB0TXIE;         	// Enable Tx/RX interrupt
}

void device_input_init(void){
	INPUT_DIR &= ~(PGOOD_BIT + SW_BIT + DIO1_BIT + DIO2_BIT);
	INPUT_SEL &= ~(DIO1_BIT + DIO2_BIT);
	INPUT_REN |= PGOOD_BIT + SW_BIT + DIO1_BIT + DIO2_BIT;			// Enables internal resistor
	INPUT_OUT |= PGOOD_BIT + SW_BIT + DIO1_BIT + DIO2_BIT;			// Pull-up configuration
	INPUT_IFG = 0x00;
	INPUT_IE  |= SW_BIT;											// Enables pin interrupt
}

void device_output_init(void){
	OUTPUT_PORT |= RED_BIT + GREEN_BIT + BLUE_BIT;
	OUTPUT_PORT &= ~SHDN_BIT;
	OUTPUT_REN |= SHDN_BIT;
	RED_OFF;
	GREEN_OFF;
	BLUE_OFF;
	SOLAR_OFF;
	// To be removed
	INPUT_REN  &= ~(DIO1_BIT + DIO2_BIT);
	INPUT_IE  &= ~(DIO1_BIT + DIO2_BIT);
	INPUT_DIR |= DIO1_BIT + DIO2_BIT;
	INPUT_OUT &= ~(DIO1_BIT + DIO2_BIT);
}

void device_sample_adc(void){
	ADC10CTL0 &= ~ENC;
	ADC10SA = (uint16_t)&adc_buffer;		// Data buffer start
	ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	__bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
	while(ADC10CTL1&ADC10BUSY);
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
	__bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

#pragma vector=I2C_RX_IV
__interrupt void I2C_RX_IV_ISR(void)
{
	UCB0STAT &= ~(UCSTPIFG + UCSTTIFG);       		// Clear interrupt flags
	if(UCB0CTL1&UCTR){
		PTxData = (uint8_t *)i2c_tx_buffer;      	// TX array start address
		if(TXByteCtr){                            	// Check RX byte counter
			//__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0 if data was
		}
	}
	else{
		PRxData = (uint8_t *)i2c_rx_buffer;      	// RX array start address
		if(RXByteCtr){                           	// Check TX byte counter
			//__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0 if data was transmitted
		}
	}
}

#pragma vector=I2C_TX_IV
__interrupt void I2C_TX_IV_ISR(void)
{
	if(!(UCB0CTL1&UCTR)){
		*PRxData++ = UCB0RXBUF;                   	// Move RX data to address PRxData
		RXByteCtr++;                              	// Increment RX byte count
		TRIGGER_UPDATE;
	}
	else{
		UCB0TXBUF = *PTxData++;                   	// Transmit data at address PTxData
		TXByteCtr++;                      			// Increment TX byte counter
	}
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	__bic_SR_register_on_exit(LPM0_bits); 			// Exit the LPM mode
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void){
	TRIGGER_SW;
	if(P2IFG&SW_BIT)
		TRIGGER_CAL;
	INPUT_IFG &= ~(DIO1_BIT + DIO2_BIT + SW_BIT);
}

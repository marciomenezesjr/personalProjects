#include "HAL_device.h"

uint32_t os_timer_overflow = 0;
uint8_t us_delay_lock = false;

void device_startup(){
	device_clk_init();
	os_timer_init();
	board_init();
	__enable_interrupt();
}

// MCLK = 24 MHz and SMCLK = 12MHz
static void device_clk_init(void){
	PJSEL0 |= BIT4 + BIT5;

	CSCTL0_H = 0xA5;
	CSCTL1 |= DCORSEL + DCOFSEL0 + DCOFSEL1;             	// Set max. DCO setting
	CSCTL2 = SELA_0 + SELS_3 + SELM_3;        				// set ACLK = XT1; MCLK = DCO
	CSCTL3 = DIVA_0 + DIVS_3 + DIVM_0;        				// set all dividers
	CSCTL4 |= XT1DRIVE_0;
	CSCTL4 &= ~XT1OFF;
}

static void board_init(void){
	LED_DIR |= RED + GREEN + BLUE;
	LED_REN |= RED + GREEN + BLUE;
	PWR_DIR |= RF_PWR_BIT + SENS_PWR_BIT;
	EN_RF;
	EN_SENS;
	RED_OFF;
	GREEN_OFF;
	BLUE_OFF;

	ACCEL_SA0_CFG;
	ACCEL_SA0_LO;

	MINT_DIR &= ~MINT_BIT;
	MINT_IFG &= ~MINT_BIT;
	MINT_IES &= ~MINT_BIT;
	MINT_IE &= ~MINT_BIT;

	TEST_DIR |= TEST_BIT;
	TEST_OFF;
}

static void os_timer_init(void){
	float tmp;
	tmp = (float)(ACLK_CLK)*((float)OS_TIMER_PERIOD/1000.0);
	TA0CCTL0 = CCIE;                	// CCR0 interrupt enabled
	TA0CCR0 = tmp;
	TA0CTL = TASSEL_1 + TACLR;			// SMCLK, contmode, clear TAR

}

void os_timer_start(void){
	TA0CTL |= MC_1;
}

void os_timer_stop(void){
	TA0CTL &= ~MC_1;
}

void os_usdelay_timer_init(uint16_t delay){
	delay = 12*delay;
	us_delay_lock = true;
	TB0CCTL0 = CCIE;                	// CCR0 interrupt enabled
	TB0CCR0 = delay;
	TB0CTL = TBSSEL_2 + TACLR;			// SMCLK, contmode, clear TAR
	TB0CTL |= MC_1;
	us_delay_lock = true;
	__bis_SR_register(LPM0_bits + GIE);
	while(us_delay_lock);
	TB0CTL &= ~MC_1;
}

void sensors_reset(void){
	DIS_SENS;
	DIS_RF;
	__delay_cycles(240000);
	EN_SENS;
	EN_RF;
	__delay_cycles(240000);
}


// Perform global data initialization
#pragma NOINIT(SysRstIv);
unsigned int SysRstIv;
int _system_pre_init(void){
	WDTCTL = WDTPW + WDTHOLD;				// stop WDT
	SysRstIv = SYSRSTIV;					// save reset information
	return 1;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void OS_TIMER_ISR(void)
{
	__bic_SR_register_on_exit(LPM0_bits);
	os_timer_overflow++;
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void us_TIMER_ISR(void)
{
	__bic_SR_register_on_exit(LPM0_bits);
	us_delay_lock = false;
}

#pragma vector=PORT3_VECTOR
__interrupt void PORT3_ISR(void)
{
	// ISR for Magnetometer Interruption
	if(MINT_IFG&MINT_BIT){
		MINT_IFG &= ~MINT_BIT;
		__bic_SR_register_on_exit(LPM0_bits);
	}

	// ISR for GDO0
	else
		MRFI_GpioIsr();
}


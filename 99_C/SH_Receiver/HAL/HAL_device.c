#include "HAL_device.h"

uint32_t os_timer_overflow = 0;
uint8_t us_delay_lock = false;

void device_startup(){
	device_clk_init();
	os_timer_init();
	hal_board_init();
	__enable_interrupt();
}

// MCLK = 12MHz
static void device_clk_init(void){
	P5SEL |= BIT4 + BIT5;              	// Port select XT1
	UCSCTL6 &= ~XT1OFF;            		// Set XT1 On
	UCSCTL6 |= XCAP_3;             		// Internal load cap
	UCSCTL3 |= SELREF_2;          		// Set DCO FLL reference = REFO
	UCSCTL4 |= SELA_0;            		// Set ACLK = REFO

	__bis_SR_register(SCG0);        	// Disable the FLL control loop
	UCSCTL0 = 0x0000;                  	// Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_5;              	// Select DCO range 24MHz operation
	UCSCTL2 = FLLD_1 + 374;           	// Set DCO Multiplier for 12MHz
										// (N + 1) * FLLRef = Fdco
										// (374 + 1) * 32768 = 12MHz
										// Set FLL Div = fDCOCLK/2
	__bic_SR_register(SCG0);          	// Enable the FLL control loop

	// Worst-case settling time for the DCO when the DCO range bits have been
	// changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
	// UG for optimization.
	// 32 x 32 x 12 MHz / 32,768 Hz = 375000 = MCLK cycles for DCO to settle
	__delay_cycles(375000);

	// Loop until XT1,XT2 & DCO fault flag is cleared
	do{
		UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
										// Clear XT2,XT1,DCO fault flags
		SFRIFG1 &= ~OFIFG;           	// Clear fault flags
	}while(SFRIFG1&OFIFG);           	// Test oscillator fault flag
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



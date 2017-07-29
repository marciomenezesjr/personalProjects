/*
 * systemToolbox.c
 *
 *  Created on: 20.05.2017
 *      Author: marcio
 */

// Includes
#include "systemToolbox.h"

// Local methods
static bool sysSetupClocks(uint32_t mclkFreq, uint8_t smclkFreq, bool extREF);
static bool sysSetupOsTimers();
static void systemInitGPIO(void);
static void sysDisableUSB(void);


// Global shared variables
volatile uint32_t globalTimeMs = 0;
volatile uint32_t wakeMeUpAt = 0;
uint32_t clockValue = 0;
uint8_t clockInitStatus = 0;
volatile bool forceEnable = FALSE;

uint8_t sysInit(){
    systemInitGPIO();                                   // Default initialization for all GPIO pins, to ensure low power consumption
    PMM_setVCore(PMM_CORE_LEVEL_3);                     // Minimum Vcore setting required for the USB API is PMM_CORE_LEVEL_2
    sysSetupClocks(25000000, DIVM__1, FALSE);           // Initialize system clocks
    sysSetupOsTimers();                                 // Initialize global time reference

    USB_setup(TRUE, TRUE);                              // Init USB & events; if a host is present, connect
    __delay_cycles(25000000);							// This delay is necessary to allow the USB to be correctly enumerated on startup sequence

    return 0;
}

// Read the value of the global timer reference
uint32_t sysGetGTime(){
    return globalTimeMs;
}

// Efficiently generates a delay putting the MCU on sleep mode while waiting (__delay_cycles will waste energy)
void sysDelayMs(uint16_t delay){
    wakeMeUpAt = sysGetGTime() + delay;
    __bis_SR_register(LPM0_bits + GIE);
}


// Routine to disable the USB peripheral, used only for power consumption evaluation
static void sysDisableUSB(void){
    // Disable VUSB LDO and SLDO
    USBKEYPID   =     0x9628;           // set USB KEYandPID to 0x9628
                                        // access to USB config registers enabled
    USBPWRCTL &= ~(SLDOEN+VUSBEN);      // Disable the VUSB LDO and the SLDO
    USBKEYPID   =    0x9600;            // access to USB config registers disabled

    // Disable SVS
    PMMCTL0_H = PMMPW_H;                // PMM Password
    SVSMHCTL &= ~(SVMHE+SVSHE);         // Disable High side SVS
    SVSMLCTL &= ~(SVMLE+SVSLE);         // Disable Low side SVS
}

// Initializes the timer used to generate the time reference used on the application
static bool sysSetupOsTimers(){
    //Start timer in continuous mode sourced by SMCLK
    Timer_A_initContinuousModeParam initContParam = {0};
    initContParam.clockSource = TIMER_A_CLOCKSOURCE_ACLK;
    initContParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    initContParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    initContParam.timerClear = TIMER_A_DO_CLEAR;
    initContParam.startTimer = false;
    Timer_A_initContinuousMode(TIMER_A1_BASE, &initContParam);

    //Initiaze compare mode
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    Timer_A_initCompareModeParam initCompParam = {0};
    initCompParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0;
    initCompParam.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;
    initCompParam.compareOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    initCompParam.compareValue = OS_TIMER_REFERENCE;
    Timer_A_initCompareMode(TIMER_A1_BASE, &initCompParam);

    Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_CONTINUOUS_MODE);
    __bis_SR_register(GIE);

    return true;
}

// System clock configuration
static bool sysSetupClocks(uint32_t mclkFreq, uint8_t smclkDivider, bool extREF){
    volatile bool returnValue;

    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN4 + GPIO_PIN5);            // Port select XT1
    UCS_setExternalClockSource(UCS_XT1_CRYSTAL_FREQUENCY, UCS_XT2_CRYSTAL_FREQUENCY);           // Initializes the XT1 and XT2 crystal frequencies being used
    returnValue = UCS_turnOnLFXT1WithTimeout(UCS_XT1_DRIVE_0, UCS_XCAP_3, UCS_XT1_TIMEOUT);     // Initialize XT1. Returns STATUS_SUCCESS if initializes successfully
    UCS_initClockSignal(UCS_ACLK, UCS_XT1CLK_SELECT, UCS_CLOCK_DIVIDER_1);

    if(extREF){																					// In case the external HF crystal is to be used as reference to the FLL	
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN2 + GPIO_PIN3);        // Port select XT2
        returnValue = UCS_turnOnXT2WithTimeout(UCS_XT2_DRIVE_4MHZ_8MHZ, UCS_XT2_TIMEOUT);       // Initialize XT2. Returns STATUS_SUCCESS if initializes successfully

        UCS_initClockSignal(UCS_SMCLK, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_4);

        // Initialize MCLK, being XT2 the reference for the FLL
        UCS_initClockSignal(UCS_FLLREF, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_1);
        UCS_initFLLSettle(mclkFreq/1000, mclkFreq / UCS_XT2_CRYSTAL_FREQUENCY);
    }
    else{																						// Otherwise use the DCO as reference	
        UCS_initClockSignal(UCS_SMCLK, UCS_DCOCLK_SELECT, smclkDivider);
        UCS_initClockSignal(UCS_FLLREF, UCS_REFOCLK_SELECT, UCS_CLOCK_DIVIDER_1);
        UCS_initFLLSettle(mclkFreq/1000, mclkFreq / 32768);
    }

    // Enable global oscillator fault flag
    SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
    SFR_enableInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

    // Enable global interrupt
    __bis_SR_register(GIE);

    //Verify if the Clock settings are as expected
    clockValue = UCS_getMCLK();
    clockValue = UCS_getACLK();
    clockValue = UCS_getSMCLK();

    return true;
}

// Initialize all GPIOs as output low, to avoid unnecessary current leakage
static void systemInitGPIO(void){
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_ALL);

    GPIO_setOutputLowOnPin(GPIO_PORT_PJ, GPIO_ALL);
    GPIO_setAsOutputPin(GPIO_PORT_PJ, GPIO_ALL);

    // TODO: port this piece of code to use the GPIO API
    P1DIR &= ~BIT1;
    P1REN |= BIT1;                            // Enable P1.4 internal resistance
    P1OUT |= BIT1;                            // Set P1.4 as pull-Up resistance
    P1IES |= BIT1;                            // P1.4 Hi/Lo edge
    P1IFG &= ~BIT1;                           // P1.4 IFG cleared
    P1IE |= BIT1;                             // P1.4 interrupt enabled
}

// Oscillator failure interrupt service routine
#pragma vector=UNMI_VECTOR
__interrupt
void NMI_ISR(void)
{
    do{
        // If it still can't clear the oscillator fault flags after the timeout,
        // trap and wait here.
        clockInitStatus = UCS_clearAllOscFlagsWithTimeout(1000);
    }
    while(clockInitStatus != 0);
}

// global timer reference, every 1ms globalTimeMs is incremented 
#pragma vector=TIMER1_A0_VECTOR
__interrupt
void TIMER1_A0_ISR(void)
{
    uint16_t compVal = Timer_A_getCaptureCompareCount(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0) + OS_TIMER_REFERENCE;
    globalTimeMs += 1;
    //Add Offset to CCR0
    Timer_A_setCompareValue(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0, compVal);
    if(globalTimeMs >= wakeMeUpAt){
        __bic_SR_register_on_exit(LPM0_bits);
    }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt
void Port_1(void)
{
    forceEnable = !forceEnable;				// The user switch is configured to force the spy to connect, even if the GUI has not enabled it
    __delay_cycles(10000000);
    P1IFG &= ~BIT1;
}

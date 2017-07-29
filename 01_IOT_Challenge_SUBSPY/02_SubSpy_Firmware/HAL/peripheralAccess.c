/*
 * spi.h
 *
 *  Created on: 20.05.2017
 *      Author: marcio
 */

// Include section
#include "peripheralAccess.h"

// Define section
#define SPICLK                          1000000

// Global variables
volatile uint8_t received = 0x00;
volatile uint8_t pinInterrupt = false;
volatile uint8_t intCounter = 0x00;
uint8_t returnValue = 0x00;

// SPI interface initialization
void spiInit(void){
    // P3.3 is used for slave reset. Reset sequence = GND -> VCC (100us) -> GND
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN3);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);

    // Slave Select pin
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);

    // Pin function selection
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN0 + GPIO_PIN1 + GPIO_PIN2);

    //Initialize Master
    USCI_B_SPI_initMasterParam param = {0};
    param.selectClockSource = USCI_B_SPI_CLOCKSOURCE_SMCLK;
    param.clockSourceFrequency = UCS_getSMCLK();
    param.desiredSpiClock = SPICLK;
    param.msbFirst = USCI_B_SPI_MSB_FIRST;
    param.clockPhase = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
    param.clockPolarity = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
    returnValue = USCI_B_SPI_initMaster(USCI_B0_BASE, &param);

    if(returnValue == STATUS_FAIL){
        return;
    }

    //Enable SPI module
    USCI_B_SPI_enable(USCI_B0_BASE);

    //Enable Receive interrupt
    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);
    USCI_B_SPI_clearInterrupt(USCI_B0_BASE, USCI_B_SPI_TRANSMIT_INTERRUPT);
    USCI_B_SPI_enableInterrupt(USCI_B0_BASE, USCI_B_SPI_RECEIVE_INTERRUPT);

    //Now with SPI signals initialized, reset slave
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN3);
    sysDelayMs(1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);

    //Wait for slave to initialize
    sysDelayMs(10);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);

    // enable interrupts
    __bis_SR_register(GIE);

}

// Write the SPI register at address (addr) with the content of (txData)
void spiWriteReg(uint8_t addr, uint8_t txData){
    spiSlaveEnable();
    spiTransmitByte(addr | 0x80);
    spiTransmitByte(txData);
    spiSlaveDisable();
}

// Read the SPI register specified by (addr)
uint8_t spiReadReg(uint8_t addr){
    spiSlaveEnable();
    spiTransmitByte(addr & 0x7F);
    spiTransmitByte(0x00);                          // Dummy write to pump out clock and read in data
    spiSlaveDisable();
    return USCI_B_SPI_receiveData(USCI_B0_BASE);
}

// Transmit a single byte on SPI bus
void spiTransmitByte(uint8_t byte){
    USCI_B_SPI_transmitData(USCI_B0_BASE, byte);
    while(USCI_B_SPI_isBusy(USCI_B0_BASE));
}

//Receive a single byte from the SPI bus
uint8_t spiReceiveByte(uint8_t byte){
    spiTransmitByte(byte);                          // Dummy write to pump out clock and read in data
    return USCI_B_SPI_receiveData(USCI_B0_BASE);
}

// Enable the SPI slave through the CS pin
void spiSlaveEnable(void){
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
}

// Disable the SPI slave through the CS pin
void spiSlaveDisable(void){
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
}

// Set pin as input
void gpioSetAsInputPin(uint8_t port, uint16_t pin){
    GPIO_setAsInputPin(port, pin);
}

// Enable pin interrupt
void gpioEnablePinInterrupt(uint8_t port, uint16_t pin){
    GPIO_enableInterrupt(port, pin);
}

// Disable pin interrupt
void gpioDisablePinInterrupt(uint8_t port, uint16_t pin){
    GPIO_disableInterrupt(port, pin);
}

// Clear pin interrupt
void gpioClearPinInterrupt(uint8_t port, uint16_t pin){
    GPIO_clearInterrupt(port, pin);
}

// Select pin interrupt edge
void gpioSelectPinInterruptEdge(uint8_t port, uint16_t pin, uint8_t edge){
    GPIO_selectInterruptEdge(port, pin, edge);
}

// Read pin status
uint8_t gpioReadPinStatus(uint8_t port, uint16_t pin){
    return GPIO_getInputPinValue(port, pin);
}


// SPI RX interrupt service routine
// TODO: optimize this interrupt routine
#pragma vector=USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
    switch(__even_in_range(UCB0IV,4)){
    //Vector 2 - RXIFG
    case 2:
        //USCI_A0 TX buffer ready?
        while(!USCI_B_SPI_getInterruptStatus(USCI_B0_BASE, USCI_B_SPI_TRANSMIT_INTERRUPT));
        received = USCI_B_SPI_receiveData(USCI_B0_BASE);

        //Increment data
        intCounter++;

        //Delay between transmissions for slave to process information
        __delay_cycles(400);

        break;
    default: break;
    }
}

// Port 1 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    pinInterrupt = true;							// Signals that a message from the RFM69CW is available
    gpioClearPinInterrupt(GPIO_PORT_P2, GPIO_PIN6);	// Clear interrupt
    __bic_SR_register_on_exit(LPM0_bits);       	// Exit LPM0
}



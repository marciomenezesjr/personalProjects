#ifndef HAL_I2C_H_
#define HAL_I2C_H_

#include <HAL_device.h>


// Defines
#define UCBxCTL0		 UCB0CTLW0		/* USCI Control Register 0 */
#define UCBxCTL1    	 UCB0CTL1		/* USCI Control Register 1 */
#define UCBxBRW     	 UCB0BRW		/* USCI Baud Rate 0 */
#define UCBxSTAT    	 UCB0STAT		/* USCI Status Register */
#define UCBxRXBUF   	 UCB0RXBUF		/* USCI Receive Buffer */
#define UCBxTXBUF   	 UCB0TXBUF		/* USCI Transmit Buffer */
#define UCBxIE 		     UCB0IE 		/* USCI Interrupt Enable Register */
#define UCBxIFG		     UCB0IFG    	/* USCI Interrupt Flags Register */
#define UCBxIV	    	 UCB0IV		    /* USCI Interrupt Vector Register */
#define UCBxRXIE         UCRXIE0
#define UCBxTXIE         UCTXIE0
#define UCBxRXIFG        UCRXIFG0
#define UCBxTXIFG        UCTXIFG0
#define UCBxI2CSA		 UCB0I2CSA
#define USCI_Bx_VECTOR   USCI_B0_VECTOR
// Pin Definitions
#define PxDIR_SDA		 P1DIR
#define PxDIR_SCL		 P1DIR
#define PxOUT_SDA		 P1OUT
#define PxOUT_SCL		 P1OUT
#define PxSEL_SDA		 P1SEL1
#define PxSEL_SCL		 P1SEL1
#define SDA_BIT			 BIT6
#define SCL_BIT 		 BIT7


// I2C Settings for master initialization
//****************************************************************************//
#define 	I2C_SOURCE_CLOCK		0x00	// 0x00 SMCLK or 0x01 ACLK
// Comment out the source clock which will not be used
#define		I2C_SOURCE_CLOCK_FREQ  	3000000
#define		I2C_CLOCK_FREQ			400000
#define 	S_MCLK                  0x00
#define 	RET_OK  1
#define 	RET_ERR 0
//****************************************************************************//


// Global Functions
extern void I2C_Master_Init(uint8_t selectClockSource, uint32_t clockSourceFrequency, uint32_t desiredI2CClock);
extern void I2C_Set_Slave_Address(uint8_t slaveAddress);
extern void I2C_Enable(void);
extern void I2C_Disable(void);
extern void I2C_Set_Mode(uint16_t receive);
extern uint16_t I2C_Bus_Busy(void);
extern uint16_t I2C_Busy(void);
extern void I2C_Interrupt_Enable(uint8_t interruptFlags);
extern void I2C_Interrupt_Disable(uint8_t interruptFlags);
extern void I2C_Interrupt_Clear(uint8_t interruptFlags);
extern unsigned char I2C_Interrupt_Status(uint8_t mask);
extern void I2C_Write_Packet_To_Sensor(uint8_t *writeData, uint8_t dataLength);
extern void I2C_Read_Packet_From_Sensor(uint8_t *readData, uint8_t dataLength);

#endif /*I2C_H_*/


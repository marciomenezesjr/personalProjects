#include "HAL_I2C.h"

// Local Variables
// @brief tx_packet_length is how many bytes of data will be written
uint8_t tx_packet_length;		
// @brief *tx_packet_data will point to the data to be written
uint8_t *tx_packet_data;		

// @brief rx_packet_length is how many bytes of data will be read
uint8_t rx_packet_length;		
// @brief *rx_packet_data will point to the data to be read
uint8_t *rx_packet_data;		

// @brief receive flag is used for the ISR to know the MSP430 will be reading from the 
// CP
uint8_t receive_flag;		
// @brief transmit flag is used for the ISR to know the MSP430 will be writing to the 
// CP
uint8_t transmit_flag;    

// @brief Used to keep track how many bytes have been received
uint8_t rx_byte_ctr;      
// @brief Used to keep track how many bytes have been transmitted
uint8_t tx_byte_ctr;      

/**
* @brief <b>Function Name</b>:     : I2C_Master_Init                                                
* @brief  <b>Description</b>: Initializes the I2C Master Block. Upon succesful
* initialization of the I2C master block, this function will have set the bus
* speed for the master, and will have enabled the SPI Master block.
* @param Input Parameters:
* <BR> uint8_t <b>selectClockSource</b> selects Clock source SMCLK (0x00) 
* or ACLK (0x1)        
* <BR> uint32_t <b>clockSourceFrequency</b> is the frequency of the 
* selected clock source
* <BR> uint32_t <b>desiredI2CClock</b> is the desired clock rate for SPI 
* communication                                 
* @return Return Values: None                                              
**/
void I2C_Master_Init(uint8_t selectClockSource, uint32_t clockSourceFrequency, uint32_t desiredI2CClock){
  // Set-up SDA and SCL pins
  PxSEL_SDA |= SDA_BIT;
  PxSEL_SCL |= SCL_BIT;
  
  // Disable the USCI Module
  I2C_Disable();
  
  // Clock Source
  if(S_MCLK == selectClockSource){
	UCBxCTL1 &= ~UCSSEL_3;
    UCBxCTL1 |= UCSSEL_2; //Select SMCLK
  }

  else{
    // Select ACLK
    UCBxCTL1 |= UCSSEL_1;   
  }
  
  // Set the Baud rate
  UCBxBRW = (unsigned int) (clockSourceFrequency/desiredI2CClock);

  UCBxCTL0 |= UCMST + UCMODE_3 + UCSYNC;
  I2C_Enable();
}

/**
* @brief <b>Function Name</b>:     : I2C_Set_Slave_Address                                               
* @brief  <b>Description</b>: This function will set the address that the I2C 
* Master will place on the bus when initiating a transaction.
* @param Input Parameters:
* <BR> uint8_t <b>slaveAddress</b> is the address of the slave                                                   
* @return Return Values: None                                                    
**/ 
void I2C_Set_Slave_Address(uint8_t slaveAddress){
  // Set the address of the slave with which the master will communicate.
  UCBxI2CSA = slaveAddress;
}

/**
* @brief <b>Function Name</b>:     : I2C_Enable                                                 
* @brief  <b>Description</b>: Enable the I2C block
* @param Input Parameters: None                                                
* @return Return Values: None                                                    
**/ 
void I2C_Enable(void){
  // Reset the UCSWRST bit to enable the USCI Module
  UCBxCTL1 &= ~(UCSWRST);
}

/**
* @brief <b>Function Name</b>:     : I2C_Disable                                                
* @brief  <b>Description</b>: Disable the I2C block
* @param Input Parameters: None                                                
* @return Return Values: None                                                      
**/ 
void I2C_Disable(void){
  UCBxCTL1 |= (UCSWRST);
}

/**
* @brief <b>Function Name</b>:     : I2C_Set_Mode                                                
* @brief  <b>Description</b>: When the receive parameter is set to 0x01, the 
* address will indicate that the I2C module is in receive mode; otherwise, the 
* I2C module is in transmit mode
* @param Input Parameters:
* <BR> uint16_t <b>receive</b> can be set to a 0x01 to be in receive mode,
*  or 0x00 to be in transmit mode                                                   
* @return Return Values: None                                                  
**/ 
void I2C_Set_Mode(uint16_t receive){
  // Disable the USCI module
  UCBxCTL1 |= UCSWRST;
  
  if(receive){
    // Configure in receive mode
    UCBxCTL1 &= ~(UCTR);
  }
  else{
    // Configure in transmit mode
    UCBxCTL1 |= UCTR;
  }
}

/**
* @brief <b>Function Name</b>:     : I2C_Bus_Busy                                                
* @brief  <b>Description</b>: This function returns an indication of whether or 
* not the I2C bus is busy. This function can be used in a multi-master 
* enviroment to determine if another master is currently using the bus. This 
* function checks the status of the bus via UCBBUSY bit in the UCBxSTAT register.
* @param Input Parameters: None                                          
* @return Return Values:
* <BR>Returns 0x01 if the I2C master is busy; otherwise, returns 0x00.                                                    
**/ 
uint16_t I2C_Bus_Busy(void){
  // Return the bus busy status.
  if(UCBxSTAT & UCBBUSY){
      return(RET_OK);
  }
  else{
      return(RET_ERR);
  }
}

/**
* @brief <b>Function Name</b>:     : I2C_Busy                                                
* @brief  <b>Description</b>: This function returns an indication of whether or 
* not the I2C module is busy transmitting or receiving data. This function 
* checks if the transmit or receive flag is set.
* @param Input Parameters: None                                             
* @return Return Values:
* <BR>Returns 0x01 if the I2C master is busy; otherwise, returns 0x00.                                                    
**/ 
uint16_t I2C_Busy(void){
  // Return the busy status.
  if((UCBxIFG & UCBxTXIFG) || (UCBxIFG & UCBxRXIFG)){
      return((uint16_t)RET_OK);
  }
  else{
      return((uint16_t)RET_ERR);
  }
}

/**
* @brief <b>Function Name</b>:     : I2C_Interrupt_Enable                                              
* @brief  <b>Description</b>: Enables Individual I2C interrupts
* @param Input Parameters:
* <BR> uint8_t <b>interruptFlags</b> is the logical OR of any of the 
* following: 
*  <BR> I2C_INT_STOP - STOP condition interrupt
*  <BR> I2C_INT_START - START condition interrupt
*  <BR> I2C_INT_DATA_RX -Receive interrupt
*  <BR> I2C_INT_DATA_TX - Transmit interrupt
*  <BR> I2C_INT_NACK - Not-acknowledge interrupt
*  <BR> I2C_INT_CALIFG - Arbitration lost interrupt                                               
* @return Return Values: None                                                    
**/ 
void I2C_Interrupt_Enable(uint8_t interruptFlags){
  // Enable the interrupt masked bit
  UCBxIE |= interruptFlags;
}

/**
* @brief <b>Function Name</b>:     : I2C_Interrupt_Disable                                           
* @brief  <b>Description</b>: Disables Individual I2C interrupts 
* @param Input Parameters:
* <BR> uint8_t <b>interruptFlags</b> is the logical OR of any of the 
* following: 
*  <BR> I2C_INT_STOP - STOP condition interrupt
*  <BR> I2C_INT_START - START condition interrupt
*  <BR> I2C_INT_DATA_RX -Receive interrupt
*  <BR> I2C_INT_DATA_TX - Transmit interrupt
*  <BR> I2C_INT_NACK - Not-acknowledge interrupt
*  <BR> I2C_INT_CALIFG - Arbitration lost interrupt                                               
* @return Return Values: None                                                 
**/ 
void I2C_Interrupt_Disable(uint8_t interruptFlags){
  // Disable the interrupt masked bit
  UCBxIE &= ~(interruptFlags);
}

/**
* @brief <b>Function Name</b>:     : I2C_Interrupt_Clear                                           
* @brief  <b>Description</b>: Clears Individual I2C interrupts flags 
* @param Input Parameters:
* <BR> uint8_t <b>interruptFlags</b> is the logical OR of any of the 
* following: 
*  <BR> I2C_INT_STOP - STOP condition interrupt
*  <BR> I2C_INT_START - START condition interrupt
*  <BR> I2C_INT_DATA_RX -Receive interrupt
*  <BR> I2C_INT_DATA_TX - Transmit interrupt
*  <BR> I2C_INT_NACK - Not-acknowledge interrupt
*  <BR> I2C_INT_CALIFG - Arbitration lost interrupt                                               
* @return Return Values: None                                                    
**/ 
void I2C_Interrupt_Clear(uint8_t interruptFlags){
  // Clear the I2C interrupt source.
  UCBxIFG &= ~(interruptFlags);
}

/**
* @brief <b>Function Name</b>:     : I2C_Interrupt_Status                                   
* @brief  <b>Description</b>: Returns the interrupt status for the I2C module 
* based on which flag is passed.   
* @param Input Parameters:
* <BR> uint8_t <b>mask</b> is the masked interrupt flag status to be 
* returned. 
*  <BR> I2C_INT_STOP - STOP condition interrupt
*  <BR> I2C_INT_START - START condition interrupt
*  <BR> I2C_INT_DATA_RX -Receive interrupt
*  <BR> I2C_INT_DATA_TX - Transmit interrupt
*  <BR> I2C_INT_NACK - Not-acknowledge interrupt
*  <BR> I2C_INT_CALIFG - Arbitration lost interrupt                                           
* @return Return Values:
* <BR>The current interrupt status, returned as 0x01 if active, otherwise 0x00.                                                    
**/ 
uint8_t I2C_Interrupt_Status(uint8_t mask){
  // Return the interrupt status of the request masked bit.
  return (UCBxIFG & mask);
}

/**
* @brief <b>Function Name</b>:     : I2C_Write_Packet_To_Sensor                                            
* @brief  <b>Description</b>: Sends data packet to sensor
* @param Input Parameters:
* <BR> uint8_t <b>writeData</b> is the pointer to the array which holds the
* the packet to send to the sensor. writeData[0] = register the packet will
* be written to. This function requires the user to have used I2C_Set_Slave_Address(),
* to set the address of the sensor. 
* <BR> uint8_t <b>dataLength</b> is the number of data bytes to be written.
* @return Return Values: None               
**/ 
void I2C_Write_Packet_To_Sensor(uint8_t *writeData, uint8_t dataLength){
  // Assign values to local variables
  tx_packet_length = dataLength;
  tx_packet_data = writeData;
  
  // Reset variables for transmission
  transmit_flag = 1;
  receive_flag = 0;
  tx_byte_ctr = 0;
  rx_byte_ctr = 0;
    
  // Enable TX Interrupt to send write address, register and data
  __bic_SR_register(GIE);
  I2C_Interrupt_Enable(UCBxTXIE);
  I2C_Interrupt_Enable(UCNACKIE);
  UCBxIFG |= UCBxTXIFG;
  
  // Enter Low Power Mode 0
  while(transmit_flag == 1)
    __bis_SR_register(LPM0_bits + GIE);       // CPU off, enable interrupts
}

/**
* @brief <b>Function Name</b>:     : I2C_Read_Packet_From_Sensor                                            
* @brief  <b>Description</b>: Sends data packet to Authentication CP 
* @param Input Parameters:
* <BR> uint8_t <b>readData</b> is the pointer to the array which holds the
* the packet to send to the sensor. readData[0] = register the packet will
* be read from. This function requires the user to have used I2C_Set_Slave_Address(),
* to set the address of the sensor. 
* <BR> uint8_t * <b>readData</b> is the number of data bytes to be read.                                       
* @return Return Values: None                 
**/ 
void I2C_Read_Packet_From_Sensor(uint8_t *readData, uint8_t dataLength){
  // Assign values to local variables
  rx_packet_length = dataLength;
  rx_packet_data = readData;
  
  // Reset variables for transmission
  transmit_flag = 0;
  receive_flag = 1;
  tx_byte_ctr = 0;
  rx_byte_ctr = 0;
  
  // Enable TX Interrupt to send write address, and register
  __bic_SR_register(GIE);
  
  I2C_Interrupt_Enable(UCBxTXIE);
  I2C_Interrupt_Enable(UCNACKIE);
  UCBxIFG |= UCBxTXIFG;
  
  // Enter Low Power Mode 0
  while(receive_flag == 1)
    __bis_SR_register(LPM0_bits + GIE);       	// CPU off, enable interrupts
  
  __delay_cycles(160);                  		// Delay 10 uS
}

#pragma vector = USCI_Bx_VECTOR
__interrupt void USCI_I2C_ISR(void){
  switch(__even_in_range(UCBxIV,0x18)){
  case 0x00: break;                           	// Vector  0: No interrupts
  case 0x02: break;                           	// Vector  2: ALIFG
  case 0x04: 		                          	// Vector  4: NACKIFG
    UCBxCTL1 |= UCTXSTT;						// Re-start condition
    tx_byte_ctr = 0;
    break;
  case 0x06: break;                           	// Vector  6: STTIFG
  case 0x08: break;                           	// Vector  8: STPIFG
  case 0x16: 									// Vector 10: RXIFG
  	if(rx_byte_ctr < rx_packet_length-1){
  	  *rx_packet_data++= UCBxRXBUF;				// Read receive buffer
  	  rx_byte_ctr++;
  	  if(rx_byte_ctr == rx_packet_length-1){
  	  	UCBxCTL1 |= UCTXSTP;                  	// Send I2C stop condition
  	  }
  	}
  	else{
      // Clear RX Flag
      receive_flag = 0;
  	  *rx_packet_data = UCBxRXBUF;
      I2C_Interrupt_Disable(UCNACKIE);
  	  I2C_Interrupt_Disable(UCBxRXIE);
  	  __bic_SR_register_on_exit(LPM0_bits);  	// Exit active CPU
  	}
  	break;                           
  case 0x18:                                  	// Vector 12: TXIFG
   if(transmit_flag){
     if(tx_byte_ctr == 0){
       while (UCBxCTL1 & UCTXSTP);          	// Ensure stop condition got sent
       UCBxCTL1 |= UCTR+UCTXSTT;            	// Send I2C start condition
       tx_byte_ctr++;
     }
     else if(tx_packet_length >= tx_byte_ctr){
       UCBxTXBUF = *tx_packet_data++;    		// Send data bytes
       tx_byte_ctr++;
     }
     else{
       UCBxCTL1 |= UCTXSTP;                  	// Send I2C stop condition
  	   I2C_Interrupt_Disable(UCBxTXIE);		
       I2C_Interrupt_Disable(UCNACKIE);
       transmit_flag = 0;
       __bic_SR_register_on_exit(LPM0_bits);  	// Exit active CPU
     }
   }
   else if(receive_flag){
     if(tx_byte_ctr == 0){
       while (UCBxCTL1 & UCTXSTP);          	// Ensure stop condition got sent
       	   UCBxCTL1 |= UCTR+UCTXSTT;            	// I2C start condition
       tx_byte_ctr++;
     }
     else if(tx_byte_ctr == 1){
	   UCBxTXBUF = rx_packet_data[0];			// Send Register name
	   tx_byte_ctr++;        	
     }
     else if(tx_byte_ctr == 2){
       UCBxCTL1 &= ~(UCTR);						// Enable receive bit
       UCBxCTL1 |= UCTXSTT;            			// Send I2C start condition
       // In the case of reading one byte, poll on start condition bit
       if(rx_packet_length == 1){
    	 // Wait for start condition to be transmitted
  	   	 while(UCBxCTL1 & UCTXSTT);
  	   	 	 UCBxCTL1 |= UCTXSTP;                // Send I2C stop condition
  	   }
       I2C_Interrupt_Enable(UCBxRXIE);		// Enable RX interrupt
  	   I2C_Interrupt_Disable(UCBxTXIE);		// Disable TX interrupt
       tx_byte_ctr++;								     
     }        
   }
   break;                          
  default: break;
  }
}

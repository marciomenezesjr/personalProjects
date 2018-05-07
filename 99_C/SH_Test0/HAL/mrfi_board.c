/**************************************************************************************************
  Filename:       sample.c
  Revised:        $Date: 2007-07-06 11:19:00 -0700 (Fri, 06 Jul 2007) $
  Revision:       $Revision: 13579 $

  Description:    Describe the purpose and contents of the file.


  Copyright 2004-2007 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights granted under
  the terms of a software license agreement between the user who downloaded the software,
  his/her employer (which must be your employer) and Texas Instruments Incorporated (the
  "License"). You may not use this Software unless you agree to abide by the terms of the
  License. The License limits your use, and you acknowledge, that the Software may not be
  modified, copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio frequency
  transceiver, which is integrated into your product. Other than for the foregoing purpose,
  you may not use, reproduce, copy, prepare derivative works of, modify, distribute,
  perform, display or sell this Software and/or its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS”
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
  WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
  IN NO EVENT SHALL TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE
  THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY
  INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST
  DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY
  THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com. 
**************************************************************************************************/

/* ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 *   MRFI (Minimal RF Interface)
 *   Board code file.
 *   Target : Texas Instruments EZ430-RF2500
 *            "MSP430 Wireless Development Tool"
 *   Radios : CC2500
 * ~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
 */

/* ------------------------------------------------------------------------------------------------
 *                                           Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "mrfi_defs.h"

void write_spi_byte(uint8_t data){
	uint16_t backup_0, backup_1, backup_2;

	backup_0 = UCB0CTLW0;
	backup_1 = UCB0BR0;
	backup_2 = UCB0IE;

	UCB0CTLW0 |= UCSWRST;
	UCB0CTLW0 = 0xA980;
	UCB0BR0 = 0x04;
	UCB0TXBUF = data;
	UCA0TXBUF = data;
	UCB0TXBUF = data;
	while(UCB0STATW & UCBUSY);

	UCB0CTLW0 |= UCSWRST;
	UCB0CTLW0 = backup_0;
	UCB0BR0 = backup_1;
	UCB0IE = backup_2;
}

uint8_t read_spi_byte(void){
	uint16_t backup_0, backup_1, backup_2;
	uint8_t data;

	P1SEL0 &= ~(BIT6 + BIT7);
	P1SEL1 &= ~(BIT6 + BIT7);
	P1DIR &= ~(BIT6 + BIT7);
	P1SEL1 |= BIT5;
	backup_0 = UCB0CTLW0;
	backup_1 = UCB0BR0;
	backup_2 = UCB0IE;

	UCB0CTLW0 |= UCSWRST;
	UCB0CTLW0 = 0xA980;
	UCB0BR0 = 0x04;

	UCB0TXBUF = 0xFF;
	data = UCA0TXBUF;
	while(UCB0STATW & UCBUSY);

	P1SEL1 |= BIT6 + BIT7;
	UCB0CTLW0 |= UCSWRST;
	UCB0CTLW0 = backup_0;
	UCB0BR0 = backup_1;
	UCB0IE = backup_2;
	return data;
}


/**************************************************************************************************
 *                                  Compile Time Integrity Checks
 **************************************************************************************************
 */
#include "mrfi_board_defs.h"

#if ( MRFI_GDO0_INT_VECTOR != PORT3_VECTOR )
#error "ERROR:  Mismatch with specified vector and actual ISR."
/*
 *  The most likely fix is to modify the vector in the above ISR.
 *  This compile time check needs updated too.
 */
#endif


/**************************************************************************************************
 */



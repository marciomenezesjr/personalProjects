#ifndef HAL_F5_BOARD_H_
#define HAL_F5_BOARD_H_


// Includes
#include <stdint.h>
#include "HAL_device.h"
#include "bsp_glue.h"

// LED1
#define LED1_BIT		BIT0
#define LED1_OUT		P1OUT
#define LED1_DIR		P1DIR
#define LED1_OFF		LED1_OUT &= ~LED1_BIT
#define LED1_ON			LED1_OUT |= LED1_BIT
#define LED1_TOGGLE		LED1_OUT ^= LED1_BIT
#define LED1_STAT		(LED1_OUT & LED1_BIT)

// LED2
#define LED2_BIT		BIT7
#define LED2_OUT		P4OUT
#define LED2_DIR		P4DIR
#define LED2_OFF		LED2_OUT &= ~LED2_BIT
#define LED2_ON			LED2_OUT |= LED2_BIT
#define LED2_TOGGLE		LED2_OUT ^= LED2_BIT
#define LED2_STAT		(LED2_OUT & LED2_BIT)

// SW1
#define SW1_BIT			BIT1
#define SW1_DIR			P2DIR
#define SW1_PIN			P2IN
#define SW1_IE			P2IE
#define SW1_IFG			P2IFG
#define SW1_IES			P2IES
#define SW1_STAT		!(SW1_PIN & SW1_BIT)
#define SW1_EXT_CFG  	st(P2OUT |= SW1_BIT; P2REN |= SW1_BIT;)

// SW2
#define SW2_BIT			BIT1
#define SW2_DIR			P1DIR
#define SW2_PIN			P1IN
#define SW2_IE			P1IE
#define SW2_IFG			P1IFG
#define SW2_IES			P1IES
#define SW2_STAT		!(SW2_PIN & SW2_BIT)
#define SW2_EXT_CFG  	st(P1OUT |= SW2_BIT; P1REN |= SW2_BIT;)



extern void hal_board_init(void);
extern void leds_init(void);
extern void sws_init(void);

#endif

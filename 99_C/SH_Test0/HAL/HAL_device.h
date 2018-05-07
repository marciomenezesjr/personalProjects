#ifndef HAL_DEVICE_H_
#define HAL_DEVICE_H_

// Includes
#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mrfi.h"

// Defines
#define true 			0x01
#define false 			0x00
#define OS_TIMER_PERIOD 10			// Operating System wake-up period (ms)
#define SYS_CLK			16000000
#define ACLK_CLK		32768

#define LED_DIR			P1DIR
#define LED_OUT			P1OUT
#define LED_REN			P1REN
#define RED				BIT2
#define GREEN			BIT0
#define BLUE			BIT1
#define RED_OFF			LED_OUT |= RED
#define GREEN_OFF		LED_OUT |= GREEN
#define BLUE_OFF		LED_OUT |= BLUE
#define RED_TOGGLE		LED_OUT ^= RED
#define GREEN_TOGGLE	LED_OUT ^= GREEN
#define BLUE_TOGGLE		LED_OUT ^= BLUE
#define RED_ON			LED_OUT &= ~RED
#define GREEN_ON		LED_OUT &= ~GREEN
#define BLUE_ON			LED_OUT &= ~BLUE

#define PWR_DIR			P1DIR
#define PWR_OUT			P1OUT
#define RF_PWR_BIT		BIT3
#define SENS_PWR_BIT	BIT4
#define EN_RF			PWR_OUT |= RF_PWR_BIT
#define EN_SENS			PWR_OUT |= SENS_PWR_BIT
#define DIS_RF			PWR_OUT &= ~RF_PWR_BIT
#define DIS_SENS		PWR_OUT &= ~SENS_PWR_BIT

#define ACCEL_SA0_CFG	P3DIR |= BIT2
#define ACCEL_SA0_LO	P3OUT &= ~BIT2
#define ACCEL_SA0_HI	P3OUT |= BIT2

#define MINT_BIT		BIT3
#define MINT_DIR		P3DIR
#define MINT_IE			P3IE
#define MINT_IFG		P3IFG
#define MINT_IES		P3IES
#define EN_MAG_IR		st(MINT_IE |= MINT_BIT;)
#define DIS_MAG_IR		MINT_IE &= ~MINT_BIT

#define TEST_BIT		BIT4
#define TEST_DIR		P2DIR
#define TEST_OUT		P2OUT
#define TEST_ON			TEST_OUT |= TEST_BIT
#define TEST_OFF		TEST_OUT &= ~TEST_BIT
#define TEST_TOGGLE		TEST_OUT ^= TEST_BIT

#define SMCLK_BIT		BIT0
#define SMCLK_DIR		PJDIR
#define SMCLK_SEL0		PJSEL0
#define EN_SMCLK_OUT	st(SMCLK_DIR |= SMCLK_BIT; SMCLK_SEL0 |= SMCLK_BIT;)
#define DIS_SMCLK_OUT	st(SMCLK_DIR &= ~SMCLK_BIT; SMCLK_SEL0 &= ~SMCLK_BIT;)




// Function Prototypes
extern void os_timer_stop(void);
extern void device_startup(void);
extern void os_timer_start(void);
extern void sensors_reset(void);

extern void os_usdelay_timer_init(uint16_t);

static void board_init(void);
static void os_timer_init(void);
static void device_clk_init(void);



// Global shared variables

#endif







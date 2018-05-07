#ifndef HAL_DEVICE_H_
#define HAL_DEVICE_H_

// Includes
#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "HAL_F5_board.h"

// Defines
#define true 			0x01
#define false 			0x00
#define OS_TIMER_PERIOD 100			// Operating System wake-up period (ms)
#define SYS_CLK			12000000
#define ACLK_CLK		32768


// Function Prototypes
extern void device_startup(void);
extern void os_timer_start(void);
extern void os_timer_stop(void);
extern void os_usdelay_timer_init(uint16_t);

static void os_timer_init(void);
static void device_clk_init(void);



// Global shared variables
extern uint8_t update_screen;
extern uint32_t os_timer_overflow;

#endif







#ifndef BSP_GLUE_H_
#define BSP_GLUE_H_

// Includes
#include <stdint.h>
#include <msp430.h>
#include "HAL_device.h"

// Defines
#define BV(n)      (1 << (n))
#define st(x)      do { x } while (__LINE__ == -1)

// Critical Sections
typedef unsigned short  bspIState_t;

#define BSP_ENTER_CRITICAL_SECTION(x)   st(x = __get_interrupt_state(); __disable_interrupt();)
#define BSP_EXIT_CRITICAL_SECTION(x)    __set_interrupt_state(x)
#define BSP_CRITICAL_STATEMENT(x)       st(bspIState_t s;                    \
                                            BSP_ENTER_CRITICAL_SECTION(s);   \
                                            x;                               \
                                            BSP_EXIT_CRITICAL_SECTION(s);)
#define BSP_ENABLE_INTERRUPTS()         __enable_interrupt()

/*#define __bsp_QUOTED_PRAGMA__(x)	_Pragma(#x)
#define __bsp_ISR_FUNCTION__(f,v)   __bsp_QUOTED_PRAGMA__(vector=v) __interrupt void f(void)
#define BSP_ISR_FUNCTION(func,vect)     __bsp_ISR_FUNCTION__(func,vect)*/

// static assert
#define BSP_STATIC_ASSERT(expr)   void bspDummyPrototype(char dummy[1/((expr)!=0)])
#define BSP_ASSERT_HANDLER()      st(__disable_interrupt();  while(1);)
#define BSP_ASSERT(expr)          st(if (!(expr)) BSP_ASSERT_HANDLER();)


// Little endian
#define   ntohs(x)    (x)
#define   htons(x)    (x)
#define   ntohl(x)    (x)
#define   htonl(x)    (x)

// Function prototypes
extern void BSP_DELAY_USECS(uint16_t);

#endif

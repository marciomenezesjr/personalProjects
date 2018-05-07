#ifndef HAL_SPI_H_
#define HAL_SPI_H_

// Includes
#include "HAL_device.h"


// Defines
#define SPI_DIR		P2DIR
#define SPI_OUT		P2OUT
#define SPI_IN		P2IN
#define SOMI		BIT1
#define SIMO		BIT0
#define SCLK		BIT2
#define SCLK_HI		SPI_OUT |= SCLK
#define SCLK_LO		SPI_OUT &= ~SCLK
#define SIMO_HI		SPI_OUT |= SIMO
#define SIMO_LO		SPI_OUT &= ~SIMO
#define SOMI_STAT	SPI_IN&SOMI

// Function prototypes
extern void sw_spi_init(void);
extern void sw_spi_tx(uint8_t);
extern uint8_t sw_spi_rx(void);

#endif

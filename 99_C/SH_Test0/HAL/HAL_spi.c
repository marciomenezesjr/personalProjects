#include "HAL_spi.h"

uint8_t spi_received_data;

void sw_spi_init(void){
	SPI_DIR |= SIMO + SCLK;
	SPI_DIR &= ~SOMI;
	SCLK_LO;
	SIMO_LO;
}

void sw_spi_tx(uint8_t data){
	uint8_t i;
	spi_received_data = 0;

	SCLK_LO;
	SIMO_LO;
	__delay_cycles(1);

	for(i=0;i<8;i++){
		if(data&BIT7){
			SIMO_HI;
		}
		else{
			SIMO_LO;
		}
		SCLK_HI;
		if(SOMI_STAT){
			spi_received_data |= BIT0;
		}
		SCLK_LO;
		data <<= 1;
		if(i<7)
			spi_received_data <<= 1;
	}

}

uint8_t sw_spi_rx(void){
	return spi_received_data;
}

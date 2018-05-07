#ifndef INTERFACE_BOARD_TIME_H_
#define INTERFACE_BOARD_TIME_H_


// System Clock Definitions
#define __1MHz__		1000000
#define __8MHz__		8000000
#define __12MHz__		12000000
#define __16MHz__		16000000
#define SYSTEM_MCLK		__16MHz__				// System Main Clock (Hz) = __8MHz__, Options are __1MHz__, __8MHz__, __12MHz__ and __16MHz__
#define SYSTEM_SMCLK	SYSTEM_MCLK/2			// System Secondary Clock used for ADC and Timer = MCLK/2 for __16MHz__ and equal to MCLK for other frequencies


// OS Timer Defines
#define OS_TMR_CLK		SYSTEM_SMCLK/2			// Timer clock uses SMCLK which is equal to MCLK and is divided by 2 by the Input Divider
#define FRAME_RATE		200						// Application frame rate in Hz
#define TIMER_CCR0		OS_TMR_CLK/FRAME_RATE


// ADC Filter Defines
#define SAMPLE_FREQ		FRAME_RATE
#define SPV				16						// Number of samples per value
#define SPV_SHIFT		4						// Division by 16
#define AVG_TIME		0.1						// Average time window in seconds
#define AVG_FRAMES		FRAME_RATE*AVG_TIME		// Number of samples taken for average calculation


// MPPT Algorithm Defines
#define MPPT_SAMPLES	0x16


// Offset Calculation Algorithm Defines
#define OFFSET_SAMPLES	500


#endif

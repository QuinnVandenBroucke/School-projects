/*
 * led_driver.c
 *
 *  Created on: 19 okt. 2020
 *      Author: quinn
 */

//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "led_driver.h"


//	----------------------------------------------------------------------------
//	ADDITIONAL INFORMATION
//	----------------------------------------------------------------------------

// BLUE  LED: 25 -> PWM 1.2 (p2.1)
// GREEN LED: 24 -> PWM 1.3 (p2.2)
// RED   LED: 23 -> PWM 1.4 (p2.3)


//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------
void led_driver_init(void) {

	const float PCLK = (SystemCoreClock / 4);
	const float PWMfreq = 100000.0;

	// Give power to the PWM
	// Default to 1 but just in case
	LPC_SC->PCONP |= (1 << 6);


	// Peripheral clock for the PWM (CCLK / 4 = 25MHz)
	//	It defaults to 0 but just in case
	LPC_SC->PCLKSEL0 &= ~(3 << 12);


	// Select the PWM pins
	// ```````````````````
	// Blue
	LPC_PINCON->PINSEL4 |= (1 << 2);
	// Green
	LPC_PINCON->PINSEL4 |= (1 << 4);
	// Red
	LPC_PINCON->PINSEL4 |= (1 << 6);


	// Set the PWM to single edge
	// ``````````````````````````
	// Blue
	LPC_PWM1->PCR &= ~(1 << 2);
	// Green
	LPC_PWM1->PCR &= ~(1 << 3);
	// Red
	LPC_PWM1->PCR &= ~(1 << 4);


	// Enable the PWM output
	// `````````````````````
	// Blue
	LPC_PWM1->PCR |= (1 << 10);
	// Green
	LPC_PWM1->PCR |= (1 << 11);
	// Red
	LPC_PWM1->PCR |= (1 << 12);


	// We want a PWM resolution of 100 (by setting the PR register)
	// PWMres = PCLK / (PR + 1)  with PWMfreq = 100kHz
	LPC_PWM1->PR = (PCLK / PWMfreq) - 1;


	// PWM Period
	LPC_PWM1->MR0 = 100;


	// Load the MR0 value
	LPC_PWM1->LER |= 1;


	// Reset the counter if TC matches MR0
	LPC_PWM1->MCR |= (1 << 1);


	// Enable the counter
	LPC_PWM1->TCR |= 1;


	// Enable the PWM
	LPC_PWM1->TCR |= (1 << 3);


	printf("LED initialized\n");
}

void led_driver_setValue(uint8_t red, uint8_t green, uint8_t blue) {

	if (red > 100) {
		red = 100;
	}
	if (green > 100) {
		green = 100;
	}
	if (blue > 100) {
		blue = 100;
	}

	LPC_PWM1->MR2  = 100 - blue;
	LPC_PWM1->LER |= (1 << 2);

	LPC_PWM1->MR3  = 100 - green;
	LPC_PWM1->LER |= (1 << 3);

	LPC_PWM1->MR4  = 100 - red;
	LPC_PWM1->LER |= (1 << 4);
}

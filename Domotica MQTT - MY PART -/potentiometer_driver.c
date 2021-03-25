/*
 * potentiometer_driver.c
 *
 *  Created on: 5 okt. 2020
 *      Author: quinn
 */


//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "potentiometer_driver.h"


//	----------------------------------------------------------------------------
//	GLOBAL VARIABLES
//	----------------------------------------------------------------------------
uint8_t conversion_done;
uint16_t adc_value;


//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------

void pot_init(void){
	//	Enable power for the ADC
	LPC_SC->PCONP |= (1 << 12);


	//	Enable the ADC
	LPC_ADC->ADCR |= (1 << 21);


	//	Select the peripheral clock for the ADC (CCLK / 4 = 25MHz)
	//	It defaults to 0 but just in case
	LPC_SC->PCLKSEL0 &= ~(3 << 24);


	//	Set the clock divider
	//	The clock has to be less than 13MHz
	//	ADC CLK = PCLK / (CLKDIV + 1) = 25MHz / 2 = 12.5MHz
	LPC_ADC->ADCR |= (1 << 8);


	//	Configure pin AD0.4
	LPC_PINCON->PINSEL3 |= (3 << 28);


	//	Select AD0.4
	LPC_ADC->ADCR |= (1 << 4);


	//	Disable interrupts on AD0.4
	//	It defaults to 0 but just in case
	LPC_ADC->ADINTEN &= ~(1 << 4);


	printf("Potentiometer initialized\n");
}

uint8_t pot_getValue (void){
	//	Start the ADC conversion
	LPC_ADC->ADCR |= (1 << 24);

	conversion_done = 0;
	while(!conversion_done){
		//	Busy waiting
		conversion_done = (LPC_ADC->ADGDR >> 31) & 1;
	}
	//	Read the AD0.4 Register
	adc_value = LPC_ADC->ADDR4;
	adc_value = (uint8_t)(((float)adc_value/65536.0)*100);

	return adc_value;
}

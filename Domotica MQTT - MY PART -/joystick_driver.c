/*
 * joystick_driver.c
 *
 *  Created on: 12 okt. 2020
 *      Author: quinn
 */


//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "joystick_driver.h"



//	----------------------------------------------------------------------------
//	GLOBAL VARIABLES
//	----------------------------------------------------------------------------
uint8_t joystick_pressed = 0;



//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------

void joy_init(void) {

	//	Select the GPIO function
	//	It defaults to 0 but just in case
	LPC_PINCON->PINSEL1 &= ~(1 << 0);


	//	Set the GPIO to be an input
	// 	It defaults to 0 but just in case
	LPC_GPIO0->FIODIR &= ~(1 << 16);


	//	Enable the pull down for 0.16
	LPC_PINCON->PINMODE1 |= 3;


	//	Enable interrupt on the rising edge of GPIO 0.16
	LPC_GPIOINT->IO0IntEnR |= (1 << 16);


	//	Enable general interrupts. All the GPIO interrupts are connected
	//	to EINT3 so this one needs to be turned on in order to use GPIO interr.
	NVIC_EnableIRQ(EINT3_IRQn);


	printf("Joystick initialized!\n");
}


uint8_t joy_getValue(void) {
	uint8_t joy_Value = LPC_GPIO0->FIOPIN2;
	return joy_Value;
}


void EINT3_IRQHandler() {
	//	Debouncing
	timer_wait_ms(250);

	//	Check if the interrupt happened on p0.16
	if (((LPC_GPIOINT->IO0IntStatR >> 16) & 1) == 1) {

		//	Set the bool
		joystick_pressed = 1;

		//	Clear the interrupt & read him to make sure he's cleared
		LPC_GPIOINT->IO0IntClr = (1 << 16);
		assert(LPC_GPIOINT->IO0IntClr == 0);
	}

}


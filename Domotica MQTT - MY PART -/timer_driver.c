/*
 * wait.c
 *
 *  Created on: 19 nov. 2020
 *      Author: quinn
 */


//	----------------------------------------------------------------------------
//	INCLUDES
//	----------------------------------------------------------------------------
#include "timer_driver.h"


//	----------------------------------------------------------------------------
//	GLOBAL VARIABLES
//	----------------------------------------------------------------------------
uint8_t timer_interrupt_happend = 0;


//	----------------------------------------------------------------------------
//	FUNCTIONS
//	----------------------------------------------------------------------------

void timer_wait_us(uint16_t microseconds)
{

	//	Get the clock (CCLK / 4)
	uint32_t PCLK = SystemCoreClock / 4;

	//	Set the PCLK (CCLK / 4)
	LPC_SC->PCLKSEL0 &= ~(3 << 2);

	//	Give power to the timer
	//	On by default, but just in case
	LPC_SC->PCONP |= (1 << 1);

	//	Set the MR0 value
	LPC_TIM0->MR0 = microseconds;

	//	Set the prescale register
	LPC_TIM0->PR = (uint32_t) PCLK * 0.000001;

	//	Enable timer mode
	//	On by default, just to be sure
	LPC_TIM0->CTCR &= ~(3 << 0);

	//	Reset the timer
	LPC_TIM0->TCR =  (1 << 1);

	//	 Stop TC and PC when matching MR0
	LPC_TIM0->MCR |= (1 << 2);

	//	 Reset the timer when it matches MR0
	LPC_TIM0->MCR |= (1 << 1);

	//	Disable interrupt on MR0
	LPC_TIM0->MCR &= ~(1 << 0);

	//	Start the timer
	LPC_TIM0->TCR = (1 << 0);

	//	Wait the desired time
	while (LPC_TIM0->TCR == 1)
		;
}

void timer_wait_ms(uint16_t milliseconds){

	//	Get the clock (CCLK / 4)
	uint32_t PCLK = SystemCoreClock / 4;

	//	Set the PCLK (CCLK / 4)
	LPC_SC->PCLKSEL0 &= ~(3 << 2);

	//	Give power to the timer
	//	On by default, but just in case
	LPC_SC->PCONP |= (1 << 1);

	//	Set the MR0 value
	LPC_TIM0->MR0 = milliseconds;

	//	Set the prescale register
	LPC_TIM0->PR = (uint32_t) PCLK * 0.001;

	//	Enable timer mode
	//	On by default, just to be sure
	LPC_TIM0->CTCR &= ~(3 << 0);

	//	Reset the timer
	LPC_TIM0->TCR =  (1 << 1);

	//	 Stop TC and PC when matching MR0
	LPC_TIM0->MCR |= (1 << 2);

	//	 Reset the timer when it matches MR0
	LPC_TIM0->MCR |= (1 << 1);

	//	Disable interrupt on MR0
	LPC_TIM0->MCR &= ~(1 << 0);

	//	Start the timer
	LPC_TIM0->TCR = (1 << 0);

	//	Wait the desired time
	while (LPC_TIM0->TCR == 1)
		;
}

void timer_wait_ms_interrupt(uint32_t milliseconds)
{

	//	Get the clock (CCLK / 4)
	uint32_t PCLK = SystemCoreClock / 4;

	//	Set the PCLK (CCLK / 4)
	LPC_SC->PCLKSEL0 &= ~(3 << 2);

	//	Give power to the timer
	//	On by default, but just in case
	LPC_SC->PCONP |= (1 << 1);

	//	Set the MR0 value
	LPC_TIM0->MR0 = milliseconds;

	//	Set the prescale register
	LPC_TIM0->PR = (uint32_t) PCLK * 0.001;

	//	Enable timer mode
	//	On by default, just to be sure
	LPC_TIM0->CTCR &= ~(3 << 0);

	//	Reset the timer
	LPC_TIM0->TCR =  (1 << 1);

	//	 Stop TC and PC when matching MR0
	LPC_TIM0->MCR |= (1 << 2);

	//	 Reset the timer when it matches MR0
	LPC_TIM0->MCR |= (1 << 1);

	//Enable interrupt on MR0
	LPC_TIM0->MCR |= (1 << 0);

	//	Start the timer
	LPC_TIM0->TCR = (1 << 0);

	// Enable the interrupt vector
	NVIC_EnableIRQ(TIMER0_IRQn);

}

void TIMER0_IRQHandler()
{
	//	Read which interrupt happened
	if(LPC_TIM0->IR & 1){
		//	Set the interrupt bit high
		timer_interrupt_happend = 1;

		//	Clear the interrupt flag
		LPC_TIM0->IR |= (1 << 0);

		//	Read the interrupt flag, to make sure it has been reset
		assert(LPC_TIM0->IR == 0);
	}
}

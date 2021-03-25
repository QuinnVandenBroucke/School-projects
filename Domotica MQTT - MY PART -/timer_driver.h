/*
 * wait.h
 *
 *  Created on: 19 nov. 2020
 *      Author: quinn
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

// -----------------------------------------------------------------------------
// INCLUDES
// -----------------------------------------------------------------------------
#include "LPC17xx.h"
#include "assert.h"

// -----------------------------------------------------------------------------
// FUNCTION DECLARATIONS
// -----------------------------------------------------------------------------

//	Wait for x microseconds
//	@ param microseconds : The amount of microseconds to wait
//	@ return void
void timer_wait_us(uint16_t microseconds);


//	Wait for x milliseconds
//	@ param milliseconds : The amount of milliseconds to wait
//	@ return void
void timer_wait_ms(uint16_t milliseconds);


//	Wait for x milliseconds and then generate an interrupt
//	@ param milliseconds : The amount of milliseconds to wait
//	@ return void
void timer_wait_ms_interrupt(uint32_t milliseconds);

extern uint8_t timer_interrupt_happend;

#endif /* TIMER_DRIVER_H_ */

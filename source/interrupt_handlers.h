/*
 * interrupt_handlers.h
 * 
 * This file contains the interrupt handlers for various peripherals.
 *
 *  Created on: Feb 10, 2019
 *      Author: Jack
 */

#ifndef INTERRUPT_HANDLERS_H_
#define INTERRUPT_HANDLERS_H_

#include <car_drivers/Motor.h>
#include "FreeRTOS.h"
#include "task.h"

#include "peripherals.h"
#include "car_components.h"

//extern C is needed to allow C to see C++ functions
extern "C"
{
	void FTM3_IRQHandler(void);
	void PIT0_IRQHandler(void);
	void FTM1_IRQHandler(void);
	void ADC0_IRQHandler(void);
}

#endif /* INTERRUPT_HANDLERS_H_ */

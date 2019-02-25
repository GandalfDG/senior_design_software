/*
 * interrupt_handlers.h
 *
 *  Created on: Feb 10, 2019
 *      Author: Jack
 */

#ifndef INTERRUPT_HANDLERS_H_
#define INTERRUPT_HANDLERS_H_

#include <Motor.h>
#include "peripherals.h"
#include "car_components.h"

extern "C" {
	void FTM3_IRQHandler(void);
	void PIT0_IRQHandler(void);
	void FTM1_IRQHandler(void);
	void ADC0_IRQHandler(void);
}



#endif /* INTERRUPT_HANDLERS_H_ */

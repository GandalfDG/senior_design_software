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
	void CAMERA_PIT_0_IRQHandler(void);
	void CAMERA_TIMER_IRQHandler(void);
	void CAMERA_ADC_IRQHandler(void);
}



#endif /* INTERRUPT_HANDLERS_H_ */

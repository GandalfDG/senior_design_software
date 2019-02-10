/*
 * interrupt_handlers.h
 *
 *  Created on: Feb 10, 2019
 *      Author: Jack
 */

#ifndef INTERRUPT_HANDLERS_H_
#define INTERRUPT_HANDLERS_H_

#include "peripherals.h"
#include "Motor.h"
#include "car_components.h"

extern "C" {
	void FTM3_IRQHandler(void);
}



#endif /* INTERRUPT_HANDLERS_H_ */

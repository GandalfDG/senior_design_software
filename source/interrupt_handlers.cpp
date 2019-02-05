/*
 * interrupt_handlers.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Jack
 */

#include "peripherals.h"
#include "Motor.h"
#include "car_components.h"

void ENCODER_TIMER_IRQHANDLER(void) {
	uint32_t capture_val_l = 0;
	uint32_t capture_val_r = 0;
	// read counter value from triggered channel(s)
	uint32_t encoder_l_flags = FTM_GetStatusFlags(motor_l.encoder_ftm_base)
			& (1 << motor_l.encoder_a_channel);
	uint32_t encoder_r_flags = FTM_GetStatusFlags(motor_r.encoder_ftm_base)
			& (1 << motor_r.encoder_a_channel);

	if (encoder_l_flags) {
		capture_val_l =
				motor_l.encoder_ftm_base->CONTROLS[motor_l.encoder_a_channel].CnV;
		FTM_ClearStatusFlags(motor_l.encoder_ftm_base,
				motor_l.encoder_a_channel);
	}

	if (encoder_r_flags) {
		capture_val_r =
				motor_r.encoder_ftm_base->CONTROLS[motor_r.encoder_a_channel].CnV;
		FTM_ClearStatusFlags(motor_r.encoder_ftm_base,
				motor_r.encoder_a_channel);
	}

	// clear interrupt flags on triggered channel(s)

	// notify motor structures with new counter values
}


/*
 * interrupt_handlers.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Jack
 */

#include "interrupt_handlers.h"

void FTM3_IRQHandler(void) {
	//TODO handle the timer overflow case, speed might temporarily be wrong if the timer overflows
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
				1u << motor_l.encoder_a_channel);
		motor_l.update_encoder_period(capture_val_l);
	}

	if (encoder_r_flags) {
		capture_val_r =
				motor_r.encoder_ftm_base->CONTROLS[motor_r.encoder_a_channel].CnV;
		FTM_ClearStatusFlags(motor_r.encoder_ftm_base,
				1u << motor_r.encoder_a_channel);
		motor_r.update_encoder_period(capture_val_r);
	}
}




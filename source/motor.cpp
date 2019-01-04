/*
 * motor.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Jack
 */
#include "motor.h"


motor::motor(ftm_chnl_t fwd, ftm_chnl_t rev) {
	forward_channel = fwd;
	reverse_channel = rev;

	pwm_ftm_base = MOTOR_PWM_PERIPHERAL;
	encoder_ftm_base = ENCODER_TIMER_PERIPHERAL;
}

void motor::set_speed(uint8_t rotation_speed) {
	assert()
//TODO either change duty cycle to 100-motor speed or change hardware to active low to drive our h-bridge
	if(rotation_direction == FORWARD) {
		FTM_UpdatePwmDutycycle(pwm_ftm_base, forward_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, rotation_speed);
		FTM_UpdatePwmDutycycle(pwm_ftm_base, reverse_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, 100);
	}

	else if(rotation_direction == REVERSE) {
		FTM_UpdatePwmDutycycle(pwm_ftm_base, reverse_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, rotation_speed);
		FTM_UpdatePwmDutycycle(pwm_ftm_base, forward_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, 100);
	}
}

void motor::set_direction(motor::direction dir) {
	rotation_direction = dir;
}

void motor::stop(void) {
}

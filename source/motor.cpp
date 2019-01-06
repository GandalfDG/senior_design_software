/*
 * motor.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Jack
 */
#include <Motor.h>


Motor::Motor(ftm_chnl_t fwd, ftm_chnl_t rev) {
	forward_channel = fwd;
	reverse_channel = rev;

	pwm_ftm_base = MOTOR_PWM_PERIPHERAL;
	encoder_ftm_base = ENCODER_TIMER_PERIPHERAL;
}

void Motor::set_speed(uint8_t rotation_speed) {
	assert(rotation_speed >= 0 && rotation_speed <= 100);
	uint8_t inverse_duty = 100 - rotation_speed;

	if(rotation_direction == FORWARD) {
		FTM_UpdatePwmDutycycle(pwm_ftm_base, forward_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, inverse_duty);
		FTM_UpdatePwmDutycycle(pwm_ftm_base, reverse_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, 100);
	}

	else if(rotation_direction == REVERSE) {
		FTM_UpdatePwmDutycycle(pwm_ftm_base, reverse_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, inverse_duty);
		FTM_UpdatePwmDutycycle(pwm_ftm_base, forward_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, 100);
	}

	Motor::rotation_speed = rotation_speed;
}

void Motor::set_direction(direction dir) {
	rotation_direction = dir;
	set_speed(rotation_speed);
}

Motor::direction Motor::getRotationDirection() const {
	return rotation_direction;
}

uint8_t Motor::getRotationSpeed() const {
	return rotation_speed;
}

void Motor::stop(void) {
	FTM_UpdatePwmDutycycle(pwm_ftm_base, forward_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, 0);
	FTM_UpdatePwmDutycycle(pwm_ftm_base, reverse_channel, (ftm_pwm_mode_t)Motor_PWM_config.pwmSyncMode, 0);
	rotation_speed = 0;
}

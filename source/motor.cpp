/*
 * motor.cpp
 *
 *  Created on: Jan 4, 2019
 *      Author: Jack
 */
#include <Motor.h>

Motor::Motor(ftm_chnl_t fwd, ftm_chnl_t rev,  ftm_chnl_t enc_a, ftm_chnl_t enc_b) {
	forward_channel = fwd;
	reverse_channel = rev;
	encoder_a_channel = enc_a;
	encoder_b_channel = enc_b;

	encoder_a_prev = 0;
	encoder_b_prev = 0;
	encoder_a_curr = 0;
	encoder_b_curr = 0;

	physical_speed = 0;

	pwm_ftm_base = MOTOR_PWM_PERIPHERAL;
	encoder_ftm_base = ENCODER_TIMER_PERIPHERAL;
}

void Motor::set_speed(uint8_t rotation_speed) {
	assert(rotation_speed >= 0 && rotation_speed <= 100);
	uint8_t inverse_duty = 100 - rotation_speed;

	if (rotation_direction == FORWARD) {
		FTM_UpdatePwmDutycycle(pwm_ftm_base, forward_channel,
				kFTM_EdgeAlignedPwm, inverse_duty);
		FTM_UpdatePwmDutycycle(pwm_ftm_base, reverse_channel,
				kFTM_EdgeAlignedPwm, 100);
	}

	else if (rotation_direction == REVERSE) {
		FTM_UpdatePwmDutycycle(pwm_ftm_base, reverse_channel,
				kFTM_EdgeAlignedPwm, inverse_duty);
		FTM_UpdatePwmDutycycle(pwm_ftm_base, forward_channel,
				kFTM_EdgeAlignedPwm, 100);
	}

	FTM_SetSoftwareTrigger(pwm_ftm_base, true);

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
	FTM_UpdatePwmDutycycle(pwm_ftm_base, forward_channel,
			(ftm_pwm_mode_t) Motor_PWM_config.pwmSyncMode, 0);
	FTM_UpdatePwmDutycycle(pwm_ftm_base, reverse_channel,
			(ftm_pwm_mode_t) Motor_PWM_config.pwmSyncMode, 0);
	rotation_speed = 0;
}

uint16_t Motor::getPhysicalSpeed() {
	return physical_speed;
}

//this can be called from the motor drive task if a semaphore has been given from the isr
void Motor::update_physical_speed() {
	physical_speed = encoder_a_curr - encoder_a_prev;
	//could also check physical rotation direction by comparing most recent
	//time from a and b, but not super important
}

void Motor::motor_test(void) {
	set_direction(FORWARD);

	// drive motors from 0 to full forward
	for (int i = 0; i <= 100; i++) {
		set_speed(i);
		vTaskDelay(pdMS_TO_TICKS(MOTOR_TEST_PERIOD));
	}

	// from full forward to 0
	for (int i = 100; i >= 0; i--) {
		set_speed(i);
		vTaskDelay(pdMS_TO_TICKS(MOTOR_TEST_PERIOD));
	}

	set_direction(REVERSE);

	// drive motors from 0 to full reverse
	for (int i = 0; i <= 100; i++) {
		set_speed(i);
		vTaskDelay(pdMS_TO_TICKS(MOTOR_TEST_PERIOD));
	}

	// from full reverse to 0
	for (int i = 100; i >= 0; i--) {
		set_speed(i);
		vTaskDelay(pdMS_TO_TICKS(MOTOR_TEST_PERIOD));
	}
	vTaskSuspend(NULL);

}


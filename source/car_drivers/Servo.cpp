/*
 * Servo.cpp
 *
 *  Created on: Jan 6, 2019
 *      Author: Jack
 */

#include <car_drivers/Servo.h>

Servo::Servo() {
	Servo(kFTM_Chnl_0, 400, 2000);
}

Servo::Servo(ftm_chnl_t servo_channel, uint16_t left_width,
		uint16_t right_width) {
	servo_channel = servo_channel;
	left_pulse_width = left_width;
	right_pulse_width = right_width;
	center_pulse_width = (left_pulse_width + right_pulse_width) / 2;
	current_pulse_width = center_pulse_width;
}

void Servo::set_position(uint16_t pos) {
	uint16_t cnv, mod;
	mod = pwm_ftm_base->MOD;

	cnv = (mod * pos) / SERVO_PWM_PERIOD;
	pwm_ftm_base->CONTROLS[servo_channel].CnV = cnv;

	FTM_SetSoftwareTrigger(pwm_ftm_base, true);

	current_pulse_width = pos;
}

void Servo::servo_test(void) {
	vTaskSuspend(NULL);

	// start at center
	set_position(center_pulse_width);

	// move to full left
	for (int i = center_pulse_width; i >= left_pulse_width; i -=
	SERVO_TEST_STEP) {
		set_position(i);
		vTaskDelay(pdMS_TO_TICKS(SERVO_TEST_PERIOD));
	}

	// move to full right

	for (int i = left_pulse_width; i <= right_pulse_width; i +=
	SERVO_TEST_STEP) {
		set_position(i);
		vTaskDelay(pdMS_TO_TICKS(SERVO_TEST_PERIOD));
	}

	// move back to center
	for (int i = right_pulse_width; i >= center_pulse_width; i -=
	SERVO_TEST_STEP) {
		set_position(i);
		vTaskDelay(pdMS_TO_TICKS(SERVO_TEST_PERIOD));
	}

}

void Servo::position_from_camera(int centerline) {
int exp_centerline;
if(centerline >= 64) {
	exp_centerline = (int)(centerline + pow(EXPVAL, centerline - 64));
	exp_centerline = exp_centerline <= NUM_PIXELS ? exp_centerline : NUM_PIXELS;
}
else {
	exp_centerline = (int)(centerline - pow(EXPVAL, 64 - centerline));
	exp_centerline = exp_centerline >= 0 ? exp_centerline : 0;
}
int position = (right_pulse_width - left_pulse_width) * (((float)NUM_PIXELS - (float)exp_centerline) / (float)NUM_PIXELS) + left_pulse_width;
	set_position(position);
}

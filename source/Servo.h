/*
 * Servo.h
 *
 *  Created on: Jan 6, 2019
 *      Author: Jack
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "MK64f12.h"
#include "peripherals.h"

#include "FreeRTOS.h"
#include "task.h"

#define SERVO_PWM_PERIOD (20000) // microseconds
#define SERVO_TEST_PERIOD (30)  // milliseconds
#define SERVO_TEST_STEP (10)

class Servo {
public:

	FTM_Type* pwm_ftm_base = SERVO_PWM_PERIPHERAL;


	Servo();
	Servo(ftm_chnl_t servo_channel, uint16_t left_width, uint16_t right_width);

	void set_position(uint16_t pos);
	void servo_test(void);

private:
	ftm_chnl_t servo_channel;

	// pulse widths in microseconds
	uint16_t center_pulse_width, left_pulse_width, right_pulse_width;
	uint16_t current_pulse_width;
};

#endif /* SERVO_H_ */

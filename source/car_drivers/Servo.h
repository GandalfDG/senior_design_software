/*
 * Servo.h
 *
 *  Created on: Jan 6, 2019
 *      Author: Jack
 */

#ifndef CAR_DRIVERS_SERVO_H_
#define CAR_DRIVERS_SERVO_H_

#include "MK64f12.h"
#include "peripherals.h"

#include <cmath>
#include "FreeRTOS.h"
#include "task.h"

#define SERVO_PWM_PERIOD (20000) // microseconds
#define SERVO_TEST_PERIOD (100)  // milliseconds
#define SERVO_TEST_STEP (50)
#define NUM_PIXELS (128)
#define EXPVAL (1.15f)

class Servo {
public:

	TaskHandle_t test_task_handle;

	FTM_Type* pwm_ftm_base = SERVO_PWM_PERIPHERAL;

	// pulse widths in microseconds
	uint16_t center_pulse_width, left_pulse_width, right_pulse_width;
	uint16_t current_pulse_width;


	Servo();
	Servo(ftm_chnl_t servo_channel, uint16_t left_width, uint16_t right_width);

	void set_position(uint16_t pos);
	void servo_test(void);

	void position_from_camera(int centerline);

private:
	ftm_chnl_t servo_channel;


};

#endif /* CAR_DRIVERS_SERVO_H_ */

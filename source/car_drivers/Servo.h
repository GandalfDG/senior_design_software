/*
 * Servo.h
 *
 * This class contains code for driving a servo motor via a PWM signal.
 * 
 * For an example of servo object construction, refer to car_components.cpp
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
#define EXPVAL (1.2f)

class Servo
{
  public:
	TaskHandle_t test_task_handle;
	TaskHandle_t task_handle;

	FTM_Type *pwm_ftm_base = SERVO_PWM_PERIPHERAL;

	// pulse widths in microseconds
	uint16_t center_pulse_width, left_pulse_width, right_pulse_width;
	uint16_t current_pulse_width;

	Servo();
	Servo(ftm_chnl_t servo_channel, uint16_t left_width, uint16_t right_width);

	//sets the pulse width to the specified number of microseconds
	void set_position(uint16_t pos);

	//moves the servo back and forth for testing
	void servo_test(void);

	//sets the servo position based on the provided current centerline value
	void position_from_camera(int centerline);

  private:
	ftm_chnl_t servo_channel;
};

#endif /* CAR_DRIVERS_SERVO_H_ */

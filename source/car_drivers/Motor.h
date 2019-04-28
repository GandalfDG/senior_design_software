/*
 * motor.h
 * 
 * This class contains code for driving a motor via an h-bridge with PWM-
 * controlled speed, as well as for reading motor speed with an encoder.
 * 
 * For and example of Motor object construction, refer to car_components.cpp
 * 
 *  Created on: Jan 4, 2019
 *      Author: Jack
 */

#ifndef CAR_DRIVERS_MOTOR_H_
#define CAR_DRIVERS_MOTOR_H_

#include "MK64F12.h"
#include "peripherals.h"

#include "FreeRTOS.h"
#include "task.h"

#define MOTOR_TEST_PERIOD (100) //milliseconds

class Motor
{
  public:
	enum direction
	{
		FORWARD,
		REVERSE
	};

	//the peripheral base addresses for the h-bridge and encoders
	FTM_Type *pwm_ftm_base;
	FTM_Type *encoder_ftm_base;

	TaskHandle_t test_task_handle;

	// the channels corresponding to driving the motor forward or in reverse
	ftm_chnl_t forward_channel, reverse_channel;
	// the channels corresponding to each encoder
	ftm_chnl_t encoder_a_channel, encoder_b_channel;

	Motor(ftm_chnl_t fwd, ftm_chnl_t rev, ftm_chnl_t enc_a, ftm_chnl_t enc_b);

	// this should be called after peripheral initialization to get some important values
	void init();

	void set_speed(uint8_t rotation_speed);
	void set_direction(direction dir);
	void stop(void);
	direction getRotationDirection() const;
	uint8_t getRotationSpeed() const;

	static void ENCODER_TIMER_IRQHANDLER();

	void update_encoder_period(uint32_t captured);

	void motor_test(void);
	uint16_t getPhysicalSpeed();

  private:
	void period_to_rpm(void);
	// internal values for determining the actual rotation speed of the motor
	uint16_t encoder_a_prev, encoder_b_prev;
	uint16_t encoder_a_curr, encoder_b_curr;

	uint32_t pwm_timer_freq, encoder_timer_freq;

	uint8_t rotation_speed; // 0% - 100%
	direction rotation_direction;
	uint16_t raw_period;
	uint16_t physical_speed;
};

#endif /* CAR_DRIVERS_MOTOR_H_ */

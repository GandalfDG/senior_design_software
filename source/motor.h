/*
 * motor.h
 *
 *  Created on: Jan 4, 2019
 *      Author: Jack
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "MK64F12.h"
#include "peripherals.h"

#include "FreeRTOS.h"
#include "task.h"

#define MOTOR_TEST_PERIOD (100) //milliseconds

class Motor {
public:
	enum direction {
		FORWARD,
		REVERSE
	};

	FTM_Type* pwm_ftm_base;
	FTM_Type* encoder_ftm_base;

	Motor(ftm_chnl_t fwd, ftm_chnl_t rev, ftm_chnl_t enc_a, ftm_chnl_t enc_b);

	void set_speed(uint8_t rotation_speed);
	void set_direction(direction dir);
	void stop(void);
	direction getRotationDirection() const;
	uint8_t getRotationSpeed() const;

	static void ENCODER_TIMER_IRQHANDLER();
	
	void update_physical_speed();

	void motor_test(void);
	uint16_t getPhysicalSpeed();

private:
	// the channels corresponding to driving the motor forward or in reverse
	ftm_chnl_t forward_channel, reverse_channel;
	ftm_chnl_t encoder_a_channel, encoder_b_channel;

	// internal values for determining the actual rotation speed of the motor
	uint16_t encoder_a_prev, encoder_b_prev;
	uint16_t encoder_a_curr, encoder_b_curr;

	uint8_t rotation_speed; // 0% - 100%
	direction rotation_direction;
	
	uint16_t physical_speed;
};



#endif /* MOTOR_H_ */

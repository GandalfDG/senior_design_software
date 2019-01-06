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

class Motor {
public:
	enum direction {
		FORWARD,
		REVERSE
	};

	static FTM_Type* pwm_ftm_base;
	static FTM_Type* encoder_ftm_base;

	Motor(ftm_chnl_t fwd, ftm_chnl_t rev);

	void set_speed(uint8_t rotation_speed);
	void set_direction(direction dir);
	void stop(void);
	direction getRotationDirection() const;
	uint8_t getRotationSpeed() const;

private:
	// the channels corresponding to driving the motor forward or in reverse
	ftm_chnl_t forward_channel, reverse_channel;
	uint8_t rotation_speed; // 0% - 100%
	direction rotation_direction;
};



#endif /* MOTOR_H_ */

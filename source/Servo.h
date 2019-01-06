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

class Servo {
public:

	static FTM_Type* pwm_ftm_base;

	Servo();
	virtual ~Servo();

	void set_position(uint8_t pos);

private:
	uint8_t center_position;
	uint8_t position;
};

#endif /* SERVO_H_ */

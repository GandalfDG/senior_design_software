/*
 * MotorDrive.h
 *
 *  Created on: Apr 23, 2019
 *      Author: Jack
 */

#ifndef MOTORDRIVE_H_
#define MOTORDRIVE_H_

#include <car_drivers/Motor.h>
#include "FreeRTOS.h"
#include "task.h"

#define TOP_SPEED (100)
#define MIN_SPEED (50)

#define CENTER (64)
#define CENTER_BUFFER (5)

class MotorDrive {
public:
	TaskHandle_t task_handle;
	unsigned int current_speed;
	Motor &motor_l, &motor_r;
	MotorDrive(Motor &motor_l, Motor &motor_r): motor_l{motor_l}, motor_r{motor_r} {};

	void update_from_camera(int centerline);
	void set_motors(int duty);
	void set_motors(int duty_l, int duty_r);
};

#endif /* MOTORDRIVE_H_ */

/*
 * MotorDrive.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: Jack
 */

#include <MotorDrive.h>

void MotorDrive::update_from_camera(int centerline) {
	//if on centerline, increase speed towards top speed
	if(centerline < CENTER + CENTER_BUFFER && centerline > CENTER - CENTER_BUFFER) {
		current_speed += current_speed + 1 <= TOP_SPEED ? 1 : 0;
	}
	else {
		current_speed = MIN_SPEED;
	}
	set_motors(current_speed);
}

void MotorDrive::set_motors(int duty) {
	motor_l.set_direction(Motor::FORWARD);
	motor_r.set_direction(Motor::FORWARD);
	motor_l.set_speed(duty);
	motor_r.set_speed(duty);
}

void MotorDrive::set_motors(int duty_l, int duty_r) {
	motor_l.set_direction(Motor::FORWARD);
	motor_r.set_direction(Motor::FORWARD);
	motor_l.set_speed(duty_l);
	motor_r.set_speed(duty_r);
}

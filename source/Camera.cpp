/*
 * Camera.cpp
 *
 *  Created on: Feb 21, 2019
 *      Author: Jack
 */

#include <Camera.h>

void Camera::init() {
	gpio_pin_config_t gpioconfig;
	gpioconfig.pinDirection = kGPIO_DigitalOutput;
	gpioconfig.outputLogic = 0;
	GPIO_PinInit(gpio_base, si_pin, &gpioconfig);
	GPIO_PinInit(gpio_base, clk_pin, &gpioconfig);
}

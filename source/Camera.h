/*
 * Camera.h
 *
 *  Created on: Feb 21, 2019
 *      Author: Jack
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "MK64F12.h"
#include "peripherals.h"

class Camera {
public:

	//peripherals responsible for driving the camera
	FTM_Type* ftm_base;
	ftm_chnl_t ftm_channel;

	PIT_Type* pit_base;
	pit_chnl_t pit_channel;
	ADC_Type* adc_base;
	GPIO_Type* gpio_base;

	uint32_t clk_pin, si_pin;

	Camera(FTM_Type* ftm, ftm_chnl_t ftm_chnl, PIT_Type* pit, pit_chnl_t pit_chnl, ADC_Type* adc, GPIO_Type* gpio, uint32_t clk, uint32_t si):
		ftm_base{ftm},
		ftm_channel{ftm_chnl},
		pit_base{pit},
		pit_channel{pit_chnl},
		adc_base{adc},
		gpio_base{gpio},
		clk_pin{clk},
		si_pin{si} {};

	int16_t current_pixel = 0;
	uint32_t adc_value = 0;

	uint16_t line_buffer[128];

private:

};

#endif /* CAMERA_H_ */

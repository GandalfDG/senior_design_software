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
	FTM_Type* camera_ftm_base;
	PIT_Type* camera_pit_base;
	ADC_Type* camera_adc_base;

	Camera();
};

#endif /* CAMERA_H_ */

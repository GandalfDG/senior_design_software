/*
 * Camera.cpp
 *
 *  Created on: Feb 21, 2019
 *      Author: Jack
 */

#include <car_drivers/Camera.h>

void Camera::init() {
	//set gpio pins as output
	gpio_pin_config_t gpioconfig;
	gpioconfig.pinDirection = kGPIO_DigitalOutput;
	gpioconfig.outputLogic = 0;
	GPIO_PinInit(gpio_base, si_pin, &gpioconfig);
	GPIO_PinInit(gpio_base, clk_pin, &gpioconfig);

	//enable the ADC
	adc16_channel_config_t adcconfig;
	adcconfig.channelNumber = 0;
	adcconfig.enableInterruptOnConversionCompleted = true;
	adcconfig.enableDifferentialConversion = false;
	ADC16_SetChannelConfig(adc_base, 0, &adcconfig);

}

void Camera::process(void) {
	uint16_t current_line[NUM_PIXELS];
	uint16_t previous_line[NUM_PIXELS];
	uint16_t *temp;

	//initialize camera data struct
	camera_data.center = NUM_PIXELS / 2;
	camera_data.prev_center = camera_data.center;

	//load the previous value on the first run
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	memcpy((void*) previous_line, (const void*) line_buffer,
			NUM_PIXELS * sizeof(uint16_t));

	for (;;) {
		//wait for the line buffer to be full
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		//copy the current line into a local buffer
		memcpy((void*) current_line, (const void*) line_buffer,
				NUM_PIXELS * sizeof(uint16_t));

		//find edges
		find_edges(current_line);

		//move current line to previous line
		//TODO optimize this by swapping pointers around instead of copying all the time
		memcpy((void*) previous_line, (const void*) current_line,
				NUM_PIXELS * sizeof(uint16_t));

		//pass data to relevant tasks (motor, servo)

		vTaskDelay(pdMS_TO_TICKS(1000));
	}

}

void Camera::filter(void) {

}

void Camera::calibrate(void) {
	uint16_t average[NUM_PIXELS];
	uint16_t current[NUM_PIXELS];
	//initialize the average
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

	//initialize the calibration struct
	calibration.max = 0;
	calibration.min = UINT16_MAX;

	memcpy((void*) average, (const void*) line_buffer,
			NUM_PIXELS * sizeof(uint16_t));

	//average some number of camera readings
	for (int i = 0; i < CALIBRATION_COUNT; i++) {
		//wait for a camera reading
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		memcpy((void*) current, (const void*) line_buffer,
				NUM_PIXELS * sizeof(uint16_t));

		for (int j = 0; j < NUM_PIXELS; j++) {
			average[j] = (average[j] + current[j]) / 2;
		}

	}

	//find max, min, and calculate a threshold value
	for (int i = 0; i < NUM_PIXELS; i++) {
		if (average[i] > calibration.max) {
			calibration.max = average[i];
		}
		if (average[i] < calibration.min) {
			calibration.min = average[i];
		}
	}

	//TODO a better threshold might be some percentage other than 50%
	calibration.rising_threshold = (calibration.max + calibration.min) / 2 + THRESHOLD_WIDTH;
	calibration.falling_threshold = (calibration.max + calibration.min) / 2 - THRESHOLD_WIDTH;

}

void Camera::find_edges(uint16_t* camline) {
	camera_data.left_edge_outer = find_edge_between(0,
			NUM_PIXELS, camline, FALLING);
	camera_data.left_edge_inner = find_edge_between(camera_data.left_edge_outer,
			NUM_PIXELS, camline, RISING);
	camera_data.right_edge_inner = find_edge_between(camera_data.left_edge_inner + FUZZY_WIDTH,
			NUM_PIXELS, camline, FALLING);
	camera_data.right_edge_outer = find_edge_between(camera_data.right_edge_inner, NUM_PIXELS,
			camline, RISING);
	camera_data.prev_center = camera_data.center;
	camera_data.center = (camera_data.left_edge_inner + camera_data.right_edge_inner) / 2;
}

uint8_t Camera::find_edge_between(uint8_t lower_bound, uint8_t upper_bound,
		uint16_t *camline, edge_polarity pol) {
	int8_t edge = -1;
	for (int i = lower_bound >= 0 ? lower_bound : 0;
			i < (upper_bound <= NUM_PIXELS ? upper_bound : NUM_PIXELS) && edge == -1; i++) {
		if (pol == RISING) {
			if (camline[i] > calibration.rising_threshold) {
				edge = i;
			}
		} else {
			if (camline[i] < calibration.falling_threshold) {
				edge = i;
			}
		}
	}
	return (uint8_t)edge >= 0 ? edge : 0;
}

uint8_t Camera::calculate_centerline(struct data* camdata) {
	if(camdata->left_edge_inner && camdata->right_edge_inner) {
		camdata->center = (camdata->left_edge_inner + camdata->right_edge_inner) / 2;
	}
	else {
		camdata->center = camdata->prev_center;
	}

	camdata->prev_center = camdata->center;
	return camdata->center;
}

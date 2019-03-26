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
	struct data camdata;

	//initialize camera data struct
	camdata.center = NUM_PIXELS / 2;
	camdata.prev_center = camdata.center;

	//load the previous value on the first run
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	memcpy((void*)previous_line, (const void*)line_buffer, NUM_PIXELS * sizeof(uint16_t));


	for (;;) {
		//wait for the line buffer to be full
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		//copy the current line into a local buffer
		memcpy((void*)current_line, (const void*)line_buffer, NUM_PIXELS * sizeof(uint16_t));

		//find edges
		uint16_t max = 0;
		for(int i = 0; i < NUM_PIXELS; i++) {
			if(current_line[i] > max) {
				max = current_line[i];
			}
		}

		//move current line to previous line
		//TODO optimize this by swapping pointers around instead of copying all the time
		memcpy((void*)previous_line, (const void*)current_line, NUM_PIXELS * sizeof(uint16_t));

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
	calibration.threshold = 0;

	memcpy((void*)average, (const void*)line_buffer, NUM_PIXELS * sizeof(uint16_t));

	//average some number of camera readings
	for(int i = 0; i < CALIBRATION_COUNT; i++) {
		//wait for a camera reading
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		memcpy((void*)current, (const void*)line_buffer, NUM_PIXELS * sizeof(uint16_t));

		for(int j = 0; j < NUM_PIXELS; j++) {
			average[j] = (average[j] + current[j]) / 2;
		}

	}

	//find max, min, and calculate a threshold value
	for(int i = 0; i < NUM_PIXELS; i++) {
		if(average[i] > calibration.max) {
			calibration.max = average[i];
		}
		if(average[i] < calibration.min) {
			calibration.min = average[i];
		}
	}

	//TODO a better threshold might be some percentage other than 50%
	calibration.threshold = (calibration.max + calibration.min) / 2;

}

void Camera::find_edges(uint16_t* camline, struct data* camdata) {
	camdata->left_edge_inner = find_edge_between(camdata->prev_center, NUM_PIXELS, camline, RISING);
	camdata->left_edge_outer = find_edge_between(camdata->left_edge_inner, NUM_PIXELS, camline, FALLING);
	camdata->right_edge_outer = find_edge_between(0, camdata->prev_center, camline, RISING);
	camdata->right_edge_inner = find_edge_between(camdata->right_edge_outer, camdata->prev_center, camline, FALLING);


}

uint8_t Camera::find_edge_between(uint8_t lower_bound, uint8_t upper_bound,
		uint16_t *camline, edge_polarity pol) {
	uint8_t edge = -1;
	for(int i = lower_bound; i < upper_bound && edge == -1; i++) {
		if(pol == RISING) {
			if(camline[i] > calibration.threshold) {
				edge = i;
			}
		}
		else {
			if(camline[i] < calibration.threshold) {
				edge = i;
			}
		}
	}
	return edge;
}

/*
 * Camera.h
 *
 *  Created on: Feb 21, 2019
 *      Author: Jack
 */

#ifndef CAR_DRIVERS_CAMERA_H_
#define CAR_DRIVERS_CAMERA_H_

#include "MK64F12.h"
#include "peripherals.h"

#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdint.h>

#define NUM_PIXELS (128)			//the number of camera pixels
#define CALIBRATION_COUNT (256)		//the number of camera readings to average for calibration

class Camera {
public:

	struct data {
		uint8_t left_edge_inner, left_edge_outer;
		uint8_t right_edge_inner, right_edge_outer;
		uint8_t center, prev_center;
	};

	struct calibration {
		uint16_t max, min, threshold;
	} calibration;

	enum edge_polarity {
		RISING, FALLING
	};

	//peripherals responsible for driving the camera
	FTM_Type* ftm_base;
	ftm_chnl_t ftm_channel;

	PIT_Type* pit_base;
	pit_chnl_t pit_channel;
	ADC_Type* adc_base;
	GPIO_Type* gpio_base;

	uint32_t clk_pin, si_pin;

	TaskHandle_t task_handle;

	int16_t current_pixel = 0;
	uint32_t adc_value = 0;

	uint16_t line_buffer[NUM_PIXELS];

	void init();

	Camera(FTM_Type* ftm, ftm_chnl_t ftm_chnl, PIT_Type* pit,
			pit_chnl_t pit_chnl, ADC_Type* adc, GPIO_Type* gpio, uint32_t clk,
			uint32_t si) :
			ftm_base { ftm }, ftm_channel { ftm_chnl }, pit_base { pit }, pit_channel {
					pit_chnl }, adc_base { adc }, gpio_base { gpio }, clk_pin {
					clk }, si_pin { si }, task_handle { NULL } {
	}
	;

	void process(void);
	void calibrate(void);

private:
	void filter(void);
	void find_edges(uint16_t *camline, struct data *camdata);
	uint8_t find_edge_between(uint8_t lower_bound, uint8_t upper_bound,
			uint16_t *camline, edge_polarity pol);
	uint8_t calculate_centerline(struct data *camdata);
};

#endif /* CAR_DRIVERS_CAMERA_H_ */

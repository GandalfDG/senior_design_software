/*
 * Camera.h
 *
 * This file contains code for processing input from the linescan camera.
 * The actual code that drives and reads values from the camera is located in
 * interrupt_handlers.cpp 
 * 
 * The interrupt handler notifies the camera RTOS task when a full line has been
 * read, unblocking the process function and copying that full line into a local
 * buffer.
 * 
 * For an example of camera object construction, refer to car_components.cpp
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

#define NUM_PIXELS (128)		//the number of camera pixels
#define CALIBRATION_COUNT (256) //the number of camera readings to average for calibration

#define FUZZY_WIDTH (20) //gives some leeway between edge detections

#define THRESHOLD_WIDTH (100)	 //determines the difference between rising and falling threshold values
#define BAD_CENTER_THRESHOLD (50) //a threshold for determining erroneous centerline values

class Camera
{
  public:
	//where public data about the camera's view will be stored
	struct data
	{
		uint8_t left_edge_inner, left_edge_outer;
		uint8_t right_edge_inner, right_edge_outer;
		uint8_t center, prev_center;
	} camera_data;

	//where calibration values will be stored
	struct calibration
	{
		uint16_t max, min, rising_threshold, falling_threshold;
	} calibration;

	//peripherals responsible for driving the camera
	FTM_Type *ftm_base;
	ftm_chnl_t ftm_channel;

	PIT_Type *pit_base;
	pit_chnl_t pit_channel;
	ADC_Type *adc_base;
	GPIO_Type *gpio_base;

	uint32_t clk_pin, si_pin;

	TaskHandle_t task_handle;

	int16_t current_pixel = 0;
	uint32_t adc_value = 0;

	//interrupt handler stores pixels here
	uint16_t line_buffer[NUM_PIXELS];

	void init();

	Camera(FTM_Type *ftm, ftm_chnl_t ftm_chnl, PIT_Type *pit,
		   pit_chnl_t pit_chnl, ADC_Type *adc, GPIO_Type *gpio, uint32_t clk,
		   uint32_t si) : ftm_base{ftm}, ftm_channel{ftm_chnl}, pit_base{pit}, pit_channel{
																				   pit_chnl},
						  adc_base{adc}, gpio_base{gpio}, clk_pin{clk}, si_pin{si}, task_handle{NULL} {};

	/* this is the main function called by the RTOS camera task.
	 * it waits for a task notification sent by the interrupt
	 * handler, and then copies the line of pixel data to a 
	 * local buffer.
	 */
	void process(void);

	/* This function calibrates the rising and falling threshold
 	 * values by averaging a number of camera lines while the 
	 * camera is pointed at the track.
	 */
	void calibrate(void);

  private:
	//used for the find_edges_between function
	enum edge_polarity
	{
		RISING,
		FALLING
	};

	/* this function looks for the black lines from the center
	 * of the camera line outward in both directions.
 	*/
	void find_edges(uint16_t camline[]);

	/* this function looks for falling or rising threshold crosses between the lower and
 	* upper bound values provided. This can work in either direction.
 	*/
	uint8_t find_edge_between(uint8_t lower_bound, uint8_t upper_bound,
							  uint16_t *camline, edge_polarity pol, bool reverse);

	/* finds a centerline value by averaging the left and right edge positions.
 	* It also handles erroneous cases of a centerline being wildly different 
 	* from its previous value.
 	*/
	uint8_t calculate_centerline(struct data *camdata);
};

#endif /* CAR_DRIVERS_CAMERA_H_ */

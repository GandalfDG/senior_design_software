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
	for (;;) {
		//wait for the line buffer to be full
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		//copy the current line into a local buffer
		uint16_t current_line[NUM_PIXELS];
		memcpy((void*)current_line, (const void*)line_buffer, NUM_PIXELS * sizeof(uint16_t));

		//find edges
		uint16_t max = 0;
		for(int i = 0; i < NUM_PIXELS; i++) {
			if(current_line[i] > max) {
				max = current_line[i];
			}
		}

		//pass data to relevant tasks (motor, servo)

		PRINTF("camera line max value: %d\r\n\r\n", max);

		vTaskDelay(pdMS_TO_TICKS(1000));
	}

}

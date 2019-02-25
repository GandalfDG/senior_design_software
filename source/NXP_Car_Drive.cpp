/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    NXP_Car_Drive.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "PortExpander.h"
#include "UserInterface.h"

#include "car_components.h"
#include "interrupt_handlers.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)
static void hello_task(void*);
static void motor_test_task(void*);
static void servo_test_task(void *pvParameters);
static void print_diagnostic_task(void *pvParameters);

User_Interface interface;

/*
 * @brief   Application entry point.
 */
int main(void) {

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();

	motor_l.init();
	motor_r.init();
	camera.init();
	camera.adc_base->SC1[0] |= ADC_SC1_AIEN_MASK;

	//uint32_t test = ADC16_GetChannelConversionValue(camera.adc_base, 0);

	PortExpander expander;

	expander.begin();

	xTaskCreate(print_diagnostic_task, "Diagnostic task",
	configMINIMAL_STACK_SIZE + 100, NULL, hello_task_PRIORITY, NULL);

//	if (xTaskCreate(hello_task, "Hello_task", configMINIMAL_STACK_SIZE + 20,
//	NULL, hello_task_PRIORITY, NULL) != pdPASS) {
//		PRINTF("Task creation failed!.\r\n");
//		while (1)
//			;
//	}

	xTaskCreate(servo_test_task, "Servo_test", configMINIMAL_STACK_SIZE, &servo,
	hello_task_PRIORITY, NULL);
	if (xTaskCreate(motor_test_task, "Motor_test", configMINIMAL_STACK_SIZE,
			(void*) &motor_l, hello_task_PRIORITY, NULL) != pdPASS
			|| xTaskCreate(motor_test_task, "Motor_test",
			configMINIMAL_STACK_SIZE, (void*) &motor_r,
			hello_task_PRIORITY, NULL) != pdPASS) {
		PRINTF("Task creation failed!.\r\n");
		while (1)
			;
	}

	vTaskStartScheduler();
	for (;;)
		;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void hello_task(void *pvParameters) {
	interface.begin(16, 2);
	interface.clear();
	for (;;) {
		PRINTF("Hello world.\r\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

static void motor_test_task(void *pvParameters) {
	Motor* motor_p = (Motor*) pvParameters;
	for (;;) {
		motor_p->motor_test();
	}
}

static void servo_test_task(void *pvParameters) {
	Servo* servo_p = (Servo*) pvParameters;
	for (;;) {
		servo_p->servo_test();
	}
}

static void print_diagnostic_task(void *pvParameters) {
	for (;;) {
		PRINTF("Left motor speed set at %d\r\n Physical speed: %d\r\n\r\n",
				motor_l.getRotationSpeed(), motor_l.getPhysicalSpeed());
		PRINTF("Right motor speed set at %d\r\n Physical speed: %d\r\n\r\n",
				motor_r.getRotationSpeed(), motor_r.getPhysicalSpeed());
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}


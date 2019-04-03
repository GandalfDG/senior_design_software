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
#include <car_drivers/PortExpander.h>
#include <car_drivers/UserInterface.h>
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

#include "car_components.h"
#include "interrupt_handlers.h"

#define hello_task_PRIORITY (configMAX_PRIORITIES - 2)
static void hello_task(void*);
static void motor_test_task(void*);
static void servo_test_task(void *pvParameters);
static void print_diagnostic_task(void *pvParameters);
static void camera_task(void *pvParameters);
static void user_interface_task(void *pvParameters);
static void steering_task(void *pvParameters);

//test drive
static void circle_drive_task(void *pvParameters);
TaskHandle_t circle_handle;

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

	__NVIC_SetPriority(FTM1_IRQn,
			((configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1)
					<< __NVIC_PRIO_BITS) - 1UL);
	__NVIC_SetPriority(ADC0_IRQn,
			((configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1)
					<< __NVIC_PRIO_BITS) - 1UL);
	__NVIC_SetPriority(PIT0_IRQn,
			((configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1)
					<< __NVIC_PRIO_BITS) - 1UL);

	expander.begin();

	xTaskCreate(print_diagnostic_task, "Diagnostic task",
	configMINIMAL_STACK_SIZE + 100, NULL, hello_task_PRIORITY, NULL);

//	if (xTaskCreate(hello_task, "Hello_task", configMINIMAL_STACK_SIZE + 20,
//	NULL, hello_task_PRIORITY, NULL) != pdPASS) {
//		PRINTF("Task creation failed!.\r\n");
//		while (1)
//			;
//	}

//	xTaskCreate(servo_test_task, "Servo_test", configMINIMAL_STACK_SIZE, &servo,
//	hello_task_PRIORITY, &servo.test_task_handle);

//	xTaskCreate(user_interface_task, "UI", configMINIMAL_STACK_SIZE + 100, NULL,
//	hello_task_PRIORITY, &interface.task_handle);

	xTaskCreate(steering_task, "Circle Drive", configMINIMAL_STACK_SIZE,
			NULL,
			hello_task_PRIORITY, &circle_handle);

	xTaskCreate(camera_task, "Camera_process",
	NUM_PIXELS * sizeof(uint16_t) * 2,
	NULL, hello_task_PRIORITY + 1, &camera.task_handle);

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
		PRINTF("motor_l: %d   motor_r: %d  servo: %d\r\n",
				motor_l.getRotationSpeed(), motor_r.getRotationSpeed(), servo.current_pulse_width);
		PRINTF("outer_l: %d  inner_l: %d  center: %d inner_r: %d  outer_r: %d\r\n\r\n",
				camera.camera_data.left_edge_outer,
				camera.camera_data.left_edge_inner,
				camera.camera_data.center,
				camera.camera_data.right_edge_inner,
				camera.camera_data.right_edge_outer);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

static void camera_task(void *pvParameters) {
	camera.calibrate();
	camera.process();
}

static void steering_task(void *pvParameters) {
	uint16_t position;
	for(;;) {
		position = (servo.right_pulse_width - servo.left_pulse_width) * (((float)NUM_PIXELS - (float)camera.camera_data.center) / (float)NUM_PIXELS) + servo.left_pulse_width;
		servo.set_position(position);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void print_interface() {
	interface.clear();
	interface.setCursor(0, 0);
	interface.print("TEST  CALIB  RUN");
	interface.setCursor(1, 1);
	interface.write(0x7F);
	interface.setCursor(8, 1);
	interface.write(0x5E);
	interface.setCursor(14, 1);
	interface.write(0x7E);
}

static void circle_drive_task(void *pvParameters) {
	vTaskSuspend(NULL);
	int position;
	for(;;) {
		servo.set_position(servo.left_pulse_width);
		vTaskDelay(pdMS_TO_TICKS(1000));
		servo.set_position(servo.center_pulse_width);
		vTaskDelay(pdMS_TO_TICKS(1000));
		servo.set_position(servo.right_pulse_width);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

static void user_interface_task(void *pvParameters) {
	interface.begin(16, 2, 0);
	print_interface();
	for (;;) {
		uint8_t button = interface.readButtons();
		if (button && button != 255) {
			interface.clear();
			interface.setCursor(0, 0);
			//start test
			if (button == BUTTON_LEFT) {
				interface.print("Running Test...");
				//start test task
				if ((eTaskGetState(motor_l.test_task_handle) == eSuspended)
						&& (eTaskGetState(motor_r.test_task_handle)
								== eSuspended)) {
					vTaskResume(motor_l.test_task_handle);
					vTaskResume(motor_r.test_task_handle);
				}
				if (eTaskGetState(servo.test_task_handle) == eSuspended) {
					vTaskResume(servo.test_task_handle);
				}
			}
			//start calibration
			else if (button == BUTTON_UP) {
				interface.print("Running Calibration");
				//start calibration task
			}
			//start running
			else if (button == BUTTON_RIGHT) {
				interface.print("Starting Car!");
				//run main driving task
				vTaskResume(&circle_handle);
			}
			//stop running
			else {
				interface.print("***ABORT***");
				motor_l.set_speed(0);
				motor_r.set_speed(0);

			}
			vTaskDelay(pdMS_TO_TICKS(1000));
			print_interface();
		}
		//lost i2c connection
		if (button == 255) {
			motor_l.set_speed(0);
			motor_r.set_speed(0);
		}

	}
}


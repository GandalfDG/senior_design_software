/*
 * interrupt_handlers.c
 *
 *  Created on: Feb 5, 2019
 *      Author: Jack
 */

#include "interrupt_handlers.h"

void FTM3_IRQHandler(void) {
	//TODO handle the timer overflow case, speed might temporarily be wrong if the timer overflows
	uint32_t capture_val_l = 0;
	uint32_t capture_val_r = 0;
	// read counter value from triggered channel(s)
	uint32_t encoder_l_flags = FTM_GetStatusFlags(motor_l.encoder_ftm_base)
			& (1 << motor_l.encoder_a_channel);
	uint32_t encoder_r_flags = FTM_GetStatusFlags(motor_r.encoder_ftm_base)
			& (1 << motor_r.encoder_a_channel);

	if (encoder_l_flags) {
		capture_val_l =
				motor_l.encoder_ftm_base->CONTROLS[motor_l.encoder_a_channel].CnV;
		FTM_ClearStatusFlags(motor_l.encoder_ftm_base,
				1u << motor_l.encoder_a_channel);
		motor_l.update_encoder_period(capture_val_l);
	}

	if (encoder_r_flags) {
		capture_val_r =
				motor_r.encoder_ftm_base->CONTROLS[motor_r.encoder_a_channel].CnV;
		FTM_ClearStatusFlags(motor_r.encoder_ftm_base,
				1u << motor_r.encoder_a_channel);
		motor_r.update_encoder_period(capture_val_r);
	}
}

//TODO clean this up a bit
void CAMERA_TIMER_IRQHandler(void) {
	int16_t pixel_num = 0;
	FTM_ClearStatusFlags(camera.ftm_base, 1u << camera.ftm_channel);
	camera.ftm_base->CNT = 0; //sync the timer

	//toggle the clock signal
	GPIO_PortToggle(camera.gpio_base, 1u << camera.clk_pin);

	pixel_num = camera.current_pixel;
	if(pixel_num >=2 && pixel_num < 256) {
		camera.line_buffer[pixel_num/2] = camera.adc_value;
		camera.current_pixel++;
	}
	//generate the SI pulse
	else if(pixel_num < 2) {
		if(pixel_num == -1) {
			GPIO_PinWrite(camera.gpio_base, camera.si_pin, 1);
		}
		else if(pixel_num == 1) {
			GPIO_PinWrite(camera.gpio_base, camera.si_pin, 0);
			camera.line_buffer[0] = camera.adc_value;
		}
		camera.current_pixel++;
	}
	else {
		GPIO_PinWrite(camera.gpio_base, camera.clk_pin, 0);
		camera.current_pixel = -2;

		FTM_DisableInterrupts(camera.ftm_base, 1u << camera.ftm_channel);
	}
}

void CAMERA_PIT_0_IRQHANDLER(void) {
	//clear PIT interrupt flag
	PIT_ClearStatusFlags(camera.pit_base, camera.pit_channel, kPIT_TimerFlag);

	// Setting mod resets the FTM counter
	//TODO Don't think this is necessary...
    //FTM2_MOD = DEFAULT_SYSTEM_CLOCK / 100000;

	//enable camera FTM interrupts to start capture
	FTM_EnableInterrupts(camera.ftm_base, 1u << camera.ftm_channel);
}




/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v5.0
processor: MK64FN1M0xxx12
package_id: MK64FN1M0VLL12
mcu_data: ksdk2_0
processor_version: 5.0.0
board: FRDM-K64F
functionalGroups:
- name: BOARD_InitPeripherals
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Motor_PWM initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'Motor_PWM'
- type: 'ftm'
- mode: 'EdgeAligned'
- type_id: 'ftm_04a15ae4af2b404bf2ae403c3dbe98b3'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'FTM0'
- config_sets:
  - ftm_main_config:
    - ftm_config:
      - clockSource: 'kFTM_SystemClock'
      - clockSourceFreq: 'GetFreq'
      - prescale: 'kFTM_Prescale_Divide_1'
      - timerFrequency: '10000'
      - bdmMode: 'kFTM_BdmMode_0'
      - pwmSyncMode: 'kFTM_SoftwareTrigger'
      - reloadPoints: ''
      - faultMode: 'kFTM_Fault_Disable'
      - faultFilterValue: '0'
      - deadTimePrescale: 'kFTM_Deadtime_Prescale_1'
      - deadTimeValue: '0'
      - extTriggers: ''
      - chnlInitState: ''
      - chnlPolarity: ''
      - useGlobalTimeBase: 'false'
    - timer_interrupts: ''
    - enable_irq: 'false'
    - ftm_interrupt:
      - IRQn: 'FTM0_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - EnableTimerInInit: 'true'
  - ftm_edge_aligned_mode:
    - ftm_edge_aligned_channels_config:
      - 0:
        - edge_aligned_mode: 'kFTM_EdgeAlignedPwm'
        - edge_aligned_pwm:
          - chnlNumber: 'kFTM_Chnl_0'
          - level: 'kFTM_HighTrue'
          - dutyCyclePercent: '0'
          - enable_chan_irq: 'false'
      - 1:
        - edge_aligned_mode: 'kFTM_EdgeAlignedPwm'
        - edge_aligned_pwm:
          - chnlNumber: 'kFTM_Chnl_1'
          - level: 'kFTM_HighTrue'
          - dutyCyclePercent: '0'
          - enable_chan_irq: 'false'
      - 2:
        - edge_aligned_mode: 'kFTM_EdgeAlignedPwm'
        - edge_aligned_pwm:
          - chnlNumber: 'kFTM_Chnl_2'
          - level: 'kFTM_HighTrue'
          - dutyCyclePercent: '0'
          - enable_chan_irq: 'false'
      - 3:
        - edge_aligned_mode: 'kFTM_EdgeAlignedPwm'
        - edge_aligned_pwm:
          - chnlNumber: 'kFTM_Chnl_3'
          - level: 'kFTM_HighTrue'
          - dutyCyclePercent: '0'
          - enable_chan_irq: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const ftm_config_t Motor_PWM_config = {
  .prescale = kFTM_Prescale_Divide_1,
  .bdmMode = kFTM_BdmMode_0,
  .pwmSyncMode = kFTM_SoftwareTrigger,
  .reloadPoints = 0,
  .faultMode = kFTM_Fault_Disable,
  .faultFilterValue = 0,
  .deadTimePrescale = kFTM_Deadtime_Prescale_1,
  .deadTimeValue = 0,
  .extTriggers = 0,
  .chnlInitState = 0,
  .chnlPolarity = 0,
  .useGlobalTimeBase = false
};

const ftm_chnl_pwm_signal_param_t Motor_PWM_pwmSignalParams[] = { 
  {
    .chnlNumber = kFTM_Chnl_0,
    .level = kFTM_HighTrue,
    .dutyCyclePercent = 0
  },
  {
    .chnlNumber = kFTM_Chnl_1,
    .level = kFTM_HighTrue,
    .dutyCyclePercent = 0
  },
  {
    .chnlNumber = kFTM_Chnl_2,
    .level = kFTM_HighTrue,
    .dutyCyclePercent = 0
  },
  {
    .chnlNumber = kFTM_Chnl_3,
    .level = kFTM_HighTrue,
    .dutyCyclePercent = 0
  }
};

void Motor_PWM_init(void) {
  FTM_Init(MOTOR_PWM_PERIPHERAL, &Motor_PWM_config);
  FTM_SetupPwm(MOTOR_PWM_PERIPHERAL, Motor_PWM_pwmSignalParams, sizeof(Motor_PWM_pwmSignalParams) / sizeof(ftm_chnl_pwm_signal_param_t), kFTM_EdgeAlignedPwm, 10000U, MOTOR_PWM_CLOCK_SOURCE);
  FTM_StartTimer(MOTOR_PWM_PERIPHERAL, kFTM_SystemClock);
}

/***********************************************************************************************************************
 * Servo_PWM initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'Servo_PWM'
- type: 'ftm'
- mode: 'EdgeAligned'
- type_id: 'ftm_04a15ae4af2b404bf2ae403c3dbe98b3'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'FTM2'
- config_sets:
  - ftm_main_config:
    - ftm_config:
      - clockSource: 'kFTM_SystemClock'
      - clockSourceFreq: 'GetFreq'
      - prescale: 'kFTM_Prescale_Divide_32'
      - timerFrequency: '50'
      - bdmMode: 'kFTM_BdmMode_0'
      - pwmSyncMode: 'kFTM_SoftwareTrigger'
      - reloadPoints: ''
      - faultMode: 'kFTM_Fault_Disable'
      - faultFilterValue: '0'
      - deadTimePrescale: 'kFTM_Deadtime_Prescale_1'
      - deadTimeValue: '0'
      - extTriggers: ''
      - chnlInitState: ''
      - chnlPolarity: ''
      - useGlobalTimeBase: 'false'
    - timer_interrupts: ''
    - enable_irq: 'false'
    - ftm_interrupt:
      - IRQn: 'FTM2_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - EnableTimerInInit: 'true'
  - ftm_edge_aligned_mode:
    - ftm_edge_aligned_channels_config:
      - 0:
        - edge_aligned_mode: 'kFTM_EdgeAlignedPwm'
        - edge_aligned_pwm:
          - chnlNumber: 'kFTM_Chnl_0'
          - level: 'kFTM_HighTrue'
          - dutyCyclePercent: '0'
          - enable_chan_irq: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const ftm_config_t Servo_PWM_config = {
  .prescale = kFTM_Prescale_Divide_32,
  .bdmMode = kFTM_BdmMode_0,
  .pwmSyncMode = kFTM_SoftwareTrigger,
  .reloadPoints = 0,
  .faultMode = kFTM_Fault_Disable,
  .faultFilterValue = 0,
  .deadTimePrescale = kFTM_Deadtime_Prescale_1,
  .deadTimeValue = 0,
  .extTriggers = 0,
  .chnlInitState = 0,
  .chnlPolarity = 0,
  .useGlobalTimeBase = false
};

const ftm_chnl_pwm_signal_param_t Servo_PWM_pwmSignalParams[] = { 
  {
    .chnlNumber = kFTM_Chnl_0,
    .level = kFTM_HighTrue,
    .dutyCyclePercent = 0
  }
};

void Servo_PWM_init(void) {
  FTM_Init(SERVO_PWM_PERIPHERAL, &Servo_PWM_config);
  FTM_SetupPwm(SERVO_PWM_PERIPHERAL, Servo_PWM_pwmSignalParams, sizeof(Servo_PWM_pwmSignalParams) / sizeof(ftm_chnl_pwm_signal_param_t), kFTM_EdgeAlignedPwm, 50U, SERVO_PWM_CLOCK_SOURCE);
  FTM_StartTimer(SERVO_PWM_PERIPHERAL, kFTM_SystemClock);
}

/***********************************************************************************************************************
 * User_I2C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'User_I2C'
- type: 'i2c'
- mode: 'I2C_Polling'
- type_id: 'i2c_2566d7363e7e9aaedabb432110e372d7'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'I2C0'
- config_sets:
  - fsl_i2c:
    - i2c_mode: 'kI2C_Master'
    - clockSource: 'BusInterfaceClock'
    - clockSourceFreq: 'GetFreq'
    - i2c_master_config:
      - enableMaster: 'true'
      - enableStopHold: 'false'
      - baudRate_Bps: '100000'
      - glitchFilterWidth: '0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const i2c_master_config_t User_I2C_config = {
  .enableMaster = true,
  .enableStopHold = false,
  .baudRate_Bps = 100000,
  .glitchFilterWidth = 0
};

void User_I2C_init(void) {
  /* Initialization function */
  I2C_MasterInit(USER_I2C_PERIPHERAL, &User_I2C_config, USER_I2C_CLK_FREQ);
}

/***********************************************************************************************************************
 * UART_0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'UART_0'
- type: 'uart'
- mode: 'polling'
- type_id: 'uart_cd31a12aa8c79051fda42cc851a27c37'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'UART0'
- config_sets:
  - uartConfig_t:
    - uartConfig:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'GetFreq'
      - baudRate_Bps: '115200'
      - parityMode: 'kUART_ParityDisabled'
      - stopBitCount: 'kUART_OneStopBit'
      - txFifoWatermark: '0'
      - rxFifoWatermark: '1'
      - idleType: 'kUART_IdleTypeStartBit'
      - enableTx: 'true'
      - enableRx: 'true'
    - quick_selection: 'QuickSelection1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const uart_config_t UART_0_config = {
  .baudRate_Bps = 115200,
  .parityMode = kUART_ParityDisabled,
  .stopBitCount = kUART_OneStopBit,
  .txFifoWatermark = 0,
  .rxFifoWatermark = 1,
  .idleType = kUART_IdleTypeStartBit,
  .enableTx = true,
  .enableRx = true
};

void UART_0_init(void) {
  UART_Init(UART_0_PERIPHERAL, &UART_0_config, UART_0_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * GPIO_A initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO_A'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_be9de87e5addb6b0f416d9acbab34797'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIOA'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'true'
    - port_interrupt:
      - IRQn: 'PORTA_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void GPIO_A_init(void) {
  /* Make sure, the clock gate for port A is enabled (e. g. in pin_mux.c) */
  /* Enable interrupt PORTA_IRQn request in the NVIC */
  EnableIRQ(PORTA_IRQn);
}

/***********************************************************************************************************************
 * GPIO_C initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO_C'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_be9de87e5addb6b0f416d9acbab34797'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIOC'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'true'
    - port_interrupt:
      - IRQn: 'PORTC_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void GPIO_C_init(void) {
  /* Make sure, the clock gate for port C is enabled (e. g. in pin_mux.c) */
  /* Enable interrupt PORTC_IRQn request in the NVIC */
  EnableIRQ(PORTC_IRQn);
}

/***********************************************************************************************************************
 * RTC_1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'RTC_1'
- type: 'rtc'
- mode: 'general'
- type_id: 'rtc_5a0edd77b33c110032c2a0f5e3d1bd2f'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'RTC'
- config_sets:
  - fsl_rtc:
    - clockConfig_t: []
    - rtc_config:
      - updateMode: 'false'
      - supervisorAccess: 'false'
      - compensationIntervalInt: '1'
      - compensationTimeInt: '0'
      - setDateTime: 'false'
      - setAlarm: 'false'
      - start: 'false'
    - interruptsCfg:
      - interruptSources: ''
      - isSecondsInterruptEnabled: 'false'
      - secondsInterrupt:
        - IRQn: 'RTC_Seconds_IRQn'
        - enable_priority: 'false'
        - enable_custom_name: 'false'
      - isInterruptEnabled: 'false'
      - commonInterrupt:
        - IRQn: 'RTC_IRQn'
        - enable_priority: 'false'
        - enable_custom_name: 'false'
    - quick_selection: 'QuickSelection1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const rtc_config_t RTC_1_config = {
  .wakeupSelect = false,
  .updateMode = false,
  .supervisorAccess = false,
  .compensationInterval = 0x0U,
  .compensationTime = 0x0U
};

void RTC_1_init(void) {
  /* RTC initialization */
  RTC_Init(RTC_1_PERIPHERAL, &RTC_1_config);
}

/***********************************************************************************************************************
 * Camera_ADC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'Camera_ADC'
- type: 'adc16'
- mode: 'ADC'
- type_id: 'adc16_7d827be2dc433dc756d94a7ce88cbcc5'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'ADC0'
- config_sets:
  - fsl_adc16:
    - adc16_config:
      - referenceVoltageSource: 'kADC16_ReferenceVoltageSourceVref'
      - clockSource: 'kADC16_ClockSourceAsynchronousClock'
      - enableAsynchronousClock: 'true'
      - clockDivider: 'kADC16_ClockDivider8'
      - resolution: 'kADC16_ResolutionSE16Bit'
      - longSampleMode: 'kADC16_LongSampleDisabled'
      - enableHighSpeed: 'false'
      - enableLowPower: 'false'
      - enableContinuousConversion: 'false'
    - adc16_channel_mux_mode: 'kADC16_ChannelMuxA'
    - adc16_hardware_compare_config:
      - hardwareCompareModeEnable: 'false'
    - doAutoCalibration: 'true'
    - trigger: 'true'
    - hardwareAverageConfiguration: 'kADC16_HardwareAverageDisabled'
    - enable_dma: 'false'
    - enable_irq: 'true'
    - adc_interrupt:
      - IRQn: 'ADC0_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - adc16_channels_config:
      - 0:
        - enableDifferentialConversion: 'false'
        - channelNumber: 'SE.0'
        - enableInterruptOnConversionCompleted: 'true'
        - channelGroup: '0'
        - initializeChannel: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
adc16_channel_config_t Camera_ADC_channelsConfig[1] = {
  {
    .channelNumber = 0U,
    .enableDifferentialConversion = false,
    .enableInterruptOnConversionCompleted = true,
  }
};
const adc16_config_t Camera_ADC_config = {
  .referenceVoltageSource = kADC16_ReferenceVoltageSourceVref,
  .clockSource = kADC16_ClockSourceAsynchronousClock,
  .enableAsynchronousClock = true,
  .clockDivider = kADC16_ClockDivider8,
  .resolution = kADC16_ResolutionSE16Bit,
  .longSampleMode = kADC16_LongSampleDisabled,
  .enableHighSpeed = false,
  .enableLowPower = false,
  .enableContinuousConversion = false
};
const adc16_channel_mux_mode_t Camera_ADC_muxMode = kADC16_ChannelMuxA;
const adc16_hardware_average_mode_t Camera_ADC_hardwareAverageMode = kADC16_HardwareAverageDisabled;

void Camera_ADC_init(void) {
  /* Enable interrupt CAMERA_ADC_IRQN request in the NVIC */
  EnableIRQ(CAMERA_ADC_IRQN);
  /* Initialize ADC16 converter */
  ADC16_Init(CAMERA_ADC_PERIPHERAL, &Camera_ADC_config);
  /* Make sure, that hardware trigger is used */
  ADC16_EnableHardwareTrigger(CAMERA_ADC_PERIPHERAL, true);
  /* Configure hardware average mode */
  ADC16_SetHardwareAverage(CAMERA_ADC_PERIPHERAL, Camera_ADC_hardwareAverageMode);
  /* Configure channel multiplexing mode */
  ADC16_SetChannelMuxMode(CAMERA_ADC_PERIPHERAL, Camera_ADC_muxMode);
  /* Perform auto calibration */
  ADC16_DoAutoCalibration(CAMERA_ADC_PERIPHERAL);
}

/***********************************************************************************************************************
 * GPIO_D initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIO_D'
- type: 'gpio'
- mode: 'GPIO'
- type_id: 'gpio_be9de87e5addb6b0f416d9acbab34797'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIOD'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'true'
    - port_interrupt:
      - IRQn: 'PORTD_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void GPIO_D_init(void) {
  /* Make sure, the clock gate for port D is enabled (e. g. in pin_mux.c) */
  /* Enable interrupt PORTD_IRQn request in the NVIC */
  EnableIRQ(PORTD_IRQn);
}

/***********************************************************************************************************************
 * Encoder_Timer initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'Encoder_Timer'
- type: 'ftm'
- mode: 'EdgeAligned'
- type_id: 'ftm_04a15ae4af2b404bf2ae403c3dbe98b3'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'FTM3'
- config_sets:
  - ftm_main_config:
    - ftm_config:
      - clockSource: 'kFTM_SystemClock'
      - clockSourceFreq: 'GetFreq'
      - prescale: 'kFTM_Prescale_Divide_1'
      - timerFrequency: '10000'
      - bdmMode: 'kFTM_BdmMode_0'
      - pwmSyncMode: 'kFTM_SoftwareTrigger'
      - reloadPoints: ''
      - faultMode: 'kFTM_Fault_Disable'
      - faultFilterValue: '0'
      - deadTimePrescale: 'kFTM_Deadtime_Prescale_1'
      - deadTimeValue: '0'
      - extTriggers: ''
      - chnlInitState: ''
      - chnlPolarity: ''
      - useGlobalTimeBase: 'false'
    - timer_interrupts: ''
    - enable_irq: 'false'
    - ftm_interrupt:
      - IRQn: 'FTM3_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - EnableTimerInInit: 'true'
    - quick_selection: 'QuickSelectionDefault'
  - ftm_edge_aligned_mode:
    - ftm_edge_aligned_channels_config:
      - 0:
        - edge_aligned_mode: 'kFTM_InputCapture'
        - input_capture:
          - chnNumber: 'kFTM_Chnl_4'
          - input_capture_edge: 'kFTM_RisingEdge'
          - filterValue: '0'
          - enable_chan_irq: 'true'
      - 1:
        - edge_aligned_mode: 'kFTM_InputCapture'
        - input_capture:
          - chnNumber: 'kFTM_Chnl_5'
          - input_capture_edge: 'kFTM_RisingEdge'
          - filterValue: '0'
          - enable_chan_irq: 'true'
      - 2:
        - edge_aligned_mode: 'kFTM_InputCapture'
        - input_capture:
          - chnNumber: 'kFTM_Chnl_6'
          - input_capture_edge: 'kFTM_RisingEdge'
          - filterValue: '0'
          - enable_chan_irq: 'true'
      - 3:
        - edge_aligned_mode: 'kFTM_InputCapture'
        - input_capture:
          - chnNumber: 'kFTM_Chnl_7'
          - input_capture_edge: 'kFTM_RisingEdge'
          - filterValue: '0'
          - enable_chan_irq: 'true'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const ftm_config_t Encoder_Timer_config = {
  .prescale = kFTM_Prescale_Divide_1,
  .bdmMode = kFTM_BdmMode_0,
  .pwmSyncMode = kFTM_SoftwareTrigger,
  .reloadPoints = 0,
  .faultMode = kFTM_Fault_Disable,
  .faultFilterValue = 0,
  .deadTimePrescale = kFTM_Deadtime_Prescale_1,
  .deadTimeValue = 0,
  .extTriggers = 0,
  .chnlInitState = 0,
  .chnlPolarity = 0,
  .useGlobalTimeBase = false
};

void Encoder_Timer_init(void) {
  FTM_Init(ENCODER_TIMER_PERIPHERAL, &Encoder_Timer_config);
  FTM_SetupInputCapture(ENCODER_TIMER_PERIPHERAL, kFTM_Chnl_4, kFTM_RisingEdge, 0);
  FTM_SetupInputCapture(ENCODER_TIMER_PERIPHERAL, kFTM_Chnl_5, kFTM_RisingEdge, 0);
  FTM_SetupInputCapture(ENCODER_TIMER_PERIPHERAL, kFTM_Chnl_6, kFTM_RisingEdge, 0);
  FTM_SetupInputCapture(ENCODER_TIMER_PERIPHERAL, kFTM_Chnl_7, kFTM_RisingEdge, 0);
  FTM_SetTimerPeriod(ENCODER_TIMER_PERIPHERAL, ((ENCODER_TIMER_CLOCK_SOURCE/ (1U << (ENCODER_TIMER_PERIPHERAL->SC & FTM_SC_PS_MASK))) / 10000) + 1);
  FTM_EnableInterrupts(ENCODER_TIMER_PERIPHERAL, kFTM_Chnl4InterruptEnable | kFTM_Chnl5InterruptEnable | kFTM_Chnl6InterruptEnable | kFTM_Chnl7InterruptEnable);
  FTM_StartTimer(ENCODER_TIMER_PERIPHERAL, kFTM_SystemClock);
}

/***********************************************************************************************************************
 * Camera_Timer initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'Camera_Timer'
- type: 'ftm'
- mode: 'EdgeAligned'
- type_id: 'ftm_04a15ae4af2b404bf2ae403c3dbe98b3'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'FTM1'
- config_sets:
  - ftm_main_config:
    - ftm_config:
      - clockSource: 'kFTM_SystemClock'
      - clockSourceFreq: 'GetFreq'
      - prescale: 'kFTM_Prescale_Divide_1'
      - timerFrequency: '10000'
      - bdmMode: 'kFTM_BdmMode_0'
      - pwmSyncMode: 'kFTM_SoftwareTrigger'
      - reloadPoints: ''
      - faultMode: 'kFTM_Fault_Disable'
      - faultFilterValue: '0'
      - deadTimePrescale: 'kFTM_Deadtime_Prescale_1'
      - deadTimeValue: '0'
      - extTriggers: ''
      - chnlInitState: ''
      - chnlPolarity: ''
      - useGlobalTimeBase: 'false'
    - timer_interrupts: ''
    - enable_irq: 'true'
    - ftm_interrupt:
      - IRQn: 'FTM1_IRQn'
      - enable_priority: 'false'
      - enable_custom_name: 'false'
    - EnableTimerInInit: 'true'
  - ftm_edge_aligned_mode:
    - ftm_edge_aligned_channels_config: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const ftm_config_t Camera_Timer_config = {
  .prescale = kFTM_Prescale_Divide_1,
  .bdmMode = kFTM_BdmMode_0,
  .pwmSyncMode = kFTM_SoftwareTrigger,
  .reloadPoints = 0,
  .faultMode = kFTM_Fault_Disable,
  .faultFilterValue = 0,
  .deadTimePrescale = kFTM_Deadtime_Prescale_1,
  .deadTimeValue = 0,
  .extTriggers = 0,
  .chnlInitState = 0,
  .chnlPolarity = 0,
  .useGlobalTimeBase = false
};

void Camera_Timer_init(void) {
  FTM_Init(CAMERA_TIMER_PERIPHERAL, &Camera_Timer_config);
  FTM_SetTimerPeriod(CAMERA_TIMER_PERIPHERAL, ((CAMERA_TIMER_CLOCK_SOURCE/ (1U << (CAMERA_TIMER_PERIPHERAL->SC & FTM_SC_PS_MASK))) / 10000) + 1);
  /* Enable interrupt FTM1_IRQn request in the NVIC */
  EnableIRQ(CAMERA_TIMER_IRQN);
  FTM_StartTimer(CAMERA_TIMER_PERIPHERAL, kFTM_SystemClock);
}

/***********************************************************************************************************************
 * Bluetooth_UART initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'Bluetooth_UART'
- type: 'uart'
- mode: 'polling'
- type_id: 'uart_cd31a12aa8c79051fda42cc851a27c37'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'UART3'
- config_sets:
  - uartConfig_t:
    - uartConfig:
      - clockSource: 'BusInterfaceClock'
      - clockSourceFreq: 'GetFreq'
      - baudRate_Bps: '9600'
      - parityMode: 'kUART_ParityDisabled'
      - stopBitCount: 'kUART_OneStopBit'
      - txFifoWatermark: '0'
      - rxFifoWatermark: '1'
      - idleType: 'kUART_IdleTypeStartBit'
      - enableTx: 'true'
      - enableRx: 'true'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const uart_config_t Bluetooth_UART_config = {
  .baudRate_Bps = 9600,
  .parityMode = kUART_ParityDisabled,
  .stopBitCount = kUART_OneStopBit,
  .txFifoWatermark = 0,
  .rxFifoWatermark = 1,
  .idleType = kUART_IdleTypeStartBit,
  .enableTx = true,
  .enableRx = true
};

void Bluetooth_UART_init(void) {
  UART_Init(BLUETOOTH_UART_PERIPHERAL, &Bluetooth_UART_config, BLUETOOTH_UART_CLOCK_SOURCE);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  Motor_PWM_init();
  Servo_PWM_init();
  User_I2C_init();
  UART_0_init();
  GPIO_A_init();
  GPIO_C_init();
  RTC_1_init();
  Camera_ADC_init();
  GPIO_D_init();
  Encoder_Timer_init();
  Camera_Timer_init();
  Bluetooth_UART_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}

/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_DEF_H
#define __SYSTEM_DEF_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_adc1.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/*--------------------------------USER CONFIGABLE-----------------------------*/
//Node Address
#define SLAVE_NODE_ADDRESS                      1
#define MASTER_NODE_ADDRESS                     0

#define DIMMING_PERIOD_IN_MS_SECOND             1000     ///500ms

/*-------------------------------Do not change the value----------------------*/

//System
#define SYSTEM_CLK                      16000000        //16MHz

//For IR Transmitter
#define IR_TRANSMITTER_FREQ             225     //100Hz
#define IR_TRANSMITTER_PORT             GPIOA
#define IR_TRANSMITTER_PIN              GPIO_PIN_3

//For IR Reciever
#define IR_RECEIVER_ADC_CHANNEL         ADC1_CHANNEL_4          //AIN4 channel4
#define IR_RECEIVER_SIGNAL_FREQ         IR_TRANSMITTER_FREQ
//For timer counter
#define TIMER_COUNTER_PRESCALER         16
#define TIMER_COUNTER_CLK               (SYSTEM_CLK/TIMER_COUNTER_PRESCALER)
#define TIMER_COUNTER_CMP               100
#define TIMER_COUNTER_TICK_IN_SECOND    (TIMER_COUNTER_CLK/TIMER_COUNTER_CMP)
#define TIMER_COUNTER_TICK_IN_MS        (TIMER_COUNTER_TICK_IN_SECOND/1000)

//For timer pwm
//#define TIMER_COUNTER_PRESCALER         16
//#define TIMER_COUNTER_CLK               (SYSTEM_CLK/TIMER_COUNTER_PRESCALER)
//#define TIMER_COUNTER_CMP               50
//#define TIMER_COUNTER_TICK_IN_SECOND    (TIMER_COUNTER_CLK/TIMER_COUNTER_CMP)
//#define TIMER_COUNTER_TICK_IN_MS        (TIMER_COUNTER_TICK_IN_SECOND/1000)

///For task manager

//For IR Receiver
#define IR_RECEIVER_PULSE_WITHD_IN_MS                   (1000/IR_TRANSMITTER_FREQ/2)
#define IR_RECEIVER_SHORT_PULSE_TIME_OUT_IN_MS          80
#define IR_RECEIVER_LONG_PULSE_TIME_OUT_IN_MS           400
#define IR_RECEIVER_SHORT_PULSE_PULSE_COUNTER           (IR_RECEIVER_SHORT_PULSE_TIME_OUT_IN_MS/IR_RECEIVER_PULSE_WITHD_IN_MS)
#define IR_RECEIVER_LONG_PULSE_PULSE_COUNTER            (IR_RECEIVER_LONG_PULSE_TIME_OUT_IN_MS/IR_RECEIVER_PULSE_WITHD_IN_MS)
#define IR_RECEIVER_SHORT_PULSE_THRESHOLD_COUNTER       20
#define TWO_PULSE_TIME_OUT_IN_MS                        3


//For RS485 Controller
#define TRANSPORT_BAUDRATE                      57600
    
#define TRANSPORT_OUTPUT_DRIVER_PORT            GPIOA
#define TRANSPORT_OUTPUT_DRIVER_PIN             GPIO_PIN_2

//For state manager
#define STATE_MANAGER_PARALLEL_LEDS             YES

//Led Output 
#define LED_CONTROL_PORT                        GPIOD
#define LED_CONTROL_PIN                         GPIO_PIN_4

#define INDICATOR_LED_PORT                      GPIOB
#define INDICATOR_LED_PIN                       GPIO_PIN_5

#define DIGITAL_INPUT_PORT                      GPIOA
#define DIGITAL_INPUT_PIN                       GPIO_PIN_2
#define DIGITAL_OUTPUT_PORT                     GPIOA
#define DIGITAL_OUTPUT_PIN                      GPIO_PIN_1

//#define DIGITAL_INPUT_PORT                      GPIOC
//#define DIGITAL_INPUT_PIN                       GPIO_PIN_7
//#define DIGITAL_OUTPUT_PORT                     GPIOC
//#define DIGITAL_OUTPUT_PIN                      GPIO_PIN_6

//For Debug Purpose
#define LED_PORT                                GPIOB
#define LED_PIN                                 GPIO_PIN_5


/* Exported functions ------------------------------------------------------- */

#endif /* __SYSTEM_DEF_H */


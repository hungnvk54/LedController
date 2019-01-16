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
//System
#define SYSTEM_CLK                      16000000        //16MHz

//For Debug Purpose
#define LED_PORT                        GPIOB
#define LED_PIN                         GPIO_PIN_5

//For IR Transmitter
#define IR_TRANSMITTER_FREQ             500     //100Hz
#define IR_TRANSMITTER_PORT             GPIOA
#define IR_TRANSMITTER_PIN              GPIO_PIN_3

//For IR Reciever
#define IR_RECEIVER_ADC_CHANNEL         ADC1_CHANNEL_4          //AIN4 channel4
#define IR_RECEIVER_SIGNAL_FREQ         IR_TRANSMITTER_FREQ
//For timer counter
#define TIMER_COUNTER_PRESCALER         16
#define TIMER_COUNTER_CLK               (SYSTEM_CLK/TIMER_COUNTER_PRESCALER)
#define TIMER_COUNTER_CMP               50
#define TIMER_COUNTER_TICK_IN_SECOND    (TIMER_COUNTER_CLK/TIMER_COUNTER_CMP)
#define TIMER_COUNTER_TICK_IN_MS        (TIMER_COUNTER_TICK_IN_SECOND/1000)

//For timer pwm
#define TIMER_COUNTER_PRESCALER         16
#define TIMER_COUNTER_CLK               (SYSTEM_CLK/TIMER_COUNTER_PRESCALER)
#define TIMER_COUNTER_CMP               50
#define TIMER_COUNTER_TICK_IN_SECOND    (TIMER_COUNTER_CLK/TIMER_COUNTER_CMP)
#define TIMER_COUNTER_TICK_IN_MS        (TIMER_COUNTER_TICK_IN_SECOND/1000)

///For task manager


//For RS485 Controller
#define TRANSPORT_BAUDRATE                      19200
    
#define TRANSPORT_OUTPUT_DRIVER_PORT            GPIOA
#define TRANSPORT_OUTPUT_DRIVER_PIN             GPIO_PIN_2

//For state manager
#define STATE_MANAGER_PARALLEL_LEDS            YES
/* Exported functions ------------------------------------------------------- */

#endif /* __SYSTEM_DEF_H */


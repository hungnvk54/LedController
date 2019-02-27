/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  * ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "ir_transmitter.h"
#include "gpio_util.h"
#include "timer_pwm.h"
#include "system_def.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t time_prescaler = 2;
IR_Output_Mode_TypeDef running_mode = IR_OUTPUT_MODE_PWM;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void IR_Transmitter_Init(IR_Output_Mode_TypeDef mode)
{
  if( IR_OUTPUT_MODE_IO == mode )
  {
    GPIO_Util_Init(IR_TRANSMITTER_PORT,IR_TRANSMITTER_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
  } else if( IR_OUTPUT_MODE_PWM == mode ) 
  {
    Timer_PWM_IR_Transmitter_Init();
  }
  running_mode = mode;
}
 
void IR_Transmitter_Task(void *args)
{
  ///This task is peridically called in 1ms, so The max frequency is 500Hz
  if( IR_OUTPUT_MODE_IO == running_mode)
  {
    if( time_prescaler == U8_MAX) {
      GPIO_Util_WriteLow(IR_TRANSMITTER_PORT,IR_TRANSMITTER_PIN);
    } else {
      static uint8_t counter = 0;
      counter++;
      if( counter >= time_prescaler ) {
        counter = 0;
        GPIO_Util_Toggle(IR_TRANSMITTER_PORT, IR_TRANSMITTER_PIN);
      }
    }
  }
}

void IR_Transmitter_SetPrescaler(uint8_t scale)
{
  if( scale == U8_MAX ) time_prescaler = scale;
  else time_prescaler = scale + 1;
}

IR_Output_Mode_TypeDef IR_Transmitter_GetMode(void)
{
  return running_mode;
}
/**
  * @}
  */



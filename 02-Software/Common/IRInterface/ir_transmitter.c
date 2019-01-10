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
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t time_prescaler = 1;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void IR_Transmitter_Init(IR_Output_Mode_TypeDef mode)
{
  if( IR_OUTPUT_MODE_IO == mode )
  {
    GPIO_Util_Init_As_Out(IR_TRANSMITTER_PORT,IR_TRANSMITTER_PIN);
  } else if( IR_OUTPUT_MODE_PWM == mode )
  {
    Timer_PWM_IR_Transmitter_Init();
  }
}


void IR_Transmitter_PerformTask(void *args)
{
  ///This task is peridically called in 1ms, so The max frequency is 500Hz
  static uint8_t counter = 0;
  counter++;
  if( counter >= time_prescaler ) {
    counter = 0;
    GPIO_Util_Toggle(IR_TRANSMITTER_PORT, IR_TRANSMITTER_PIN);
  }
}
/**
  * @}
  */



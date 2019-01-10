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
#include "led_controller.h"
#include "timer_pwm.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Led_Control_Immediate(GPIO_State_TypeDef state);
/* Public functions ----------------------------------------------------------*/
   
/**
  * @brief   Control the output base on the passed mode
  * @par Full description:
  *  the Controller will turn on/off led base on passed mode
  * @param   
  * port: Port of the Led
  * pin: Pin Of the Led
  * mode: Control mode: Immediate or dimming
  * On/Off
  * @retval None
  */
void Led_Control_Cmd( GPIO_TypeDef port, GPIO_Pin_TypeDef pin,  \
                    Control_Mode_TypeDef mode, GPIO_State_TypeDef state
                    )
{
  if( CONTROL_MODE_DIMMING == mode )
  {
    Led_Control_Immediate(state);
  } else if( CONTROL_MODE_IMMEDIATE == mode )
  {
    Timer_PWM_Start(state);
  }
}

void Led_Control_Immediate(GPIO_State_TypeDef state)
{
  if( GPIO_STATE_ON == state)
  {
    GPIO_WriteHigh(LED_PORT,LED_PIN);
  } else 
  {
    GPIO_WriteLow(LED_PORT,LED_PIN);
  }
}

void Led_Control_Init(Control_Mode_TypeDef mode)
{
  if( CONTROL_MODE_IMMEDIATE == mode )
  {
    GPIO_Util_Init_As_Out(LED_PORT,LED_PIN);
  } else {
    Timer_PWM_Init();
  }
}

/**
  * @}
  */



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
#include "util.h"
#include "led_controller.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void Delay_Us(uint32_t t)
{
  while(--t);
}
void Generate_TestingSignal(void)
{
  //Get Current mode of the Controller
  GPIO_Util_Init(LED_CONTROL_PORT,LED_CONTROL_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Util_Init(INDICATOR_LED_PORT,INDICATOR_LED_PIN,GPIO_MODE_OUT_OD_LOW_FAST);
  
  GPIO_Util_TurnOnLed(LED_CONTROL_PORT,LED_CONTROL_PIN);
  GPIO_Util_TurnOnLed(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
  Delay_Us(500000);
  GPIO_Util_TurnOffLed(LED_CONTROL_PORT,LED_CONTROL_PIN);
  GPIO_Util_TurnOffLed(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
  
  Delay_Us(500000);
  GPIO_Util_TurnOnLed(LED_CONTROL_PORT,LED_CONTROL_PIN);
  GPIO_Util_TurnOnLed(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
  
  Delay_Us(500000);
  GPIO_Util_TurnOffLed(LED_CONTROL_PORT,LED_CONTROL_PIN);
  GPIO_Util_TurnOffLed(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
}
void Wait_SystemStable(void)
{
  
}
/**
  * @}
  */



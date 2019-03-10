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
  t = t >> 1;
  while(t != 0){
    t--;
  }
}
void Generate_TestingSignal(void)
{
  uint8_t n = 6;
  //Get Current mode of the Controller
  GPIO_Util_Init(LED_CONTROL_PORT,LED_CONTROL_PIN,GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Util_Init(INDICATOR_LED_PORT,INDICATOR_LED_PIN,GPIO_MODE_OUT_PP_LOW_FAST);
  
  while( n--) {
    GPIO_Util_Toggle(LED_CONTROL_PORT,LED_CONTROL_PIN);
    GPIO_Util_Toggle(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
    Delay_Us(100000);
  }
}
void Wait_SystemStable(void)
{
  
}
/**
  * @}
  */



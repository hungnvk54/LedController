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
#include "gpio_util.h"
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
   
/**
  * @brief   Control the output base on the passed mode
  * @par Full description:
  *  
  * @param   
  * 
  * @retval None
  */
//void GPIO_Util_Init(void)
//{
//  //Only init the Necessary pin
//  GPIO_Init(LED_PORT,LED_PIN,GPIO_MODE_OUT_OD_LOW_SLOW);
//}
void GPIO_Util_Init_As_Out(GPIO_TypeDef *port, GPIO_Pin_TypeDef pin)
{
  GPIO_Init(port,pin,GPIO_MODE_OUT_OD_LOW_SLOW);
}
void GPIO_Util_Init_As_In(GPIO_TypeDef *port, GPIO_Pin_TypeDef pin)
{
  GPIO_Init(port,pin,GPIO_MODE_IN_PU_NO_IT);
}
    
void GPIO_Util_WriteValue(GPIO_TypeDef* port, uint8_t value)
{
  GPIO_Write(port,value);
}
void GPIO_Util_WriteHigh(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin)
{
  GPIO_WriteHigh(port,pin);
}
void GPIO_Util_WriteLow(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin)
{
  GPIO_WriteLow(port,pin);
}
uint8_t GPIO_Util_ReadValue(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin)
{
  return (GPIO_ReadOutputData(port) & pin);
}

void GPIO_Util_Toggle(GPIO_TypeDef *port, GPIO_Pin_TypeDef pin)
{
  uint8_t value = GPIO_Util_ReadValue(port,pin) ^ pin;
  if( value & pin ){
    GPIO_Util_WriteHigh(port,pin);
  } else {
    GPIO_Util_WriteLow(port,pin);
  }
}

/**
  * @}
  */



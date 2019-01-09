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
#ifndef __GPIO_UTIL_H
#define __GPIO_UTIL_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Exported types ------------------------------------------------------------*/

typedef enum {
  GPIO_STATE_ON,
  GPIO_STATE_OFF
} GPIO_State_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LED_PORT                GPIOB
#define LED_PIN                 GPIO_PIN_5

/* Exported functions ------------------------------------------------------- */
void GPIO_Util_Init(void);
void GPIO_Util_WriteValue(GPIO_TypeDef* port, uint8_t value);
void GPIO_Util_WriteHigh(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin);
void GPIO_Util_WriteLow(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin);
uint8_t GPIO_Util_ReadValue(GPIO_TypeDef* port, GPIO_Pin_TypeDef pin);
#endif /* __GPIO_UTIL_H */


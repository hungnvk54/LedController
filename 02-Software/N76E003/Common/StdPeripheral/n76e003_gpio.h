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
#ifndef __N76E003_GPIO_H
#define __N76E003_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* Exported types ------------------------------------------------------------*/
/*Define Inout Type*/
typedef enum
{
  GPIO_MODE_IN_FL_NO_IT      = (uint8_t)0x00,  /*!< Input floating, no external interrupt */
  GPIO_MODE_IN_PU_NO_IT      = (uint8_t)0x40,  /*!< Input pull-up, no external interrupt */
  GPIO_MODE_IN_FL_IT         = (uint8_t)0x20,  /*!< Input floating, external interrupt */
  GPIO_MODE_IN_PU_IT         = (uint8_t)0x60,  /*!< Input pull-up, external interrupt */
  GPIO_MODE_OUT_OD_LOW_FAST  = (uint8_t)0xA0,  /*!< Output open-drain, low level, 10MHz */
  GPIO_MODE_OUT_PP_LOW_FAST  = (uint8_t)0xE0,  /*!< Output push-pull, low level, 10MHz */
  GPIO_MODE_OUT_OD_LOW_SLOW  = (uint8_t)0x80,  /*!< Output open-drain, low level, 2MHz */
  GPIO_MODE_OUT_PP_LOW_SLOW  = (uint8_t)0xC0,  /*!< Output push-pull, low level, 2MHz */
  GPIO_MODE_OUT_OD_HIZ_FAST  = (uint8_t)0xB0,  /*!< Output open-drain, high-impedance level,10MHz */
  GPIO_MODE_OUT_PP_HIGH_FAST = (uint8_t)0xF0,  /*!< Output push-pull, high level, 10MHz */
  GPIO_MODE_OUT_OD_HIZ_SLOW  = (uint8_t)0x90,  /*!< Output open-drain, high-impedance level, 2MHz */
  GPIO_MODE_OUT_PP_HIGH_SLOW = (uint8_t)0xD0   /*!< Output push-pull, high level, 2MHz */
}GPIO_Mode_TypeDef;

/**
  * @brief  Definition of the GPIO pins. Used by the @ref GPIO_Init function in
  * order to select the pins to be initialized.
  */

typedef enum
{
  GPIO_PIN_0    = ((uint8_t)0x01),  /*!< Pin 0 selected */
  GPIO_PIN_1    = ((uint8_t)0x02),  /*!< Pin 1 selected */
  GPIO_PIN_2    = ((uint8_t)0x04),  /*!< Pin 2 selected */
  GPIO_PIN_3    = ((uint8_t)0x08),   /*!< Pin 3 selected */
  GPIO_PIN_4    = ((uint8_t)0x10),  /*!< Pin 4 selected */
  GPIO_PIN_5    = ((uint8_t)0x20),  /*!< Pin 5 selected */
  GPIO_PIN_6    = ((uint8_t)0x40),  /*!< Pin 6 selected */
  GPIO_PIN_7    = ((uint8_t)0x80),  /*!< Pin 7 selected */
  GPIO_PIN_LNIB = ((uint8_t)0x0F),  /*!< Low nibble pins selected */
  GPIO_PIN_HNIB = ((uint8_t)0xF0),  /*!< High nibble pins selected */
  GPIO_PIN_ALL  = ((uint8_t)0xFF)   /*!< All pins selected */
}GPIO_Pin_TypeDef;

typedef enum GPIO_struct
{
  PORT_0,
  PORT_1
} GPIO_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GPIO_Init(GPIO_TypeDef port, GPIO_Pin_TypeDef pin, GPIO_Mode_TypeDef mode);
void GPIO_Write(GPIO_TypeDef port, uint8_t value);
void GPIO_WriteHigh(GPIO_TypeDef port, GPIO_Pin_TypeDef pin);
void GPIO_WriteLow(GPIO_TypeDef port, GPIO_Pin_TypeDef pin);
uint8_t GPIO_ReadOutputData(GPIO_TypeDef port);
void GPIO_WriteReverse(GPIO_TypeDef port, GPIO_Pin_TypeDef pin);

#endif /* __N76E003_GPIO_H */


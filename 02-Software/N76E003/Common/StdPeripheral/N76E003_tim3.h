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
#ifndef __N76S003_TIM3_H
#define __N76S003_TIM3_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  TIM3_PRESCALE_1 = 0,
  TIM3_PRESCALE_2 = 1,
  TIM3_PRESCALE_4 = 2,
  TIM3_PRESCALE_8 = 3,
  TIM3_PRESCALE_16 = 4,
  TIM3_PRESCALE_32 = 5,
  TIM3_PRESCALE_64 = 6,
  TIM3_PRESCALE_128 = 7
} TIM3_Prescaler_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TIM3_Cmd(FunctionalState state);
void TIM3_ITConfig(FunctionalState state);
void TIM3_TimeBaseInit(TIM3_Prescaler_TypeDef prescaler , uint16_t reload);
#endif /* __N76S003_TIM3_H */


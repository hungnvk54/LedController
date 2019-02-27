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
#ifndef __N76E003_PWM_H
#define __N76E003_PWM_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  PWM_PRESCALE_1 = 0,
  PWM_PRESCALE_2 = 1,
  PWM_PRESCALE_4 = 2,
  PWM_PRESCALE_8 = 3,
  PWM_PRESCALE_16 = 4,
  PWM_PRESCALE_32 = 5,
  PWM_PRESCALE_64 = 6,
  PWM_PRESCALE_128 = 7
} PWM_Prescaler_TypeDef;

typedef enum {
  PWM_PIO0 = 1,
  PWM_PIO1 = 2,
  PWM_PIO2 = 4,
  PWM_PIO3 = 8,
  PWM_PIO4 = 16,
  PWM_PIO5 = 32
} PWM_Channel_TypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void PWM_Init( PWM_Prescaler_TypeDef prescale, uint16_t comapre, uint16_t duty, PWM_Channel_TypeDef channel);
void PWM_Cmd(FunctionalState state);
void PWM_UpdateDuty(uint16_t duty,PWM_Channel_TypeDef channel);
void PWM_CmdChannel(FunctionalState state, PWM_Channel_TypeDef channel);
#endif /* __N76E003_PWM_H */


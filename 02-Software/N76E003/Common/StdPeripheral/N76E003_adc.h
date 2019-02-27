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
#ifndef __N76E003_ADC_H
#define __N76E003_ADC_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  ADC_AIN0 = 0,
  ADC_AIN1 = 1,
  ADC_AIN2 = 2,
  ADC_AIN3 = 3,
  ADC_AIN4 = 4,
  ADC_AIN5 = 5,
  ADC_AIN6 = 6,
  ADC_AIN7 = 7,
  ADC_BandGap = 8
} ADC_Channel_TypeDef;

typedef enum {
  ADC_ADCS = 0x04,
  ADC_PWM0 = 0x00,
  ADC_PWM2 = 0x01,
  ADC_PWM4=  0x02,
  ADC_STADC_PIN = 0x03
} ADC_Trigger_Source_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ADC_Init(ADC_Trigger_Source_TypeDef triggerSrc,ADC_Channel_TypeDef channel);
void ADC_SwitchChannel(ADC_Channel_TypeDef channel);
void ADC_Cmd(FunctionalState state);
void ADC_StartConversation(void);
uint16_t ADC_GetResult(void);
#endif /* __N76E003_ADC_H */


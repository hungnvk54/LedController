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
#include "N76E003_tim3.h"
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
void TIM3_Cmd(FunctionalState state)
{
  if( ENABLE == state ) {
    set_TR3;
  } else {
    clr_TR3;
  }
}

void TIM3_ITConfig(FunctionalState state)
{
  if( ENABLE == state )
  {
    set_ET3;
  } else {
    clr_ET3;
  }
}

void TIM3_TimeBaseInit(TIM3_Prescaler_TypeDef prescaler , uint16_t reload)
{
  //Set Prescale
  T3CON = ((T3CON & 0xF8) | ((uint8_t)prescaler&0x07));
  
  //Set Reload Time
  RH3 = ((65536 - reload)>>8)&0xFF;
  RL3 = (65536 - reload)&0xFF;
}
/**
  * @}
  */



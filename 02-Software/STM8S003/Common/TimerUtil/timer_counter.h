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
#ifndef __TIMER_COUNTER_H
#define __TIMER_COUNTER_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Timer_Counter_Init();
uint32_t Timer_Counter_GetCounter();
void Timer_Counter_SetCounter( uint32_t cnt);
void Timer_Counter_ResetCounter( );
void Timer_Counter_IncreaseCounter(void);
#endif /* __TIMER_COUNTER_H */


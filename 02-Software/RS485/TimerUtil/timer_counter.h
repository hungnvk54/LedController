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
#include "stm8s.h"

/* Exported types ------------------------------------------------------------*/
typedef void Timer_Counter_Task(void *args);
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define TICK_PERIOD_IN_MS               1000
#define TICK_PER_SECOND                 (1000000/TICK_PERIOD_IN_MS)
/* Exported functions ------------------------------------------------------- */
void Timer_Counter_Init();
uint32_t Timer_Counter_GetCounter();
void Timer_Counter_SetCounter( uint32_t cnt);
void Timer_Counter_ResetCounter( );
void Timer_Counter_IncreaseCounter(void);
void Timer_Counter_PerformTask(void);
void Timer_Counter_AddTask(Timer_Counter_Task *task);
#endif /* __TIMER_COUNTER_H */


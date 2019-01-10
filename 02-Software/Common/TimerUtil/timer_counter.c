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
#include "timer_counter.h"
#include "stm8s_tim1.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_TASK                10
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// External Task
Timer_Counter_Task *tasks[MAX_TASK];
uint8_t task_Index = 0;
static uint32_t timer_counter;
/* Private function prototypes -----------------------------------------------*/
void Timer_Connter_Init_Timer();
/* Private functions ---------------------------------------------------------*/
void Timer_Connter_Init_Timer()
{
 /* Timer 1 config
   * Fclk = 16MHz
   * Period = 1000
   * Prescale = 16 ==> Interrupt Period 1ms
 */
  TIM1_TimeBaseInit(16, TIM1_COUNTERMODE_UP, 1000, 0);
  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
  TIM1_Cmd(ENABLE);
  
  enableInterrupts();
}
/* Public functions ----------------------------------------------------------*/

void Timer_Counter_Init()
{
  //Init Timer 1 to Counter the counter variable
  timer_counter = 0;
  Timer_Connter_Init_Timer();
}
uint32_t Timer_Counter_GetCounter()
{
  return timer_counter;
}
void Timer_Counter_SetCounter( uint32_t cnt)
{
  timer_counter = cnt;
}
void Timer_Counter_ResetCounter( )
{
  timer_counter = 0;
}
void Timer_Counter_IncreaseCounter()
{
  timer_counter++;
}

void Timer_Counter_AddTask(Timer_Counter_Task *task)
{
  tasks[task_Index++] = task;
}

void Timer_Counter_PerformTask(void)
{
  uint8_t index;
  for( index = 0; index < task_Index; ++index )
  {
    tasks[index](0);
  }
}
/**
  * @}
  */



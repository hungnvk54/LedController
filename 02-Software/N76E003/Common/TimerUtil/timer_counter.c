/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  * ****************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "timer_counter.h"
//#include "stm8s_tim1.h"
#include "N76E003_tim3.h"
#include "system_def.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static volatile uint32_t timer_counter ;
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
  TIM3_TimeBaseInit(TIMER_COUNTER_PRESCALER,TIMER_COUNTER_CMP);
  TIM3_ITConfig( ENABLE);
  TIM3_Cmd(ENABLE);  
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

/**
  * @}
  */



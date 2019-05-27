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
#ifndef __TIMER_PWM_H
#define __TIMER_PWM_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"
#include "gpio_util.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Timer_PWM_Init();
void Timer_PWM_SetChangePeriod(uint16_t period_in_ms);
void Timer_PWM_Start(GPIO_State_TypeDef state);
void Timer_PWM_Update_Period(void *args);
void Timer_PWM_Set_Active_Period(double active_period);
double Timer_PWM_Get_Active_Period(void);
double Timer_PWM_Get_Max_Active_Period(void);
void Timer_PWM_Set_Max_Active_Period(double period);
//For the IR Pulse generator
void Timer_PWM_IR_Transmitter_Init();
#endif /* __TIMER_PWM_H */


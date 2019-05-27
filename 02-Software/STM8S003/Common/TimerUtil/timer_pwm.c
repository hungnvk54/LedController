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
#include "timer_pwm.h"
#include "stm8s_tim2.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
#define TIMER_PWM_RESOLUTION_US                 1                  
#define TIMER_PWM_PERIOD_US                     100
#define TIMER_PWM_TICK                          (TIMER_PWM_PERIOD_US/TIMER_PWM_RESOLUTION_US)
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
double max_active_period = 1; // will be read from static rom
double active_period = 1;//[Value from 0 - 1]
double change_factor = 0;
GPIO_State_TypeDef gpio_state = GPIO_STATE_OFF;
FunctionalState is_configured = DISABLE;
/* Private function prototypes -----------------------------------------------*/
void update_duty_cycle();
/* Private functions ---------------------------------------------------------*/
void update_duty_cycle()
{
  TIM2_SetCompare1((uint16_t)(active_period*TIMER_PWM_TICK));
}
/* Public functions ----------------------------------------------------------*/
void Timer_PWM_Init()
{
  // Fclk = 16MHz
  // Clock scale = 16
  // Counter Period = 100  ==> PWM Period = 100 us
  if( ENABLE == is_configured ) {
    TIM2_Cmd(DISABLE);
  }
  TIM2_OC1Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,50,TIM2_OCPOLARITY_HIGH);
  TIM2_OC1PreloadConfig(ENABLE);
  
  if( DISABLE == is_configured ){
    TIM2_TimeBaseInit(TIM2_PRESCALER_16, TIMER_PWM_TICK);
    TIM2_ARRPreloadConfig(ENABLE);
        is_configured = ENABLE;
  }
  TIM2_Cmd(ENABLE);
//  if( change_factor == 0 ) change_factor = 0.001;
  Timer_PWM_SetChangePeriod(DIMMING_PERIOD_IN_MS_SECOND);
  
}
void Timer_PWM_IR_Transmitter_Init()
{
  //5KHz Pulse
  if( ENABLE == is_configured ) {
    TIM2_Cmd(DISABLE);
  }
  TIM2_OC3Init(TIM2_OCMODE_PWM1,TIM2_OUTPUTSTATE_ENABLE,TIMER_PWM_TICK/2,TIM2_OCPOLARITY_HIGH);
  TIM2_OC3PreloadConfig(ENABLE);
  
  if( DISABLE == is_configured ){
    TIM2_TimeBaseInit(TIM2_PRESCALER_16, TIMER_PWM_TICK);
    TIM2_ARRPreloadConfig(ENABLE);
    is_configured = ENABLE;
  }
  TIM2_Cmd(ENABLE);
}

void Timer_PWM_Start(GPIO_State_TypeDef state)
{
  gpio_state = state;
}
void Timer_PWM_Update_Period(void *args)
{
  (void)args;
  if( GPIO_STATE_ON == gpio_state )
  {
    if( active_period >= 1 ) 
    {
//      gpio_state = GPIO_STATE_OFF;
      return;
    }
    active_period += 0.8*change_factor;
    if( active_period > max_active_period) {
            active_period = max_active_period;
    }
    update_duty_cycle();
  } else if (GPIO_STATE_OFF == gpio_state)
  {
    if( active_period <= 0 ) 
    {
//      gpio_state = GPIO_STATE_OFN;
      return;
    }
    active_period -= 2*change_factor;
    if( active_period < 0) {
            active_period = 0;
    }
    update_duty_cycle();
  } 
}

void Timer_PWM_SetChangePeriod(uint16_t period_in_ms)
{
  change_factor = 1.0f/period_in_ms;
}

void Timer_PWM_Set_Active_Period(double act_prd)
{
  active_period = act_prd;
  max_active_period = act_prd;
  update_duty_cycle();
}

double Timer_PWM_Get_Active_Period(void)
{
  return active_period;
}
double Timer_PWM_Get_Max_Active_Period(void)
{
  return max_active_period;
}
void Timer_PWM_Set_Max_Active_Period(double period)
{
  max_active_period = period;
}
/**
  * @}
  */



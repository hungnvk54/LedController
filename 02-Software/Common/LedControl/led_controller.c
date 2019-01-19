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
#include "led_controller.h"
#include "timer_pwm.h"
#include "system_def.h"
#include "nodestatemanager.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static Control_Mode_TypeDef running_mode;
/* Private function prototypes -----------------------------------------------*/
void update_led_indicator(void);
/* Private functions ---------------------------------------------------------*/
void Led_Control_Immediate(GPIO_State_TypeDef state);
/* Public functions ----------------------------------------------------------*/
   
/**
  * @brief   Control the output base on the passed mode
  * @par Full description:
  *  the Controller will turn on/off led base on passed mode
  * @param   
  * port: Port of the Led
  * pin: Pin Of the Led
  * mode: Control mode: Immediate or dimming
  * On/Off
  * @retval None
  */
void Led_Control_Cmd( GPIO_TypeDef *port, GPIO_Pin_TypeDef pin,\
                      GPIO_State_TypeDef state
                    )
{
  if( CONTROL_MODE_IMMEDIATE == running_mode )
  {
    Led_Control_Immediate(state);
  } else if( CONTROL_MODE_DIMMING == running_mode )
  {
    Timer_PWM_Start(state);
  }
}

void Led_Control_Immediate(GPIO_State_TypeDef state)
{
  if( GPIO_STATE_ON == state)
  {
    GPIO_Util_TurnOnLed(LED_CONTROL_PORT,LED_CONTROL_PIN);//Active in low level
  } else 
  {
    GPIO_Util_TurnOffLed(LED_CONTROL_PORT,LED_CONTROL_PIN);
  }
}

void Led_Control_Init(Control_Mode_TypeDef mode)
{
  if( CONTROL_MODE_IMMEDIATE == mode )
  {
    GPIO_Util_Init_As_Out(LED_PORT,LED_PIN);
  } else {
    Timer_PWM_Init();
  }
  running_mode = mode;
}

Control_Mode_TypeDef Led_Control_GetMode(void)
{
  return running_mode;
}

void Led_Control_Task(void *args)
{
  (void)args;
  GPIO_State_TypeDef output_state = Node_State_GetOutputState();
  Led_Control_Cmd(LED_CONTROL_PORT,LED_CONTROL_PIN,output_state);
  
  //Update Led Indicator
//  update_led_indicator();
}

void update_led_indicator(void)
{
  GPIO_State_TypeDef output_state = Node_State_GetOutputState();
  
  if( GPIO_STATE_OFF == output_state) {
    GPIO_Util_TurnOnLed(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
  } else {
    GPIO_Util_TurnOffLed(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
  }
}

/**
  * @}
  */



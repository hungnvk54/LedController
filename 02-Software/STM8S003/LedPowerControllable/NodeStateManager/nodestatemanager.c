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
#include "nodestatemanager.h"
#include "ir_receiver.h"
#include "system_def.h"
#include "timer_pwm.h"
#include "write_flash.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Node_State_TypeDef node_state;

Node_State_Output_Mode_TypeDef output_mode = OUTPUT_TOGGLE_WHEN_INPUT_ON;
double dimming_on_change_factor = 0.01;
double dimming_off_change_factor = 0.01;
uint16_t update_flash_timeout = 0;
/* Private function prototypes -----------------------------------------------*/
void update_output(uint8_t input_state);
/* Private functions ---------------------------------------------------------*/
void update_output(uint8_t input_state)
{
  if( OUTPUT_TOGGLE_WHEN_INPUT_ON == output_mode )
  {
    if( (input_state ==OFF )&& (node_state.input_state == ON)) {
      if( node_state.output_state == GPIO_STATE_OFF ) {
        node_state.output_state = GPIO_STATE_ON;
      } else {
        node_state.output_state = GPIO_STATE_OFF;
      }
    } else if( input_state == DIM ) {
      if( node_state.input_state == ON )
      {
//        if( node_state.output_state == GPIO_STATE_ON){
//          node_state.dimming_active_period = 1;
//          node_state.output_state = GPIO_STATE_DIM_DOWN;
//        } else if(node_state.output_state == GPIO_STATE_OFF) {
//          node_state.dimming_active_period = 0;
//          node_state.output_state = GPIO_STATE_DIM_UP;
//        }
        node_state.output_state = GPIO_STATE_DIM_UP;
        node_state.dimming_active_period = Timer_PWM_Get_Active_Period();
      }
      //Change the dim level here
      if( node_state.output_state == GPIO_STATE_DIM_UP) {
        if((node_state.dimming_active_period + dimming_on_change_factor) < 1){
          node_state.dimming_active_period += dimming_on_change_factor;
        } else {
          node_state.output_state = GPIO_STATE_DIM_DOWN;
        }
      } else if(node_state.output_state == GPIO_STATE_DIM_DOWN) {
        if(( node_state.dimming_active_period - dimming_off_change_factor) > 0.07) {
          node_state.dimming_active_period -= dimming_off_change_factor;
        } else {
          node_state.output_state = GPIO_STATE_DIM_UP;
        }
      }
    }
  } else if(output_mode == OUTPUT_AS_INPUT) {
    if( input_state == ON) {
      node_state.output_state = GPIO_STATE_ON;
    } else {
      node_state.output_state = GPIO_STATE_OFF;
    }
  }
}
/* Public functions ----------------------------------------------------------*/
void Node_State_Manager_Init(Node_State_Output_Mode_TypeDef outputMode)
{
  node_state.input_state = OFF;
  node_state.output_state = GPIO_STATE_OFF;
  node_state.dimming_active_period = 0;
  dimming_on_change_factor = 1.0f/DIMMING_ON_CHANGE_PERIOD_IN_MS_SECOND;
  dimming_off_change_factor = 1.0f/DIMMING_OFF_CHANGE_PERIOD_IN_MS_SECOND;
  output_mode = outputMode;
  
  Flash_Init();
  
  //Read the active value from the Flash
  double active_value = Flash_Read_ActivePeriod();
  if( active_value <= 1)
    Timer_PWM_Set_Max_Active_Period(active_value);
    Flash_Write_ActivePeriod(active_value);
}

void Node_State_Manager_Task(void *args)
{
  //Get input ADC and generate the input state
  IR_Signal_State_TypeDef ir_state = IR_Receiver_GetState();
  uint8_t input_state = OFF;
#if (STATE_MANAGER_PARALLEL_LEDS == YES)
  if( IR_HIDDEN == ir_state ) {
    input_state = OFF;
  } else if (IR_SHORT_PULSE == ir_state ){
    input_state = ON;
  } else if (IR_LONG_PULSE == ir_state){
    input_state = DIM;
  }
#else
  if( IR_HIDDEN == ir_state ) {
     input_state = (ON);
  } else {
     input_state = (OFF);
  }
#endif
  
  //Update output
  update_output(input_state);
  Node_State_SetInputState(input_state);
  
  update_flash_timeout += 1;
  if( update_flash_timeout > 30000) {
    //Only update the flash after 30s
    double max_active_period = Timer_PWM_Get_Max_Active_Period();
    Flash_Write_ActivePeriod(max_active_period);
    update_flash_timeout = 0;
  }
}

uint8_t Node_State_GetInputState(void)
{
  return node_state.input_state;
}
GPIO_State_TypeDef Node_State_GetOutputState(void)
{
  return node_state.output_state;
}
void Node_State_SetOutputState(GPIO_State_TypeDef state)
{
  node_state.output_state = state;
}
void Node_State_SetInputState(uint8_t state)
{
  node_state.input_state = state;
}

void Node_State_SetOutputMode(Node_State_Output_Mode_TypeDef mode)
{
  output_mode = mode;
}

double Node_State_GetActivePeriod()
{
  return node_state.dimming_active_period;
}

/**
  * @}
  */



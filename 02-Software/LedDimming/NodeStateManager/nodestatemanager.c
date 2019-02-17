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
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Node_State_TypeDef node_state;

Node_State_Output_Mode_TypeDef output_mode = OUTPUT_TOGGLE_WHEN_INPUT_ON;
/* Private function prototypes -----------------------------------------------*/
void update_output(uint8_t input_state);
/* Private functions ---------------------------------------------------------*/
void update_output(uint8_t input_state)
{
  if( OUTPUT_TOGGLE_WHEN_INPUT_ON == output_mode )
  {
    if( (input_state ==OFF )&& (node_state.input_state == ON)) {
      if( node_state.output_state == GPIO_STATE_ON ) {
        node_state.output_state = GPIO_STATE_OFF;
      } else {
        node_state.output_state = GPIO_STATE_ON;
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
  output_mode = outputMode;
}

void Node_State_Manager_Task(void *args)
{
  //Get input ADC and generate the input state
  IR_Signal_State_TypeDef ir_state = IR_Receiver_GetState();
  uint8_t input_state = OFF;
#if (STATE_MANAGER_PARALLEL_LEDS == YES)
  if( IR_HIDDEN == ir_state ) {
    input_state = OFF;
  } else {
    input_state = ON;
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

/**
  * @}
  */



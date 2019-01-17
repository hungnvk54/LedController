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
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void Node_State_Manager_Init(void)
{
  node_state.input_state = OFF;
  node_state.output_state = GPIO_STATE_OFF;
}

void Node_State_Manager_Task(void *args)
{
  //Get input ADC and generate the input state
  IR_Signal_State_TypeDef ir_state = IR_Receiver_GetState();
#if (STATE_MANAGER_PARALLEL_LEDS == YES)
  if( IR_HIDDEN == ir_state ) {
    Node_State_SetInputState(OFF);
  } else {
    Node_State_SetInputState(ON);
  }
#else
  if( IR_HIDDEN == ir_state ) {
    Node_State_Manager_SetInputState(ON);
  } else {
    Node_State_Manager_SetInputState(OFF);
  }
#endif
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

/**
  * @}
  */



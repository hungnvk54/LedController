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
  node_state.output_state = OFF;
}

void Node_State_Manager_Task(void *args)
{
  //Get input ADC and generate the input state
}

uint8_t Node_State_GetInputState(void)
{
  return node_state.input_state;
}
uint8_t Node_State_GetOutputState(void)
{
  return node_state.output_state;
}
void Node_State_SetOutputState(uint8_t state)
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



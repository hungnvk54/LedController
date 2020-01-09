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
#include "nodeinterconn.h"
#include "inc.h"
#include "nodestatemanager.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_State_TypeDef pre_digital_input_state = GPIO_STATE_OFF;
/* Private function prototypes -----------------------------------------------*/
GPIO_State_TypeDef get_input_state(void);
void process_digital_input();
void process_ditital_output();
/* Private functions ---------------------------------------------------------*/
GPIO_State_TypeDef get_input_state(void)
{
  uint8_t input = GPIO_Util_ReadInputData(DIGITAL_INPUT_PORT);
  
  if( input & DIGITAL_INPUT_PIN) {
    return GPIO_STATE_ON;
  } else {
    return GPIO_STATE_OFF;
  }
}
void process_digital_input()
{
  // If any change from  Low to High - Toggle the output of the master node
  GPIO_State_TypeDef current_input_state = get_input_state();
  if(current_input_state != pre_digital_input_state)
  {
    pre_digital_input_state = current_input_state;
    if( GPIO_STATE_ON == current_input_state )
    {
      //Toggle the output
      //Node_State_ToggleOutputState();
      Node_State_SetOutputState(GPIO_STATE_ON);
    } else{
      Node_State_SetOutputState(GPIO_STATE_OFF);
    }
  }
}

void process_ditital_output()
{
  GPIO_State_TypeDef output_state = Node_State_GetOutputState();
  if( GPIO_STATE_ON == output_state){
    GPIO_Util_WriteHigh(DIGITAL_OUTPUT_PORT,DIGITAL_OUTPUT_PIN);
  } else {
    GPIO_Util_WriteLow(DIGITAL_OUTPUT_PORT,DIGITAL_OUTPUT_PIN);
  }
}
/* Public functions ----------------------------------------------------------*/
void Node_Inter_Conn_Task(void *args)
{
    (void)args;
    
    //1.Get the Input
    process_digital_input();
    //2.Get the output. Set the output pin as the power control pin
    process_ditital_output();
}

void Node_Inter_Conn_Init(void)
{
  //Set the input,output in
  GPIO_Util_Init(DIGITAL_INPUT_PORT,DIGITAL_INPUT_PIN,GPIO_MODE_IN_FL_NO_IT);
  
  //Set the output
  GPIO_Util_Init(DIGITAL_OUTPUT_PORT,DIGITAL_OUTPUT_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
}
/**
  * @}
  */


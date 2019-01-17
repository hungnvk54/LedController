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
#include "nodecontrol.h"
#include "commands.h"
#include "system_def.h"
#include "nodestatemanager.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void compose_command(uint8_t addr, Command_Code_TypeDef code, uint8_t state)
{
  Command_TypeDef cmd;
  cmd.address = addr;
  cmd.code = code;
  cmd.data = state;
  Command_SendCommand(cmd);
}

void process_command(Command_TypeDef cmd)
{
  if( cmd.address == NODE_ADDRESS)//Chi xu ly ma lenh co dia chi
  {
    switch( cmd.code)
    {
      case COMMAND_NODE_QUERRY:
      {
        //Received respond from slave node.
        uint8_t input_state = Node_State_GetInputState();
        compose_command(NODE_ADDRESS,COMMAND_NODE_RESPOND,input_state);
        break;
      }
    case COMMAND_NODE_QUERY_STATE:
      {
          //Received the previous request
        uint8_t input_state = Node_State_GetInputState();
        compose_command(NODE_ADDRESS,COMMAND_NODE_REPORT_STATE,input_state);
        break;
      }
    case COMMAND_NODE_REQUEST_CHANGE_STATE:
      {
        Node_State_SetOutputState((GPIO_State_TypeDef)cmd.data);
        break;
      }
    }
  }
}

/* Public functions ----------------------------------------------------------*/
void Node_Control_InitNodes(void){
}

void Node_Control_Task(void *args)
{
  Command_TypeDef cmd;
  while( Command_PopCommand(&cmd) == SUCCESS) {
    process_command(cmd);
  }
}

/**
  * @}
  */



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
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_NODES		        25
#define ARROUND_NODE_SIZE               1

#define TIME_OUT_IN_MS                  10
#define TIMER_IS_TIMEOUT(x)             (x==0)
#define TIMER_RESET(x)                  (x=TIME_OUT_IN_MS)
#define TIMER_IS_RUNNING(x)             (x > 0)
#define TIMER_UPDATE_TIME(x)            (x--)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
Node_TypeDef nodes[MAX_NODES];
uint8_t detected_node_index=0;// For detecting node
uint8_t state_node_query_index=0; // For control state of the node
Node_Control_State_TypeDef control_state;

uint16_t timeout;
/* Private function prototypes -----------------------------------------------*/
void change_control_state(Node_Control_State_TypeDef state); //Thay doi trang thai cua cac node
void query_node_state(); //Lay thong tin trang thai dau vao cua node
void process_command(Command_TypeDef cmd);//Xu ly menh lenh nhan duoc
void compose_command(uint8_t addr, Command_Code_TypeDef code, uint8_t state);//Tao menh lenh va gui cho cac node
void process_node_input_state(void);//Thay doi trang thai dau ra dua vao trang thai dau vao
/* Private functions ---------------------------------------------------------*/
void change_control_state(Node_Control_State_TypeDef state)
{
  control_state = state;
}

void query_node_state()
{
  //Change address to other node
  while( (state_node_query_index < MAX_NODES)&& \
    (nodes[state_node_query_index].is_avaiable == NO)) {
      state_node_query_index++;
    }
  
  if( state_node_query_index >= MAX_NODES ) {
    state_node_query_index = 0;
    //Send Command to change the output node state
    process_node_input_state();
  } else {
    compose_command(state_node_query_index,COMMAND_NODE_QUERY_STATE,COMMAND_DATA_UNUSED);
    TIMER_RESET(timeout);
  }
  change_control_state(NODE_CONTROL_STATE_WAIT_NODE_REPORT);
}

void process_node_input_state(void)
{
  uint8_t idx;
  for(idx = 0; idx < MAX_NODES;++idx)
  {
    if( nodes[idx].input_state == OFF){
      nodes[idx].output_state = OFF;
    } else {
      nodes[idx].output_state = ON;
    }
  }
  
  for(idx = 0; idx < MAX_NODES;++idx)
  {
    if( nodes[idx].input_state == ON){
      //Change previous node state
      int16_t arround_node_idx = idx - 1;
      uint8_t node_counter = ARROUND_NODE_SIZE;
      while( (arround_node_idx >=0 )&& ( node_counter > 0) )
      {
        nodes[arround_node_idx].output_state = ON;
        node_counter --;
        arround_node_idx--;
      }
      
      arround_node_idx = idx + 1;
      node_counter = ARROUND_NODE_SIZE;
      while( (arround_node_idx < MAX_NODES)&&(node_counter > 0)) {
        nodes[arround_node_idx].output_state = ON;
        node_counter --;
        arround_node_idx++;
      }
    }
  }
  
  for(idx = 0; idx < MAX_NODES;++idx)
  {
    compose_command(idx,COMMAND_NODE_REQUEST_CHANGE_STATE,nodes[idx].output_state);
  }
}

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
  switch( cmd.code)
  {
    case COMMAND_NODE_RESPOND:
    {
      //Received respond from slave node.
      nodes[cmd.address].is_avaiable = YES;
      nodes[cmd.address].output_state = ((cmd.data&UB_UINT8)==UB_UINT8);
      nodes[cmd.address].input_state = ((cmd.data&LB_UINT8)==LB_UINT8);
      if( detected_node_index < MAX_NODES ) {
        change_control_state(NODE_CONTROL_STATE_DETECTING);
      } else{
        //Decting node finish
        change_control_state(NODE_CONTROL_STATE_STATE_QUERY);/* Can nhac xem nen chuyen
                                                        sang state nao */
      }
      break;
    }
  case COMMAND_NODE_REPORT_STATE:
    {
      //Received the previous request
      nodes[cmd.address].output_state = ((cmd.data&UB_UINT8)==UB_UINT8);
      nodes[cmd.address].input_state = ((cmd.data&LB_UINT8)==LB_UINT8);
      //start new request
      change_control_state(NODE_CONTROL_STATE_STATE_QUERY);
    }
  }
}

/* Public functions ----------------------------------------------------------*/
void Node_Control_DetectNodes(void){
  //Change address to other node
  if( detected_node_index < MAX_NODES )
  {
    //Build command
    compose_command(detected_node_index,COMMAND_NODE_QUERRY,COMMAND_DATA_UNUSED);
    TIMER_RESET(timeout);
    change_control_state(NODE_CONTROL_STATE_WAIT_NODE_QUERY);
  } else {
    //Reach the end of node - start query the node state.
    change_control_state(NODE_CONTROL_STATE_STATE_QUERY);
  }
  detected_node_index++;
}

void Node_Control_InitNodes(void){
  uint8_t node_index;
  
  for( node_index = 0 ; node_index < MAX_NODES; ++node_index){
    nodes[node_index].is_avaiable = NO;
    nodes[node_index].address = node_index;
    nodes[node_index].output_state = OFF;
    nodes[node_index].input_state = OFF;
  }
  control_state = NODE_CONTROL_STATE_DETECTING;
  timeout = 0;
}

void Node_Control_Task(void *args)
{
  switch(control_state)
  {
    case NODE_CONTROL_STATE_IDLE:
    {
      break;
    }
    case NODE_CONTROL_STATE_DETECTING:
    {
      Node_Control_DetectNodes();
      break;
    }
    case NODE_CONTROL_STATE_STATE_QUERY:
    {
      query_node_state();
      break;
    }
    case NODE_CONTROL_STATE_WAIT_NODE_QUERY:
    case NODE_CONTROL_STATE_WAIT_NODE_REPORT:
    case NODE_CONTROL_STATE_WAIT_COMMAND:
    {
      Command_TypeDef cmd;
      while( Command_PopCommand(&cmd) == SUCCESS) {
        process_command(cmd);
      }
      break;
    }
    default:
    {
      
    }
  }
  if( TIMER_IS_TIMEOUT(timeout) == TRUE )
  {
    if(NODE_CONTROL_STATE_WAIT_NODE_QUERY == control_state)
    {
      change_control_state(NODE_CONTROL_STATE_DETECTING);
    } else if( NODE_CONTROL_STATE_WAIT_NODE_REPORT == control_state)
    {
      change_control_state(NODE_CONTROL_STATE_STATE_QUERY);
    }
  } else {
    TIMER_UPDATE_TIME(timeout);
  }
}

/**
  * @}
  */



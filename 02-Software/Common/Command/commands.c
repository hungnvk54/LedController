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
#include "commands.h"
#include "const.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_COMMAND_BUFFER_SIZE         5

Command_TypeDef commands[MAX_COMMAND_BUFFER_SIZE];
uint8_t cmd_wr_idx=0, cmd_rd_idx = 0, cmd_cnt=0;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint8_t cmd_push(Command_TypeDef cmd);
/* Private functions ---------------------------------------------------------*/
uint8_t cmd_push(Command_TypeDef cmd)
{
  if( cmd_cnt >= MAX_COMMAND_BUFFER_SIZE) return FAILED;/// !!!! Be carefully - Buffer Full

  commands[cmd_wr_idx] = cmd;
  cmd_wr_idx++;
  cmd_cnt++;
  if( cmd_wr_idx >= MAX_COMMAND_BUFFER_SIZE ) cmd_wr_idx = 0 ;
  return SUCCESS;
}
uint8_t Command_PopCommand(Command_TypeDef *cmd)
{
  if( cmd_cnt == 0 ) return FAILED;
  *cmd = commands[cmd_rd_idx];
  cmd_rd_idx++;
  cmd_cnt--;
  if( cmd_rd_idx >= MAX_COMMAND_BUFFER_SIZE ) cmd_rd_idx =0;
  return SUCCESS;
}
/* Public functions ----------------------------------------------------------*/

void Command_SendCommand(Command_TypeDef cmd)
{
  ///Prepare the command
  uint8_t buffer[COMMAND_SIZE];
  ///Build the command
  {
    buffer[COMMAND_HEADER_INDEX] = COMMAND_HEADER;
    buffer[COMMAND_ADDRESS_INDEX] = cmd.address;
    buffer[COMMAND_COMMAND_INDEX] = cmd.code;
    buffer[COMMAND_DATA_INDEX]= cmd.data;
  }
  Transport_Write(buffer, COMMAND_SIZE);
}

void Command_Task(void *args)
{
  /** Query data from transporter, then decode data to find the command
   * Command will be pushed into the internal buffer 
   */
    uint8_t data;
    Command_TypeDef cmd;
    while( (Transport_GetRxBufferSize() >= COMMAND_SIZE) && (Transport_RxPop(&data) == SUCCESS )){
      // Terminate the loop when size is less than to Commandsize
      if( data == (uint8_t)COMMAND_HEADER ) {
        cmd.header = data;
        Transport_RxPop(&data);
        cmd.address = data;
        Transport_RxPop(&data);
        cmd.code = (Command_Code_TypeDef)data;
        Transport_RxPop(&data);
        cmd.data = data;
        
        cmd_push(cmd);
      }
    }
}

/**
  * @}
  */



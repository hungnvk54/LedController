/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   This file contains the commands that send between the devices in
  *          the local network. The command is defined as below
  *          |--Header--|--Address--|--Command--|---Data---|
  *          |--1 byte--|--1 byte---|--1 byte---|--1 byte--|
  *          |----FA----|--0===>64--|-----V-----|-----V----|
  *          Address: 0-Master Node, 64 - Broadcast
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMANDS_H
#define __COMMANDS_H

/* Includes ------------------------------------------------------------------*/
#include "transport.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  COMMAND_NODE_QUERRY, /*Query Node in the Network. If node exist in the Network
                          Reply the network with the command Respond */
  COMMAND_NODE_RESPOND, /* Reply the Master when received this */
  
  COMMAND_NODE_REQUEST_CHANGE_STATE, /* Change state of the output base on 
                              Data in command */
  COMMAND_NODE_QUERY_STATE, /* Query current state of the Nodes */
  COMMAND_NODE_REPORT_STATE /* Report state of current Nodes */
  
} Command_Code_TypeDef;

typedef enum {
  COMMAND_DATA_STATE_ON, /* State of the Node is On */
  COMMAND_DATA_STATE_OFF, /* State of the Node is Off */
  
  COMMAND_DATA_UNUSED = 0xff
} Command_Data_TypeDef;

typedef uint8_t Node_Address_TypeDef;

typedef struct  {
  uint8_t header;
  Node_Address_TypeDef address;
  Command_Code_TypeDef code;
  Command_Data_TypeDef data;
} Command_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define COMMAND_HEADER                  0xFA

#define COMMAND_HEADER_INDEX            0
#define COMMAND_ADDRESS_INDEX           1
#define COMMAND_COMMAND_INDEX           2
#define COMMAND_DATA_INDEX              3

#define COMMAND_SIZE                    4
/* Exported functions ------------------------------------------------------- */

void Command_SendCommand(Command_TypeDef cmd);
void Command_Task(void *args);
uint8_t Command_PopCommand(Command_TypeDef *cmd);

#endif /* __COMMANDS_H */


/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NODE_CONTROL_H
#define __NODE_CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* Exported types ------------------------------------------------------------*/
typedef struct {
  uint8_t is_avaiable;
  uint8_t address;
  uint8_t output_state;
  uint8_t input_state;
} Node_TypeDef;

typedef enum {
  NODE_CONTROL_STATE_IDLE,
  NODE_CONTROL_STATE_DETECTING,
  NODE_CONTROL_STATE_STATE_QUERY,
  NODE_CONTROL_STATE_REQUEST_CHANGE_STATE,
  NODE_CONTROL_STATE_WAIT_NODE_QUERY,
  NODE_CONTROL_STATE_WAIT_NODE_REPORT,
  NODE_CONTROL_STATE_WAIT_COMMAND
} Node_Control_State_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Node_Control_InitNodes(void);
void Node_Control_DetectNodes(void);
void Node_Control_Task(void *args);
#endif /* __NODE_CONTROL_H */


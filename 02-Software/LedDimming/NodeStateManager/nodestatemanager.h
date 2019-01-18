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
#ifndef __NODE_STATE_MANAGER_H
#define __NODE_STATE_MANAGER_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"
#include "const.h"
#include "gpio_util.h"

/* Exported types ------------------------------------------------------------*/
typedef struct 
{
  uint8_t input_state;
  GPIO_State_TypeDef output_state;
} Node_State_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Node_State_Manager_Init(void);
void Node_State_Manager_Task(void *args);
uint8_t Node_State_GetInputState(void);
GPIO_State_TypeDef Node_State_GetOutputState(void);
void Node_State_SetOutputState(GPIO_State_TypeDef state);
void Node_State_SetInputState(uint8_t state);
#endif /* __NODE_STATE_MANAGER_H */


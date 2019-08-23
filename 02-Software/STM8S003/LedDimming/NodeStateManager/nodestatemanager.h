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

typedef enum {
  OUTPUT_AS_INPUT,
  OUTPUT_TOGGLE_WHEN_INPUT_ON
} Node_State_Output_Mode_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Node_State_Manager_Init(Node_State_Output_Mode_TypeDef outputMode);
void Node_State_Manager_Task(void *args);
uint8_t Node_State_GetInputState(void);
GPIO_State_TypeDef Node_State_GetOutputState(void);
void Node_State_SetOutputState(GPIO_State_TypeDef state);
void Node_State_SetInputState(uint8_t state);
void Node_State_SetOutputMode(Node_State_Output_Mode_TypeDef mode);
double Node_State_GetActivePeriod(void);
#endif /* __NODE_STATE_MANAGER_H */


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
#ifndef __LED_CONTROLLER_H
#define __LED_CONTROLLER_H

/* Includes ------------------------------------------------------------------*/
#include "gpio_util.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  CONTROL_MODE_DIMMING,
  CONTROL_MODE_IMMEDIATE
} Control_Mode_TypeDef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Led_Control_Init(Control_Mode_TypeDef mode);

void Led_Control_Cmd( GPIO_TypeDef port, GPIO_Pin_TypeDef pin,  \
                      GPIO_State_TypeDef state
                    );
Control_Mode_TypeDef Led_Control_GetMode(void);

void Led_Control_Task(void *args);
#endif /* __LED_CONTROLLER_H */


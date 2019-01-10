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
                    Control_Mode_TypeDef mode, GPIO_State_TypeDef state
                    );
#endif /* __LED_CONTROLLER_H */


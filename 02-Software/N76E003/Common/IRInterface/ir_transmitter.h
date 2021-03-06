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
#ifndef __IR_TRANSMITTER_H
#define __IR_TRANSMITTER_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  IR_OUTPUT_MODE_PWM,
  IR_OUTPUT_MODE_IO
} IR_Output_Mode_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void IR_Transmitter_Init(IR_Output_Mode_TypeDef mode);
void IR_Transmitter_SetPrescaler(uint8_t scale);
void IR_Transmitter_Task(void *args);
IR_Output_Mode_TypeDef IR_Transmitter_GetMode(void);
#endif /* __IR_TRANSMITTER_H */


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
#include "stm8s.h"

/* Exported types ------------------------------------------------------------*/
typedef enum {
  IR_OUTPUT_MODE_PWM,
  IR_OUTPUT_MODE_IO
} IR_Output_Mode_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define IR_TRANSMITTER_PORT             GPIOA
#define IR_TRANSMITTER_PIN              GPIO_PIN_3
/* Exported functions ------------------------------------------------------- */
void IR_Transmitter_Init(IR_Output_Mode_TypeDef mode);
void IR_Transmitter_PerformTask(void *args);
#endif /* __IR_TRANSMITTER_H */


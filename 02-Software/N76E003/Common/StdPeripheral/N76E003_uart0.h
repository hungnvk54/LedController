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
#ifndef __N76E003_UART0_H
#define __N76E003_UART0_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  UART0_RI = 0x01,
  UART0_TI = 0x02
} UART0_IT_Flags_TypeDef;

typedef enum 
{
  UART0_Mode0 = 0,
  UART0_Mode1 = 1,
  UART0_Mode2 = 2,
  UART0_Mode3 = 3
} UART0_Mode_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void UART0_Init(UART0_Mode_TypeDef mode, uint16_t baud);
void UART0_ITConfig(FunctionalState state);
ITStatus UART0_GetITStatus(UART0_IT_Flags_TypeDef flag);
void UART0_SetITStatus(UART0_IT_Flags_TypeDef flag);
void UART0_ClearITStatus(UART0_IT_Flags_TypeDef flag);
void UART0_SendData(uint8_t data);
uint8_t UART0_GetData(void);
#endif /* __N76E003_UART0_H */


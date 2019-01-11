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
#ifndef __TRANSPORT_H
#define __TRANSPORT_H

/* Includes ------------------------------------------------------------------*/
#include "inc.h"
#include "const.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Transport_Init(void);

void Transport_TxPush(uint8_t data);
uint8_t Transport_TxPop(uint8_t *data);

void Transport_RxPush(uint8_t data);
uint8_t Transport_RxPop(uint8_t *data);

void Transport_Write(uint8_t *data, uint16_t length);
uint16_t Transport_Read(uint8_t *data, uint16_t length);

uint8_t Transport_GetRxBufferSize(void);
#endif /* __TRANSPORT_H */


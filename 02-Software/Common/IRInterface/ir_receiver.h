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
#ifndef __IR_RECEIVER_H
#define __IR_RECEIVER_H

/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
typedef enum {
  IR_HIDDEN, //Tin hieu bi che khuat - khong co tin hieu tai mat nhan
  IR_SHORT_HIDDEN, //Tin hieu bi che khuat trong khoang thoi gian ngan
  IR_NOT_HIDDEN //Tin hieu khong bi che khuat.
} IR_Signal_State_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void IR_Receiver_Init(void);
void IR_Receiver_Task(void *args);
IR_Signal_State_TypeDef IR_Receiver_GetState(void);
#endif /* __IR_RECEIVER_H */


/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  * ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "n76e003_gpio.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void GPIO_Init(GPIO_TypeDef port, GPIO_Pin_TypeDef pin, GPIO_Mode_TypeDef mode)
{
  switch( port) {
  case PORT_0:
    if( ((uint8_t)mode & (uint8_t)0x80 ) != (uint8_t)0) 
    {
      ///Output
      if(((uint8_t)mode & (uint8_t)0x40) != (uint8_t)0){
        //Open push-pull
        P0M1 &= ~((uint8_t)pin);
        P0M2|=(uint8_t)pin;
      } else {
        //Drain
        P0M1|=(uint8_t)pin;
        P0M2|=(uint8_t)pin;
      }
    } else {
      ///Input
      P0M1 |= (uint8_t)(pin);
      P0M2 &=~((uint8_t)(pin));
    }
    break;
  case PORT_1:
    if( ((uint8_t)mode & (uint8_t)0x80 ) != (uint8_t)0) {
      ///Output
      if(((uint8_t)mode & (uint8_t)0x40) != (uint8_t)0){
        //push-pull
        P1M1 &= ~((uint8_t)pin);
        P1M2|=(uint8_t)pin;
      } else {
        //Open Drain
        P1M1|=(uint8_t)pin;
        P1M2|=(uint8_t)pin;
      }
    } else {
      ///Input
      P1M1 |= (uint8_t)(pin);
      P1M2 &=~((uint8_t)(pin));
    }
    break;
  }
}
                
void GPIO_Write(GPIO_TypeDef port, uint8_t value)
{
  switch( port) {
  case PORT_0:
    P0 = value;
    break;
  case PORT_1:
    P1 = value;
    break;
  }
}

void GPIO_WriteHigh(GPIO_TypeDef port, GPIO_Pin_TypeDef pin)
{
  switch( port) {
  case PORT_0:
    P0 |= pin ;
    break;
  case PORT_1:
    P1 |= pin;
    break;
  }
}
void GPIO_WriteLow(GPIO_TypeDef port, GPIO_Pin_TypeDef pin)
{
  switch( port) {
  case PORT_0:
    P0 &= ~pin ;
    break;
  case PORT_1:
    P1 &= ~pin;
    break;
  }
}

uint8_t GPIO_ReadOutputData(GPIO_TypeDef port)
{
  uint8_t value = 0;
  switch( port) {
  case PORT_0:
    value = P0 ;
    break;
  case PORT_1:
    value = P1 ;
    break;
  }  
  return value;
}

void GPIO_WriteReverse(GPIO_TypeDef port, GPIO_Pin_TypeDef pin)
{
  switch( port) {
  case PORT_0:
    P0 ^= pin;
    break;
  case PORT_1:
    P1 ^= pin ;
    break;
  }
}
/**
  * @}
  */



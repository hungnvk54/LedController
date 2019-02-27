/**
  ******************************************************************************
  * @file    N76E003_uart0.c
  * @author  
  * @version 
  * @date    
  * @brief   
  * ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "N76E003_uart0.h"
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
void UART0_Init(UART0_Mode_TypeDef mode, uint16_t baud)
{
  //1.Set IO Pin
  P06_Quasi_Mode;
  P07_Quasi_Mode;	
  //2.Set Mode
  SCON |= ((uint8_t)mode)<<6;
  
  //2.Enable Receving
  set_REN;
  
  switch(mode){
  case UART0_Mode0:
    break;
  case UART0_Mode1:
    //2.1 Set double baudrate
    set_SMOD;
    //2.2 Set clock source is Timer 1
    TMOD |= 0x20; //Set Timer as Timer mode (Mode 1)
    set_T1M; //The clock source of Timer 1 is direct the system clock
    clr_BRCK;
    //2.3
    break;
  case UART0_Mode2:
    break;
  case UART0_Mode3:
    break;
  }
  //3.Calucate baudrae
#ifdef FOSC_160000
    TH1 = 256 - (1000000/baud+1);               /*16 MHz */
#endif    	
#ifdef FOSC_166000
    TH1 = 256 - (1037500/baud);         		     /*16.6 MHz */
#endif
  //4.Clear Interrupt
  clr_RI;
  clr_TI;
}

void UART0_ITConfig(FunctionalState state)
{
  if( ENABLE == state ){
    set_ES;
  } else {
    clr_ES;
  }
}
ITStatus UART0_GetITStatus(UART0_IT_Flags_TypeDef flag)
{
  ITStatus status = RESET;
  if( UART0_RI == flag ) {
    status = (ITStatus)(RI);
  } else if( UART0_TI == flag){
    status = (ITStatus)(TI);
  }
  return status;
}
void UART0_SetITStatus(UART0_IT_Flags_TypeDef flag)
{
  if( UART0_RI == flag ) {
    set_RI;
  } else if( UART0_TI == flag){
    set_TI;
  }
}
void UART0_ClearITStatus(UART0_IT_Flags_TypeDef flag)
{
  if( UART0_RI == flag ) {
    clr_RI;
  } else if( UART0_TI == flag){
    clr_TI;
  }
}
void UART0_SendData(uint8_t data)
{
  SBUF = data;
}
uint8_t UART0_GetData(void)
{
  return (uint8_t)SBUF;
}

/**
  * @}
  */



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
#include "test.h"
#include "inc.h"
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
void Test_Task(void *args)
{
  static uint16_t counter = 0;
  GPIO_Util_Init(INDICATOR_LED_PORT,INDICATOR_LED_PIN,GPIO_MODE_OUT_OD_LOW_SLOW);
  if( ++counter == 500) {
    GPIO_Util_Toggle(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
    counter = 0; 
  }
}

void Test_IR_Receiver(void *args)
{
  IR_Signal_State_TypeDef state = IR_Receiver_GetState();
  
  if( state == IR_HIDDEN ){//|| state == IR_LONG_PULSE 
     GPIO_Util_WriteHigh(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
  } else {
    GPIO_Util_WriteLow(INDICATOR_LED_PORT,INDICATOR_LED_PIN);
  }
}

/**
  * @}
  */



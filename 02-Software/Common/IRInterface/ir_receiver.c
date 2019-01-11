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
#include "ir_receiver.h"
#include "stm8s_adc1.h"
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

void IR_Receiver_Init(void)
{
  //Init ADC
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,
            ADC1_CHANNEL_2,
            ADC1_PRESSEL_FCPU_D2,
            ADC1_EXTTRIG_TIM,
            DISABLE,
            ADC1_ALIGN_LEFT,
            ADC1_SCHMITTTRIG_CHANNEL2,
            DISABLE);
  ADC1_StartConversion();
  uint16_t v = ADC1_GetConversionValue();
}

/**
  * @}
  */



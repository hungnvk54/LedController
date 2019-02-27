/**
  ******************************************************************************
  * @file    N76E003_adc.c
  * @author  
  * @version 
  * @date    
  * @brief   
  * ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "N76E003_adc.h"
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
void ADC_Init(ADC_Trigger_Source_TypeDef triggerSrc,ADC_Channel_TypeDef channel)
{
  //1.Set Input source
  ADC_SwitchChannel(channel);
  
  //2.Set Trigger Source
  if( triggerSrc != ADC_ADCS) {
    ADCCON0 |= ((triggerSrc & 0x03)<<4);
    set_ADCEX;
  }
}
void ADC_SwitchChannel(ADC_Channel_TypeDef channel)
{
  switch( channel)
  {
  case ADC_AIN0:
    ADCCON0&=0xF0;
    P17_Input_Mode;
    AINDIDS=0x00;
    AINDIDS|=SET_BIT0;
    break;
  case ADC_AIN1:
    ADCCON0&=0xF0;
    ADCCON0|=0x01;
    P30_Input_Mode;
    AINDIDS=0x00;
    AINDIDS|=SET_BIT1;		//P30
    break;
  case ADC_AIN2:
    ADCCON0&=0xF0;
    ADCCON0|=0x02;
    P07_Input_Mode;
    AINDIDS=0x00;		//P07
    break;
  case ADC_AIN3:
    ADCCON0&=0xF0;
    ADCCON0|=0x03;
    P06_Input_Mode;
    AINDIDS=0x00;
    AINDIDS|=SET_BIT3; //P06
    break;
  case ADC_AIN4:
    ADCCON0&=0xF0;
    ADCCON0|=0x04;
    P05_Input_Mode;
    AINDIDS=0x00;
    AINDIDS|=SET_BIT4;//P05
    break;
  case ADC_AIN5:
    ADCCON0&=0xF0;
    ADCCON0|=0x05;
    P04_Input_Mode;
    AINDIDS=0x00;
    AINDIDS|=SET_BIT5;//P04
    break;
  case ADC_AIN6:
    ADCCON0&=0xF0;
    ADCCON0|=0x06;
    P03_Input_Mode;
    AINDIDS=0x00;
    AINDIDS|=SET_BIT6;		//P03
    break;
  case ADC_AIN7:
    ADCCON0&=0xF0;
    ADCCON0|=0x07;
    P11_Input_Mode;
    AINDIDS=0x00;
    AINDIDS|=SET_BIT7;		//P11
    break;
  case ADC_BandGap:
    ADCCON0|=SET_BIT3;
    ADCCON0&=0xF8;//Band-gap 1.22V
    break;
  }
}
void ADC_Cmd(FunctionalState state)
{
  if( ENABLE == state )
  {
    set_ADCEN;
  } else {
    clr_ADCEN;
  }
}
void ADC_StartConversation(void)
{
  if( ADCS) return;//1.ADC is converting. Nothing to do
  
  set_ADCS;
}
uint16_t ADC_GetResult(void)
{
  uint16_t result;
  
  //1.Wait here until conversation is completed
  while(ADCS);
  
  //2.Read Register and build result
  result = ADCRH;
  result = (result<<4)|(ADCRL&0x0F);
  
  return result;
}

/**
  * @}
  */



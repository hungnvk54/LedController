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
#include "N76E003_pwm.h"
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
void PWM_Init( PWM_Prescaler_TypeDef prescale, uint16_t comapre, uint16_t duty,PWM_Channel_TypeDef channel)
{
  //1. Firtly, clear timer counter
  set_CLRPWM;
  
  //2. Setup Clock Source and Prescale
  PWM_CLOCK_FSYS;
  PWMCON1 &= (~(uint8_t)prescale);
  PWMCON1 |= (uint8_t)prescale;
  
  //3.Setup period
  PWMPH = (uint8_t)(comapre>>8);
  PWMPL = (uint8_t)(comapre&0xFF);
  
  //4.Settup Duty
  if( channel & PWM_PIO0)
  {
     P12_Quasi_Mode;
     PWM0H = (uint8_t)(duty >> 8);
     PWM0L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO1)
  {
     P11_Quasi_Mode;
     PWM1H = (uint8_t)(duty >> 8);
     PWM1L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO2)
  {
     P10_Quasi_Mode;
     PWM2H = (uint8_t)(duty >> 8);
     PWM2L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO3)
  {
    P00_Quasi_Mode;
     PWM3H = (uint8_t)(duty >> 8);
     PWM3L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO4)
  {
    P01_Quasi_Mode;
     PWM4H = (uint8_t)(duty >> 8);
     PWM4L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO5)
  {
    P03_Quasi_Mode;
     PWM5H = (uint8_t)(duty >> 8);
     PWM5L = (uint8_t)(duty &0xFF);
  }
  
  //5.Enable Waveform output of channel 0
  //PIOCON0 &= 0xC0;//Disable all
  PIOCON0 |= (uint8_t)channel;
 }
void PWM_Cmd(FunctionalState state)
{
  if( ENABLE == state )
  {
    set_PWMRUN;
  } else {
    clr_PWMRUN;
  }
}
void PWM_UpdateDuty(uint16_t duty, PWM_Channel_TypeDef channel)
{
  while( PWMCON0 & SET_BIT6 );///Wait here until previous chane has effected
  
  //1.Free to update the duty to the register
  if( channel & PWM_PIO0)
  {
     PWM0H = (uint8_t)(duty >> 8);
     PWM0L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO1)
  {
     PWM1H = (uint8_t)(duty >> 8);
     PWM1L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO2)
  {
     PWM2H = (uint8_t)(duty >> 8);
     PWM2L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO3)
  {
     PWM3H = (uint8_t)(duty >> 8);
     PWM3L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO4)
  {
     PWM4H = (uint8_t)(duty >> 8);
     PWM4L = (uint8_t)(duty &0xFF);
  }
  if( channel & PWM_PIO5)
  {
     PWM5H = (uint8_t)(duty >> 8);
     PWM5L = (uint8_t)(duty &0xFF);
  }
  //2. Notify the duty has been changed
  PWMCON0 |= SET_BIT6;
  
  //3. Enable Output To the uC Pin
  PWM_CmdChannel(ENABLE,channel);
}

void PWM_CmdChannel(FunctionalState state, PWM_Channel_TypeDef channel)
{
  if( ENABLE == state )
  {
    PIOCON0 |= (uint8_t)channel;
  } else {
    PIOCON0 &= (~(uint8_t)channel);
  }
}
/**
  * @}
  */



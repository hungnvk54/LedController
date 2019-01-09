/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_clk.h"
#include "stm8s_tim2.h"
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Clock_Config(void) {
//  CLK_DeInit();
  
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

//  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  
  //CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

void Tim_Config(void) {
  TIM2_TimeBaseInit(TIM2_PRESCALER_16, 10);
  TIM2_ARRPreloadConfig(ENABLE);

  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
    
  TIM2_Cmd(ENABLE);
  //Enable interrupt
  enableInterrupts();
}

void main(void)
{
  /* Infinite loop */
  Clock_Config();
  GPIO_Init(GPIOB, GPIO_PIN_5,GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Write(GPIOB, 0);
  uint32_t counter = 0;
  uint8_t mask = 0;
  Tim_Config();
  enableInterrupts();
  while (1)
  {
//    if( counter >= 100000) {
//        counter = 0;
//        if( mask == 0) {
//          GPIO_Write(GPIOB, 0);
//          mask = 1;
//        } else {
//          GPIO_Write(GPIOB, 255);
//          mask = 0;
//        }
//    }
//    
//    counter++;
  }
  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

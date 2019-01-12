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
#include "gpio_util.h"
#include "timer_counter.h"
#include "timer_pwm.h"
#include "transport.h"
#include "ir_transmitter.h"
#include "ir_receiver.h"
#include "taskmanager.h"
#include "led_controller.h"
#include "commands.h"
#include "nodecontrol.h"
#include "nodestatemanager.h"
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void System_Init();
void Clock_Config(void);
void Task_Init(void);
void Test_Task(void *args);
void Test_Uart(void *args);
/* Private functions ---------------------------------------------------------*/

void System_Init()
{
  Clock_Config();
  Timer_Counter_Init();
  Timer_PWM_Init();
  Transport_Init();
  IR_Receiver_Init();
  IR_Transmitter_Init(IR_OUTPUT_MODE_PWM);
  Led_Control_Init(CONTROL_MODE_DIMMING);
  
  ///Init node control
  Node_Control_InitNodes();
  Node_State_Manager_Init();
}
    
void Clock_Config(void) { 
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

void Task_Init(void)
{
  if( IR_OUTPUT_MODE_PWM == IR_Transmitter_GetMode()){
    Task_Manager_AddTask(&Timer_PWM_Update_Period);
  }
  if( CONTROL_MODE_DIMMING == Led_Control_GetMode())
  {
    Task_Manager_AddTask(&IR_Transmitter_Task);
  }
  
  Task_Manager_AddTask(&Command_Task); /* This task will get data from the 
                                        RX buffer then process command */
//  Task_Manager_AddTask(&Node_Control_Task); /*This task will process command
//                                            which is received from Network */
  Task_Manager_AddTask(&Node_State_Manager_Task);
//  Task_Manager_AddTask(&Test_Task);
  Task_Manager_AddTask(&Test_Uart);
}

void Test_Task(void *args)
{
  static uint16_t counter = 0;
  if( ++counter == 500) {
    GPIO_Util_Toggle(LED_PORT,LED_PIN);
    counter = 0; 
  }
}

void Test_Uart(void *args)
{
  if(GPIO_ReadInputData(GPIOA) & GPIO_PIN_1) {
    Transport_TxPush(1);
//    GPIO_Util_WriteHigh(LED_PORT,LED_PIN);

  } else {
    Transport_TxPush(0);
//    GPIO_Util_WriteLow(LED_PORT,LED_PIN);
  }
  uint8_t data = 0;
  if( Transport_RxPop(&data) == SUCCESS) {
    if( data == 1 ) {
      GPIO_Util_WriteHigh(LED_PORT,LED_PIN);
    } else {
      GPIO_Util_WriteLow(LED_PORT,LED_PIN);
    }
  }
}

void main(void)
{
  /* Infinite loop */
  System_Init();
  Task_Init();
  
  /*For Test Only*/
  GPIO_Init(GPIOA,GPIO_PIN_1,GPIO_MODE_IN_FL_NO_IT);
//  GPIO_Util_Init();
  GPIO_Util_Init_As_Out(LED_PORT,LED_PIN);
//  GPIO_Util_Init_As_Out(GPIOD,GPIO_PIN_3);
//  GPIO_WriteLow(GPIOD,GPIO_PIN_3);
  
  uint32_t previous_counter = 0;
  while (1)
  {
    if( previous_counter <= Timer_Counter_GetCounter() )
    {
      if((Timer_Counter_GetCounter()  - previous_counter) > TICK_IN_MS) { //TICK_IN_MS
        Task_Manager_PerformTask();
        previous_counter = Timer_Counter_GetCounter();
      }
    } else {
      ///Counter Overflow - Update the previous_counter value
        previous_counter = Timer_Counter_GetCounter();
    }
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
  static uint32_t counter = 0;
  
  /* Infinite loop */
  while (1)
  {
    if( ++counter == 10000) {
    GPIO_Util_Toggle(LED_PORT,LED_PIN);
    counter = 0; 
  }
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

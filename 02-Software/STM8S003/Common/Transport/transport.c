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
#include "transport.h"
#include "stm8s_uart1.h"
#include "gpio_util.h"
#include "system_def.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define                 MAX_RX_BUFFER           64
#define                 MAX_TX_BUFFER           128

/* Private variables ---------------------------------------------------------*/
#if     (MAX_TX_BUFFER <=127)
uint8_t tx_buff[MAX_TX_BUFFER];
volatile uint8_t tx_wr_idx = 0, tx_rd_idx= 0, tx_cnt = 0;
#else
volatile uint16_t tx_buff[MAX_TX_BUFFER];
volatile uint16_t tx_wr_idx = 0, tx_rd_idx= 0, tx_cnt = 0;
#endif

#if     (MAX_RX_BUFFER <=127)
volatile uint8_t rx_buff[MAX_RX_BUFFER];
volatile uint8_t rx_wr_idx= 0, rx_rd_idx= 0, rx_cnt = 0;
#else
uint16_t rx_buff[MAX_RX_BUFFER];
volatile uint16_t rx_wr_idx= 0, rx_rd_idx= 0, rx_cnt = 0;
#endif

volatile uint8_t debug_variable = 0;

/* Private function prototypes -----------------------------------------------*/
void tx_interrupt_config(FunctionalState state);
void rx_interrupt_config(FunctionalState state);
/* Private functions ---------------------------------------------------------*/
void tx_interrupt_config(FunctionalState state)
{
    UART1_ITConfig(UART1_IT_TC, state);
}
void rx_interrupt_config(FunctionalState state)
{
    UART1_ITConfig(UART1_IT_RXNE_OR, state);
}

/* Public functions ----------------------------------------------------------*/
void Transport_Init(void)
{
  //Init transmit channel
    /* Deinitializes the UART1 and UART3 peripheral */
    UART1_DeInit();
    /* UART1 configuration -------------------------------------------------*/
    /* UART1 configured as follow:
          - BaudRate = 9600 baud  
          - Word Length = 8 Bits
          - One Stop Bit
          - No parity
          - Receive and transmit enabled
          - UART1 Clock disabled
     */
    /* Configure the UART1 */
    UART1_Init((uint32_t)TRANSPORT_BAUDRATE, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    /* Enable UART1 Transmit interrupt*/
    UART1_ITConfig(UART1_IT_TC, ENABLE);
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
    
    /* Config Driver Pin to Control MAX485 IC */
    GPIO_Util_Init(TRANSPORT_OUTPUT_DRIVER_PORT,TRANSPORT_OUTPUT_DRIVER_PIN,GPIO_MODE_OUT_PP_LOW_FAST);//GPIO_MODE_OUT_OD_LOW_FAST
//    GPIO_Util_WriteLow(TRANSPORT_OUTPUT_DRIVER_PORT,TRANSPORT_OUTPUT_DRIVER_PIN);
}

void Transport_TxPush(uint8_t data)
{
  while( tx_cnt >= MAX_TX_BUFFER ); //Wait here until data is send
//  if( tx_cnt )
//  {
    tx_buff[tx_wr_idx] = data;
    tx_interrupt_config(DISABLE);
//    disableInterrupts();
    ++tx_cnt;
    tx_interrupt_config(ENABLE);
//    enableInterrupts();
    ++tx_wr_idx;
    if( tx_wr_idx >= MAX_TX_BUFFER ) tx_wr_idx = 0;
//  } else {
//    Transport_OutputEnable();
//    UART1_SendData8(data);
//    tx_interrupt_config(ENABLE);
//  }
    tx_interrupt_config(ENABLE);
}
uint8_t Transport_TxPop(uint8_t *data)
{
    if(tx_cnt == 0 )
    {
      tx_interrupt_config(DISABLE);
      return FAILED;
    }
    *data = tx_buff[tx_rd_idx];
    --tx_cnt;
    ++tx_rd_idx;
    if( MAX_TX_BUFFER == tx_rd_idx ) tx_rd_idx = 0;
    return SUCCESS;
}

void Transport_RxPush(uint8_t data)
{
  if( rx_cnt >= MAX_TX_BUFFER ) return; //Wait here until data is send
  rx_buff[rx_wr_idx] = data;
  ++rx_cnt;
  ++rx_wr_idx;
  if( rx_wr_idx >= MAX_RX_BUFFER ) rx_wr_idx = 0;
  
}
uint8_t Transport_RxPop(uint8_t *data)
{
  if(rx_cnt == 0 )
  {
    return FAILED;
  }
  *data = rx_buff[rx_rd_idx];
  rx_interrupt_config(DISABLE);
  --rx_cnt;
  rx_interrupt_config(ENABLE);
  ++rx_rd_idx;
  if( MAX_RX_BUFFER == rx_rd_idx ) rx_rd_idx = 0;
  
  return SUCCESS;
}

void Transport_Write(uint8_t *data, uint16_t length)
{
  uint16_t read_idx = 0;;
  while( length > 0)
  {
    Transport_TxPush(data[read_idx++]);
    length--;
  }
}
uint16_t Transport_Read(uint8_t *data, uint16_t length)
{
   uint16_t real_length = 0;
   uint16_t read_idx = 0;
   while( real_length < length)
   {
     uint8_t d;
     if( SUCCESS == Transport_RxPop(&d) ){
        data[read_idx++] = d;
        real_length++;
     } else {
       break;
     }
   }
   
   return real_length;
}

uint8_t Transport_GetRxBufferSize(void)
{
  return rx_cnt;
}

uint8_t Transport_IsBufferEmpty(void)
{
  return tx_cnt>0?FALSE:TRUE;
}

void Transport_OutputEnable(void)
{
  GPIO_Util_WriteHigh(TRANSPORT_OUTPUT_DRIVER_PORT,TRANSPORT_OUTPUT_DRIVER_PIN);
//    GPIO_Util_WriteHigh(TRANSPORT_OUTPUT_DRIVER_PORT,TRANSPORT_OUTPUT_DRIVER_PIN);
  debug_variable = 1;
}
void Transport_OutputDisable(void)
{
  debug_variable = 0;
//  GPIO_Util_WriteLow(TRANSPORT_OUTPUT_DRIVER_PORT,TRANSPORT_OUTPUT_DRIVER_PIN);
  GPIO_Util_WriteLow(TRANSPORT_OUTPUT_DRIVER_PORT,TRANSPORT_OUTPUT_DRIVER_PIN);
}
/**
  * @}
  */



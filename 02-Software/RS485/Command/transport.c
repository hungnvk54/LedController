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
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define                 MAX_RX_BUFFER           64
#define                 MAX_TX_BUFFER           64

#define                 BAUDRATE                19200
/* Private variables ---------------------------------------------------------*/
uint8_t tx_buff[MAX_TX_BUFFER];
uint8_t tx_wr_idx = 0, tx_rd_idx= 0, tx_cnt = 0;

uint8_t rx_buff[MAX_RX_BUFFER];
uint8_t rx_wr_idx= 0, rx_rd_idx= 0, rx_cnt = 0;
/* Private function prototypes -----------------------------------------------*/
void tx_interrupt_config(FunctionalState state);
void rx_interrupt_config(FunctionalState state);
/* Private functions ---------------------------------------------------------*/
void tx_interrupt_config(FunctionalState state)
{
    UART1_ITConfig(UART1_IT_TXE, state);
}
void rx_interrupt_config(FunctionalState state)
{
    UART1_ITConfig(UART1_IT_RXNE, state);
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
    UART1_Init((uint32_t)BAUDRATE, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    /* Enable UART1 Transmit interrupt*/
    UART1_ITConfig(UART1_IT_TXE, ENABLE);
    UART1_ITConfig(UART1_IT_RXNE, ENABLE);
}

void Transport_TxPush(uint8_t data)
{
  while( tx_cnt >= MAX_TX_BUFFER ); //Wait here until data is send
  tx_interrupt_config(DISABLE);
  tx_buff[tx_wr_idx] = data;
  ++tx_cnt;
  ++tx_wr_idx;
  if( tx_wr_idx >= MAX_TX_BUFFER ) tx_wr_idx = 0;
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
  rx_interrupt_config(DISABLE);
  rx_buff[rx_wr_idx] = data;
  ++rx_cnt;
  ++rx_wr_idx;
  if( rx_wr_idx >= MAX_RX_BUFFER ) rx_wr_idx = 0;
  rx_interrupt_config(ENABLE);
}
uint8_t Transport_RxPop(uint8_t *data)
{
  if(rx_cnt == 0 )
  {
    return FAILED;
  }
  *data = rx_buff[rx_rd_idx];
  --rx_cnt;
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

/**
  * @}
  */



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
#include "write_flash.h"
#include "inc.h"
#include "gpio_util.h"
#include <math.h>
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint32_t start_add = 0x4000;
const uint32_t mask_add = 0x4008;
const uint8_t mask_val = 0x55;

const uint32_t start_add_output_state = 0x4010;
const uint32_t mask_add_output_state = 0x4014;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
void Flash_Init(void)
{
  /*Define FLASH programming time*/
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
}
void Flash_Write_ActivePeriod(double period)
{
  static double previous_value = -1;
  if( period > 1 ) return;
  if( previous_value < 0) previous_value = period;
  if( fabs(previous_value - period) < 0.005) {
    return;
  }
  previous_value = period;
  uint32_t new_val = (uint32_t)(U32_MAX* period);
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  FLASH_ProgramWord(start_add, new_val);
  
  FLASH_ProgramByte(mask_add, mask_val);
  FLASH_Lock(FLASH_MEMTYPE_DATA);
  //U32_MAX
}
double Flash_Read_ActivePeriod()
{
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  uint8_t mask = FLASH_ReadByte(mask_add);
  if( mask != mask_val) {
    FLASH_Lock(FLASH_MEMTYPE_DATA);
    return 1.0;
  } else {
    uint32_t addr = start_add;
    uint32_t reading_byte = 0;
     
    for( uint8_t i = 0; i < 4 ; ++i )
    {
      uint8_t b = FLASH_ReadByte(addr);
      reading_byte <<=8;
      reading_byte |= b;
      addr = addr + 1;
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA);
    return ((double)reading_byte)/U32_MAX;
  }
}

void Flash_Write_OutputMode(unsigned char mode)
{
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  FLASH_ProgramByte(start_add_output_state, mode);
  
  FLASH_ProgramByte(mask_add_output_state, mask_val);
  FLASH_Lock(FLASH_MEMTYPE_DATA);
}

uint8_t Flash_Read_OutputMode(void)
{
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  uint8_t mask = FLASH_ReadByte(mask_add_output_state);
  if( mask != mask_val) {
    FLASH_Lock(FLASH_MEMTYPE_DATA);
    return 1;
  } else {
    unsigned char mode = FLASH_ReadByte(start_add_output_state);
    FLASH_Lock(FLASH_MEMTYPE_DATA);
    return mode;
  }
}

/**
  * @}
  */



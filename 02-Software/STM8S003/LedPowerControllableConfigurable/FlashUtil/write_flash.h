/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_UTIL_H
#define __FLASH_UTIL_H

/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Flash_Init(void);
void Flash_Write_ActivePeriod(double period);
double Flash_Read_ActivePeriod(void);

void Flash_Write_OutputMode(unsigned char mode);
unsigned char Flash_Read_OutputMode(void);
#endif /* __FLASH_UTIL_H */


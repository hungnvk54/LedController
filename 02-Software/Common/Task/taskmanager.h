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
#ifndef __TASK_MANAGER_H
#define __TASK_MANAGER_H

/* Includes ------------------------------------------------------------------*/
#include "task.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Task_Manager_AddTask(Task *task);
void Task_Manager_PerformTask(void);

#endif /* __TASK_MANAGER_H */


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
#include "taskmanager.h"
#include "inc.h"
/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define MAX_TASK                10
/* Private variables ---------------------------------------------------------*/
// External Task
Task *tasks[MAX_TASK];
uint8_t task_Index = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

void Task_Manager_AddTask(Task *task)
{
  tasks[task_Index] = task;
  task_Index++;
}

void Task_Manager_PerformTask(void)
{
  uint8_t index;
  for( index = 0; index < task_Index; ++index )
  {
    tasks[index](0);
  }
}

/**
  * @}
  */



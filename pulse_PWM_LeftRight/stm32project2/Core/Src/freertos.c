/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include "i2c.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t flag=1;
uint8_t flag_key=1;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for motor_move */
osThreadId_t motor_moveHandle;
const osThreadAttr_t motor_move_attributes = {
  .name = "motor_move",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for motor_dir */
osThreadId_t motor_dirHandle;
const osThreadAttr_t motor_dir_attributes = {
  .name = "motor_dir",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void stepper_turn(uint8_t dir);
void stepper_stop(void);
void judge_pulse(void);
void BlinkLEDs(void);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of motor_move */
  motor_moveHandle = osThreadNew(StartDefaultTask, NULL, &motor_move_attributes);

  /* creation of motor_dir */
  motor_dirHandle = osThreadNew(StartTask02, NULL, &motor_dir_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */

  for(;;) {
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
      osDelay(10);
      flag = 0;
    }

    if(flag == 0 && flag_key == 1) {
      if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET) {
        stepper_turn(CW);
      }
      flag = 1;
    }
    /////////////////////////////////////////////////////////////////////
    if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == GPIO_PIN_RESET) {
      osDelay(10);
      flag_key = 0;
    }

    if(flag_key == 0 && flag == 1) {
      if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == GPIO_PIN_SET) {
        stepper_turn(CCW);
      }
      flag_key = 1;
    }
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
	/* Infinite loop */
	for(;;) {
		osDelay(10);
	}
  /* USER CODE END StartTask02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void stepper_turn(uint8_t dir)
{
  if(dir==CW)        //顺时针
  {
    HAL_GPIO_WritePin(MOTOR_DIR_GPIO_PORT,MOTOR_DIR_PIN,HIGH);
  }
  else if(dir==CCW)//逆时针
  {
    HAL_GPIO_WritePin(MOTOR_DIR_GPIO_PORT,MOTOR_DIR_PIN,LOW);
  }
  /*开使能*/
  HAL_GPIO_WritePin(MOTOR_EN_GPIO_PORT,MOTOR_EN_PIN,GPIO_PIN_SET);
}

void stepper_stop(void) {
  HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_1);
  HAL_GPIO_WritePin(MOTOR_EN_GPIO_PORT,MOTOR_EN_PIN,GPIO_PIN_RESET);
}


void BlinkLEDs(void) {
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5);
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
  osDelay(100);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5);
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
  osDelay(300);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5);
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
  osDelay(100);
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5);
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
  osDelay(300);
}
/* USER CODE END Application */


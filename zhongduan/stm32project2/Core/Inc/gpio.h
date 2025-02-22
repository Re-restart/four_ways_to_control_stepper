/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
#define LED1_Toggle() do{HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5);}while(0)
#define LED2_Toggle() do{HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);}while(0)


#define Pulse_Toggle() do{HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);}while(0)
#define Dir_CW() do{HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);}while(0)
#define Dir_CC() do{HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);}while(0)

  //Motor 使能
#define MOTOR_EN_PIN                        GPIO_PIN_7
#define MOTOR_EN_GPIO_PORT                  GPIOA

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */


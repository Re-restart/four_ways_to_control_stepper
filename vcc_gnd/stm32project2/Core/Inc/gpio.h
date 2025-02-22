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
  //Motor 方向
#define MOTOR_DIR_PIN                       GPIO_PIN_6
#define MOTOR_DIR_GPIO_PORT                 GPIOA
#define MOTOR_DIR_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

  //Motor 使能
#define MOTOR_EN_PIN                        GPIO_PIN_7
#define MOTOR_EN_GPIO_PORT                  GPIOA
#define MOTOR_EN_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

  //Motor 脉冲
#define MOTOR_PUL_PIN                       GPIO_PIN_5
#define MOTOR_PUL_GPIO_PORT                 GPIOA
#define MOTOR_PUL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

#define HIGH GPIO_PIN_SET         //高电平
#define LOW  GPIO_PIN_RESET     //低电平

#define CW  HIGH                        //顺时针
#define CCW LOW                       //逆时针
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */


/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define led_red_Pin GPIO_PIN_13
#define led_red_GPIO_Port GPIOC
#define buzzer_Pin GPIO_PIN_14
#define buzzer_GPIO_Port GPIOC
#define led_yellow_Pin GPIO_PIN_15
#define led_yellow_GPIO_Port GPIOC
#define led_green_Pin GPIO_PIN_1
#define led_green_GPIO_Port GPIOA
#define led_status_Pin GPIO_PIN_11
#define led_status_GPIO_Port GPIOB
#define D1_RS_Pin GPIO_PIN_15
#define D1_RS_GPIO_Port GPIOA
#define D1_RW_Pin GPIO_PIN_0
#define D1_RW_GPIO_Port GPIOD
#define D1_E_Pin GPIO_PIN_1
#define D1_E_GPIO_Port GPIOD
#define D1_D4_Pin GPIO_PIN_2
#define D1_D4_GPIO_Port GPIOD
#define D1_D5_Pin GPIO_PIN_3
#define D1_D5_GPIO_Port GPIOD
#define D1_D6_Pin GPIO_PIN_3
#define D1_D6_GPIO_Port GPIOB
#define D1_D7_Pin GPIO_PIN_4
#define D1_D7_GPIO_Port GPIOB
#define button_1_Pin GPIO_PIN_5
#define button_1_GPIO_Port GPIOB
#define button_2_Pin GPIO_PIN_6
#define button_2_GPIO_Port GPIOB
#define button_3_Pin GPIO_PIN_7
#define button_3_GPIO_Port GPIOB
#define button_4_Pin GPIO_PIN_8
#define button_4_GPIO_Port GPIOB
#define button_5_Pin GPIO_PIN_9
#define button_5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

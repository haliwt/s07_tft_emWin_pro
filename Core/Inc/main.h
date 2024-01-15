/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define ADC_FAN_Pin GPIO_PIN_0
#define ADC_FAN_GPIO_Port GPIOA
#define ADC_NTC_Pin GPIO_PIN_1
#define ADC_NTC_GPIO_Port GPIOA
#define TX_WIFI_Pin GPIO_PIN_2
#define TX_WIFI_GPIO_Port GPIOA
#define RX_WIFI_Pin GPIO_PIN_3
#define RX_WIFI_GPIO_Port GPIOA
#define WIFI_EN_Pin GPIO_PIN_4
#define WIFI_EN_GPIO_Port GPIOA
#define KEY_LED_CTL_Pin GPIO_PIN_5
#define KEY_LED_CTL_GPIO_Port GPIOA
#define KEY_POWER_LED_Pin GPIO_PIN_6
#define KEY_POWER_LED_GPIO_Port GPIOA
#define PLASMA_CTL_Pin GPIO_PIN_7
#define PLASMA_CTL_GPIO_Port GPIOA
#define RELAY_CTL_Pin GPIO_PIN_0
#define RELAY_CTL_GPIO_Port GPIOB
#define BEEP_PWM_Pin GPIO_PIN_1
#define BEEP_PWM_GPIO_Port GPIOB
#define PTC_LED_Pin GPIO_PIN_2
#define PTC_LED_GPIO_Port GPIOB
#define RAT_LED_Pin GPIO_PIN_10
#define RAT_LED_GPIO_Port GPIOB
#define POWER_KEY_Pin GPIO_PIN_11
#define POWER_KEY_GPIO_Port GPIOB
#define MODE_KEY_Pin GPIO_PIN_12
#define MODE_KEY_GPIO_Port GPIOB
#define ADD_KEY_Pin GPIO_PIN_13
#define ADD_KEY_GPIO_Port GPIOB
#define DEC_KEY_Pin GPIO_PIN_14
#define DEC_KEY_GPIO_Port GPIOB
#define ULTRA_PWM_Pin GPIO_PIN_8
#define ULTRA_PWM_GPIO_Port GPIOA
#define V_TX_Pin GPIO_PIN_9
#define V_TX_GPIO_Port GPIOA
#define V_RX_Pin GPIO_PIN_10
#define V_RX_GPIO_Port GPIOA
#define FAN_CTL_2_Pin GPIO_PIN_0
#define FAN_CTL_2_GPIO_Port GPIOD
#define FAN_CTL_1_Pin GPIO_PIN_1
#define FAN_CTL_1_GPIO_Port GPIOD
#define TEMP_SENSOR_Pin GPIO_PIN_2
#define TEMP_SENSOR_GPIO_Port GPIOD
#define TFT_RESET_Pin GPIO_PIN_3
#define TFT_RESET_GPIO_Port GPIOD
#define WIFI_LED_Pin GPIO_PIN_7
#define WIFI_LED_GPIO_Port GPIOB
#define KILL_LED_Pin GPIO_PIN_9
#define KILL_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

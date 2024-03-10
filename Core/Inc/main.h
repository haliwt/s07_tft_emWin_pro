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
//TFT backlight GPIO
#define TFT_BACKLIGHT_Pin 								GPIO_PIN_6
#define TFT_BACKLIGHT_GPIO_Port 						GPIOB

#define TFT_DCX_Pin 									GPIO_PIN_15
#define TFT_DCX_GPIO_Port 								GPIOC

//ADC
#define ADC_FAN_Pin GPIO_PIN_0
#define ADC_FAN_GPIO_Port GPIOA
#define ADC_NTC_Pin GPIO_PIN_1
#define ADC_NTC_GPIO_Port GPIOA
//USART2 WIFI 
#define TX_WIFI_Pin GPIO_PIN_2
#define TX_WIFI_GPIO_Port GPIOA
#define RX_WIFI_Pin GPIO_PIN_3
#define RX_WIFI_GPIO_Port GPIOA
#define WIFI_EN_Pin GPIO_PIN_4
#define WIFI_EN_GPIO_Port GPIOA

//LED 0F KEY
#define LED_KEY_TIM_Pin GPIO_PIN_5
#define LED_KEY_TIM_GPIO_Port GPIOA

//LED OF DISP
#define LED_POWER_Pin GPIO_PIN_6
#define LED_POWER_GPIO_Port GPIOA

#define LED_PTC_Pin GPIO_PIN_2
#define LED_PTC_GPIO_Port GPIOB
#define LED_RAT_Pin GPIO_PIN_10
#define LED_RAT_GPIO_Port GPIOB

#define LED_WIFI_Pin GPIO_PIN_7
#define LED_WIFI_GPIO_Port GPIOB
#define LED_KILL_Pin GPIO_PIN_9
#define LED_KILL_GPIO_Port GPIOB

//FUN 
#define PLASMA_CTL_Pin GPIO_PIN_7
#define PLASMA_CTL_GPIO_Port GPIOA


//relay CONTROL gpio
#define RELAY_CTL_Pin GPIO_PIN_0
#define RELAY_CTL_GPIO_Port GPIOB


#define BEEP_PWM_Pin GPIO_PIN_1
#define BEEP_PWM_GPIO_Port GPIOB



#define ULTRA_PWM_Pin GPIO_PIN_8
#define ULTRA_PWM_GPIO_Port GPIOA

#define FAN_CTL_2_Pin GPIO_PIN_0
#define FAN_CTL_2_GPIO_Port GPIOD
#define FAN_CTL_1_Pin GPIO_PIN_1
#define FAN_CTL_1_GPIO_Port GPIOD
//
//KEY 
#define KEY_POWER_Pin 							GPIO_PIN_11
#define KEY_POWER_GPIO_Port 					GPIOB
#define KEY_POWER_EXTI_IRQn 					EXTI4_15_IRQn

#define KEY_MODE_Pin 							GPIO_PIN_12
#define KEY_MODE_GPIO_Port 						GPIOB
#define KEY_MODE_EXTI_IRQn 						EXTI4_15_IRQn


#define KEY_ADD_Pin 							GPIO_PIN_13
#define KEY_ADD_GPIO_Port 						GPIOB
#define KEY_ADD_EXTI_IRQn 						EXTI4_15_IRQn

#define KEY_DEC_Pin 							GPIO_PIN_14
#define KEY_DEC_GPIO_Port 						GPIOB
#define KEY_ADD_EXTI_IRQn 						EXTI4_15_IRQn




//
//VOICE USART1 
#define VOICE_TX_Pin GPIO_PIN_9
#define VOICE_TX_GPIO_Port GPIOA
#define VOICE_RX_Pin GPIO_PIN_10
#define VOICE_RX_GPIO_Port GPIOA
//TFT SCREEN
#define TFT_NSS_Pin GPIO_PIN_15
#define TFT_NSS_GPIO_Port GPIOA

#define TFT_RESET_Pin GPIO_PIN_3
#define TFT_RESET_GPIO_Port GPIOD

//DHT11 
#define TEMP_SENSOR_Pin                   GPIO_PIN_2
#define TEMP_SENSOR_GPIO_Port             GPIOD
//



/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

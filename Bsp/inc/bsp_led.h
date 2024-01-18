#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "main.h"



#define LED_POWER_KEY_SetHigh()            HAL_GPIO_WritePin(LED_POWER_GPIO_Port,LED_POWER_Pin,GPIO_PIN_SET)    // output high level
#define LED_POWER_KEY_SetLow()             HAL_GPIO_WritePin(LED_POWER_GPIO_Port,LED_POWER_Pin,GPIO_PIN_RESET)    // output low level

#define LED_MODE_SetHigh()            HAL_GPIO_WritePin(LED_KEY_TIM_GPIO_Port,LED_KEY_TIM_Pin,GPIO_PIN_SET)    // output high level
#define LED_MODE_SetLow()             HAL_GPIO_WritePin(LED_KEY_TIM_GPIO_Port,LED_KEY_TIM_Pin,GPIO_PIN_RESET)    // output low level

//#define BACKLIGHT_SetHigh()            HAL_GPIO_WritePin(LCD_LIGHT_GPIO_Port,LCD_LIGHT_Pin,GPIO_PIN_SET)    // output high level
//#define BACKLIGHT_SetLow()             HAL_GPIO_WritePin(LCD_LIGHT_GPIO_Port,LCD_LIGHT_Pin,GPIO_PIN_RESET)    



void LED_Mode_On(void);
void LED_Mode_Off(void);

void LED_Power_On(void);
//void LED_Power_Off(void);


//void Backlight_On(void);
//void Backlight_Off(void);

void Breath_Led(void);


#endif 


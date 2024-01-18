#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "main.h"



#define LED_POWER_KEY_SetHigh()            HAL_GPIO_WritePin(LED_POWER_GPIO_Port,LED_POWER_Pin,GPIO_PIN_SET)    // output high level
#define LED_POWER_KEY_SetLow()             HAL_GPIO_WritePin(LED_POWER_GPIO_Port,LED_POWER_Pin,GPIO_PIN_RESET)    // output low level

#define LED_MODE_KEY_SetHigh()            HAL_GPIO_WritePin(LED_KEY_TIM_GPIO_Port,LED_KEY_TIM_Pin,GPIO_PIN_SET)    // output high level
#define LED_MODE_KEY_SetLow()             HAL_GPIO_WritePin(LED_KEY_TIM_GPIO_Port,LED_KEY_TIM_Pin,GPIO_PIN_RESET)    // output low level

  
//WIFI ICON LED
#define LED_WIFI_ICON_ON()                HAL_GPIO_WritePin(LED_WIFI_GPIO_Port ,LED_WIFI_Pin,GPIO_PIN_RESET)
#define LED_WIFI_ICON_OFF()               HAL_GPIO_WritePin(LED_WIFI_GPIO_Port ,LED_WIFI_Pin,GPIO_PIN_SET)
//PTC ICON LED
#define LED_PTC_ICON_ON()                HAL_GPIO_WritePin(LED_PTC_GPIO_Port,LED_PTC_Pin,GPIO_PIN_RESET)
#define LED_PTC_ICON_OFF()               HAL_GPIO_WritePin(LED_PTC_GPIO_Port,LED_PTC_Pin,GPIO_PIN_SET)

//KILL ICON LED
#define LED_KILL_ICON_ON()                HAL_GPIO_WritePin(LED_KILL_GPIO_Port,LED_KILL_Pin,GPIO_PIN_RESET)
#define LED_KILL_ICON_OFF()               HAL_GPIO_WritePin(LED_KILL_GPIO_Port,LED_KILL_Pin,GPIO_PIN_SET)

//ULTRSONIC ICO LED
#define LED_RAT_ICON_ON()                HAL_GPIO_WritePin(LED_RAT_GPIO_Port,LED_RAT_Pin,GPIO_PIN_RESET)
#define LED_RAT_ICON_OFF()               HAL_GPIO_WritePin(LED_RAT_GPIO_Port,LED_RAT_Pin,GPIO_PIN_SET)







void LED_Mode_Key_On(void);
void LED_Mode_Key_Off(void);

void LED_Power_Key_On(void);
void LED_Power_Key_Off(void);




void Breath_Led(void);


#endif 


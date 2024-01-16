#ifndef __BSP_H
#define __BSP_H
#include "main.h"

#include "adc.h"
#include "dma.h"
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "bsp_buzzer.h"
#include "bsp_ultrasonic.h"
#include "bsp_delay.h"
#include "bsp_ptc.h"
#include "bsp_sensor.h"
#include "bsp_adc.h"
#include "bsp_fan.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_ctl.h"
#include "bsp_lcd.h"
#include "bsp_usart.h"

/* 定义 BSP 版本号 */
#define __STM33G030C8T6_BSP_VERSION		"0.1"

/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */


void bsp_Idle(void);





#endif 

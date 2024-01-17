#ifndef __BSP_H
#define __BSP_H
#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
#include "bsp_lcd_gui.h"


#include "bsp_wifi_fun.h"
#include "bsp_esp8266.h"
#include "bsp_publish.h"
#include "bsp_subscription.h"
#include "bsp_mqtt_iot.h"




/* ���� BSP �汾�� */
#define __STM33G030C8T6_BSP_VERSION		"0.1"

/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */


void bsp_Idle(void);

void Main_Process_Handler(void);




#endif 

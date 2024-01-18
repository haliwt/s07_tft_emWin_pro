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



typedef enum TIMING_T{

   works_time=0x01,
   timer_time,
   timing_success ,
   
}timing_t;




typedef struct{

  //key
   uint8_t gKey_value;
   uint8_t gPower_On;
   uint8_t long_key_flag;
   uint8_t run_process_step;
   uint8_t key_power_be_pressed_flag ;
  
   uint8_t ack_wifi_led;
   uint8_t ack_power_on_sig;
   uint8_t ack_power_off_sig;

   uint8_t gKey_command_tag;

   uint8_t decodeFlag;
   //time
   uint8_t set_timer_flag;
   uint8_t gTimer_mode_flag;
   uint8_t key_set_timer_flag;

 

   //temperature 
   uint8_t temperature_set_flag;

   //warning
 
	//wifi
	uint8_t wifi_led_fast_blink_flag;

	//usart 2 voice 
	uint8_t v_usart2_rx_numbers;
	uint8_t v_usart2_rx_flag;

  	uint8_t gTimer_pro_feed_dog;
	uint8_t gTimer_pro_temp ;
	uint8_t gTimer_pro_temp_delay ;
	uint8_t gTimer_wifi_connect_counter;
	uint8_t gTimer_key_timing;

	uint8_t gTimer_pro_fan;
	uint8_t gTimer_usart_error;
	uint8_t gTimer_pro_ms;
	uint8_t gTimer_pro_disp_timer ;
	uint8_t gTimer_pro_disp_ms;
	uint8_t gTime_pro_run_voice_time;
	

}PRO_T;


extern PRO_T pro_t;



void bsp_Idle(void);

void Key_Process_Handler(void);
void TFT_Process_Handler(void);





#endif 

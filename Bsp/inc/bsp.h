#ifndef __BSP_H
#define __BSP_H
#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "adc.h"
//#include "dma.h"
#include "iwdg.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
//bsp
#include "bsp_buzzer.h"
#include "bsp_ultrasonic.h"
#include "bsp_delay.h"
#include "bsp_ptc.h"
#include "bsp_plasma.h"
#include "bsp_sensor.h"
#include "bsp_adc.h"
#include "bsp_fan.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_ctl.h"
#include "bsp_lcd.h"
#include "bsp_usart.h"
#include "bsp_lcd_gui.h"
#include "bsp_wifi.h"
#include "bsp_image.h"
#include "bsp_tft_font.h"
#include "bsp_font.h"
#include "bsp_font_app.h"
#include "bsp_bsp.h"


//wifi
#include "bsp_wifi_fun.h"
#include "bsp_esp8266.h"
#include "bsp_publish.h"
#include "bsp_subscription.h"
#include "bsp_mqtt_iot.h"

//voice 
#include "bsp_voice.h"




/* ���� BSP �汾�� */
#define __STM33G030C8T6_BSP_VERSION		"0.1"

/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */



typedef enum TIMING_T{

   works_time_id,
   timer_time_id,
   timer_set_time_id,
   timing_success_id ,
   /// @brief ：select function "ptc,kill,rat"
   fun_selection
   
}timing_t;

typedef enum{
  mode_key_temp,
  mode_key_select ,
  mode_key_confirm,
  mode_key_timer_time

}mode_key_state;

typedef enum{

  pro_init,
  pro_disp_dht11_value,
  pro_run_continue_two_hours,
  pro_disp_works_time,
  pro_disp_and_set_temperature,
  pro_disp_wifi_led,
  pro_mode_key_fun,
  pro_wifi_init
  



}process_run_state;


typedef enum{

   power_off,
   power_on,



}state_power_enum;




typedef struct{

  //key
   uint8_t gKey_value;
   uint8_t gPower_On;
   uint8_t long_key_flag;
   uint8_t run_process_step;
   uint8_t key_power_be_pressed_flag ;
   uint8_t power_off_flag;

   //buzzer
   uint8_t buzzer_sound_flag;
  
   //time
   uint8_t mode_key_select_flag ;
  
   

   //wifi info
  
 
   //modke key
   uint8_t mode_key_pressed_flag;
   uint8_t key_input_model_timer_or_timing;
   uint8_t mode_key_confirm_flag;
   uint8_t mode_key_special_fun;
 
  

   //temperature 
     uint8_t set_temperature_value_flag;

   //warning
    uint8_t spi_error_flag;
   //error 
     uint8_t lcd_over_width_flag;
     uint8_t lcd_over_height_flag ;
	//wifi
	uint8_t wifi_led_fast_blink_flag;

	//usart 2 voice 
	uint8_t v_usart2_rx_numbers;
	uint8_t v_usart2_rx_flag;

  	//timer timing function
  	uint8_t gTimer_pro_feed_dog;
	
	uint8_t gTimer_pro_temp_delay ;
	
	

  //timing by interrupt
  uint8_t gTimer_wifi_connect_counter;

  uint8_t gTimer_pro_fan;
	uint8_t gTimer_usart_error;
 
	uint8_t gTime_pro_run_voice_time;
	
	uint8_t gTimer_pro_time_split_symbol;
	uint8_t gTimer_pro_wifi_led;
	uint8_t gTimer_pro_wifi_fast_led;
	//uint8_t gTimer_pro_long_key_timer_flag;
 
  uint8_t gTimer_pro_mode_key_timer;
  uint8_t gTimer_pro_set_tem_value_blink;
  uint8_t gTimer_pro_set_timer_time;
  uint8_t gTimer_pro_detect_key_ms ;
  uint8_t gTimer_pro_mode_key_adjust;
  uint8_t gTimer_pro_power_key_adjust;
  uint8_t gTimer_pro_disp_tempe_value;
  uint8_t gTimer_pro_display_timer_timing;
	

}PRO_T;


extern PRO_T pro_t;


void bsp_Init(void);

void bsp_Idle(void);

void Key_Process_Handler(uint8_t keyvalue);
void TFT_Process_Handler(void);



void ADD_Key_Fun(void);
void DEC_Key_Fun(void);
void Wifi_Fast_Led_Blink(void);

void Mode_Long_Key_Fun(void);;

void Power_On_Fun(void);
void Power_Off_Fun(void);


#endif 

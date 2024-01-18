#ifndef __BSP_CTL_H
#define __BSP_CTL_H
#include "main.h"


typedef enum{

   close,
   open
  
}hard_state;


typedef enum{

   good,
   error

}hard_error_state;




typedef struct _bsp_ctl{

    uint8_t wifi_flag;
	uint8_t mode_flag;
	uint8_t ptc_flag;
	uint8_t plasma_flag;
	uint8_t ultrasonic_flag;

	uint8_t ptc_warning;
	uint8_t fan_warning;

    uint8_t gTimer_prcoess_iwdg;
	uint8_t gTimer_process_display;

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
   uint8_t gSet_timer_hours ;
   uint8_t gSet_temperature_value;
   uint8_t gSet_timer_minutes ;
   uint8_t set_temp_has_been_flag;

   //command
   uint8_t rx_command_tag;

 

   //temperature and humidity
   uint8_t temperature_set_flag;
   uint8_t dht11_hum_value;
   uint8_t dht11_temp_value;
   uint8_t gSet_temperature_value_flag;

   //warning
 
	//wifi
	uint8_t wifi_led_fast_blink_flag;

	//usart 2 voice 
	uint8_t v_usart2_rx_numbers;
	uint8_t v_usart2_rx_flag;

 }bsp_ctl;

extern bsp_ctl gctl_t;


extern uint8_t (*wifi_state)(void);
extern uint8_t (*mode_state)(void);

extern uint8_t (*ptc_state)(void); //adjust of ptc is open or close
extern uint8_t (*plasma_state)(void); //adjust of plasma is open or close
extern uint8_t (*ultrasonic_state)(void); //adjust of ultrasoic is open or close


extern uint8_t (*dht11_humidity_value)(void);
extern uint8_t (*dht11_temp_value)(void);

extern uint8_t (*smartphone_set_timer_timing)(void);
extern uint8_t (*smartphone_set_temp_value)(void);




extern uint8_t (*ptc_error_state)(void);
extern uint8_t (*fan_error_state)(void);
//key of panel of ref



void bsp_ctl_init(void);
void Device_Action_Handler(void);


void Wifi_State_Handler(uint8_t(*wifi_handler)(void));
void Mode_State_Handler(uint8_t(*mode_handler)(void));

void Ptc_State_Handler( uint8_t (*ptc_handler)(void));
void  Plasma_State_Handler(uint8_t(*plasma_handler)(void));
void  Ultrasonic_state_Handler(uint8_t(*ultrasonic_handler)(void));

void Dht11_humidity_Value_Handler(uint8_t(*hum_handler)(void));
void Dht11_temp_value_Handler(uint8_t(*temp_handler)(void));



void  Ptc_Error_State_Handler(uint8_t(*ptc_error_handler)(void));
void  Fan_Error_state_Handler(uint8_t(*fan_error_handler)(void));




void Smartphone_Set_Timer_Handler(uint8_t(*set_timer_handler)(void));
void Smartphone_Set_Temp_Handler(uint8_t(*set_temp_value_handler)(void));



void  Ptc_error_state_Handler(uint8_t(*error_handler)(void));
void  Fan_error_state_Handler(uint8_t(*fan_error_handler)(void));




















#endif 

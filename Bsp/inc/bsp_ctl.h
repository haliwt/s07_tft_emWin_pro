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

typedef enum{

   ptc_fun=0x01,
   plasma_fun,
   rat_fun

}fun_name;




typedef struct _bsp_ctl{

    uint8_t wifi_flag;
	uint8_t mode_flag;
	uint8_t ptc_flag;
	uint8_t plasma_flag;
	uint8_t ultrasonic_flag;
   

	uint8_t ptc_warning;
	uint8_t fan_warning;
   
    //time
   uint8_t disp_works_hours;

   
   uint8_t set_temp_has_been_flag;
   
   uint8_t disp_works_minutes;
   int8_t gSet_timer_minutes ;
   int8_t gSet_timer_hours ;
   
   int8_t gSet_temperature_value;
   int8_t select_main_fun_numbers;

   //command
   uint8_t rx_command_tag;
   uint8_t dht11_hum_value;
   uint8_t dht11_temp_value;
   uint8_t gSet_temperature_value_flag;

   uint8_t gTimer_ctl_disp_second;
   uint8_t gTimer_ctl_set_timer_time_senconds;
   uint8_t gTimer_ctl_select_led;
   

}bsp_ctl;

extern bsp_ctl gctl_t;




extern uint8_t (*power_on_state)(void);



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

void Mode_Key_Select_Fun(void);
void Mode_Key_Confirm_Fun(void);





















#endif 

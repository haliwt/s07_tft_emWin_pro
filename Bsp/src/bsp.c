#include "bsp.h"

PRO_T pro_t;

uint8_t led_blink_times;
uint8_t update_step;
uint8_t fan_continuce_run_flag;


static void mode_key_fun_handler(void);
static void TFT_Pocess_Command_Handler(void);

static void Power_On_Fun(void);
static void Power_Off_Fun(void);


//static void ADD_Key_Fun(void);
//static void DEC_Key_Fun(void);





void bsp_Init(void);

uint16_t power_off_counter;

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/

void bsp_Init(void)
{

   pro_t.mode_key_confirm_flag=0xff;
  // Buzzer_Sound_Fun_Init();


}
/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	static uint8_t power_on_first;
	if(power_on_first ==0){
       power_on_first ++;
	   gctl_t.gTimer_ctl_disp_second=0;
	   TFT_BACKLIGHT_OFF();
	   Update_DHT11_Value();
	   TFT_Disp_Temp_Value(0,gctl_t.dht11_temp_value);
       TFT_Disp_Humidity_Value(gctl_t.dht11_hum_value);
       TFT_Display_Handler();

	}
	
	/* --- 喂狗 */
    if(pro_t.gTimer_pro_feed_dog > 3){ //16s
	pro_t.gTimer_pro_feed_dog = 0;	
	iwdg_feed();

    }

    TFT_Disp_Timer_Split_Symbol();
    Wifi_Fast_Led_Blink();
	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
	//TOUCH_CapScan();
}
/*
*********************************************************************************************************
*
*	函 数 名: void TFT_Process_Handler(void)
*	功能说明: TFT显示的内容		 
*	形    参: 无
*	返 回 值: 无
*
*********************************************************************************************************
*/
void TFT_Process_Handler(void)
{
	
   static uint8_t fan_continuce_flag;
	if(pro_t.buzzer_sound_flag ==1){
		pro_t.buzzer_sound_flag=0;
		Buzzer_KeySound();
	}
	
	

	switch(pro_t.gPower_On){
	
	case power_on:
		
	   
	    TFT_Pocess_Command_Handler();

		break;

	case power_off:
	if(pro_t.power_off_flag == 1){
		pro_t.power_off_flag =0;
	    wifi_t.power_off_step=0; 
	    fan_continuce_flag =1;
		pro_t.gTimer_pro_fan =0;
		TFT_BACKLIGHT_OFF();
		Power_Off_Fun();
		Device_NoAction_Power_Off();
		LED_Mode_Key_Off();
		
   	}
	if(wifi_link_net_state() ==1  && wifi_t.gTimer_main_pro_times > 50){
		wifi_t.gTimer_main_pro_times=0;	
		MqttData_Publish_PowerOff_Ref();
		
    }

	if(fan_continuce_flag ==1){

	    if(pro_t.gTimer_pro_fan <61){
            Fan_Run();        

		}
		else{
			fan_continuce_flag++;

            Fan_Stop();
		}
      

	}
    gctl_t.ptc_warning=0;
	gctl_t.fan_warning =0;
	wifi_t.repeat_login_tencent_cloud_init_ref=0;

	wifi_t.smartphone_app_power_on_flag=0; //手机定时关机和开机，设置参数的标志位
	
	Power_Off_Retain_Beijing_Time();
	
	Breath_Led();

  
	break;


	}
	
}
/******************************************************************************
	*
	*Function Name:void TFT_Pocess_Command_Handler(void)
	*Funcion: display of TFT lcd 
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************************/
void Key_Interrup_Handler(void)
{
     switch(pro_t.gKey_value){

	  case power_key_id:
	  	
        Buzzer_KeySound();
	    pro_t.gKey_value =0XFF;

	 break;

       case add_key_id:
		 	
		 	
			 DEC_Key_Fun();

			  pro_t.gKey_value =0XFF;

		break;

		case dec_key_id:

			ADD_Key_Fun();

			 pro_t.gKey_value =0XFF;


		break;


	 }

	 mode_key_fun_handler();

   
}
/******************************************************************************
	*
	*Function Name:static void Key_Speical_Power_Fun_Handler(void)
	*Funcion: speical of power key function
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************************/
void Key_Speical_Power_Fun_Handler(void)
{
	//be pressed long time key of function that link tencent cloud funtion 

	 if(ptc_error_state()==0 && fan_error_state()==0){
	 if(pro_t.key_power_be_pressed_flag==1){
         if(POWER_KEY_VALUE() ==KEY_DOWN && pro_t.gTimer_pro_power_key_adjust > 2 &&  pro_t.gPower_On == power_on){
            pro_t.key_power_be_pressed_flag =0;
			pro_t.gTimer_pro_wifi_led =0;
            pro_t.wifi_led_fast_blink_flag=1;
			
			//WIFI CONNCETOR process
			wifi_t.link_tencent_step_counter=0;
			wifi_t.esp8266_login_cloud_success =0;
			wifi_t.runCommand_order_lable=wifi_link_tencent_cloud;
			wifi_t.wifi_config_net_lable= wifi_set_restor;
			wifi_t.gTimer_login_tencent_times=0;
			wifi_t.gTimer_linking_tencent_duration=0; //166s -2分7秒
			buzzer_sound();
			
			 
        }

	 }
	 }
	//sort time key of fun
		if(POWER_KEY_VALUE() ==KEY_UP && pro_t.key_power_be_pressed_flag ==1){

            pro_t.key_power_be_pressed_flag=0;
            if( pro_t.gPower_On == power_off){
				
			pro_t.gPower_On = power_on;   
            pro_t.long_key_flag =0;
            pro_t.run_process_step=0;
		    pro_t.gKey_value = power_key_id;

		
			
		  }
		  else{
			 //pro_t.gKey_value = power_key_id;
			 buzzer_sound();
			 pro_t.power_off_flag=1;
			
	        pro_t.long_key_flag =0;
			 
			pro_t.gPower_On = power_off;   
			pro_t.run_process_step=0xff;
			  
			 }
		  }
    
}
/******************************************************************************
	*
	*Function Name:static void Key_Speical_Mode_Fun_Handler(void)
	*Funcion: speical of mode key fun
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************************/
void Key_Speical_Mode_Fun_Handler(void)
{
 //modke _key_long_time
	if(pro_t.mode_key_pressed_flag ==1){

		//mode key be pressed long times
		if(MODE_KEY_VALUE() ==KEY_DOWN && pro_t.gTimer_pro_mode_key_adjust > 2){
			
			pro_t.mode_key_pressed_flag =0;
            Buzzer_KeySound();
			pro_t.gTimer_pro_mode_key_timer = 0; 

			pro_t.mode_key_select_flag =0;
			Mode_Long_Key_Fun();

		   
		}
       //
       if(MODE_KEY_VALUE() ==KEY_UP && pro_t.mode_key_pressed_flag ==1){
		pro_t.mode_key_pressed_flag =0;
	   
		
		pro_t.mode_key_confirm_flag = mode_key_select;
	    pro_t.mode_key_select_flag =1;
		gctl_t.select_main_fun_numbers++; // 0,1,2
		if(gctl_t.select_main_fun_numbers > 3){
		  gctl_t.select_main_fun_numbers = 1;
		}
		
        
		pro_t.buzzer_sound_flag =1;

		pro_t.gTimer_pro_mode_key_timer = 0; //counter starts after 4 seconds ,cancel this function
		gctl_t.gTimer_ctl_select_led =0;
	   }
		
		
	}
}
/******************************************************************************
	*
	*Function Name:static void mode_key_fun_handler(void)
	*Funcion: speical of mode key fun
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************************/
static void mode_key_fun_handler(void)
{

  switch(pro_t.mode_key_confirm_flag){


             case mode_key_select:

		     if(pro_t.gTimer_pro_mode_key_timer < 4){ //exit of rule

				Mode_Key_Select_Fun();
				
             }
			 else{
                
                pro_t.mode_key_confirm_flag = 0xff; //
                pro_t.mode_key_select_flag =0;
			    gctl_t.select_main_fun_numbers--; //return back the first confirm item 
				if(gctl_t.select_main_fun_numbers == 0){
					gctl_t.select_main_fun_numbers = 5;
				}
				
                Device_Action_Led_OnOff_Handler();
			 }


		   break;


		   case mode_key_confirm: //as "+" and "-" key  confirm ation
			    Device_Action_Led_OnOff_Handler();
                Mode_Key_Confirm_Fun();
				pro_t.mode_key_confirm_flag = 0xff;

			break;

	    }
}
/******************************************************************************
	*
	*Function Name:void TFT_Pocess_Command_Handler(void)
	*Funcion: display of TFT lcd 
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************************/
static void TFT_Pocess_Command_Handler(void)
{
   
	if(power_on_state() == power_on){
  
    switch(pro_t.run_process_step){


	 case 0:
	 	
		pro_t.gKey_value =0XFF;
	    //TFT_Display_Handler();
		Power_On_Fun();
	    Fan_Run();
		

		TFT_BACKLIGHT_ON();
		
		pro_t.run_process_step=pro_disp_dht11_value;
		
	 break;

	 case pro_disp_dht11_value: //1 //display works time + "temperature value " + "humidity value"

	   Wifi_Fast_Led_Blink();
	

	   if(pro_t.gTimer_pro_display_dht11_value > 28 &&  pro_t.wifi_led_fast_blink_flag==0){
	   	   pro_t.gTimer_pro_display_dht11_value=0;
         
		    Update_DHT11_Value();
		
            if(pro_t.mode_key_confirm_flag != mode_key_temp){
			   TFT_Disp_Temp_Value(0,gctl_t.dht11_temp_value);
            }
			TFT_Disp_Humidity_Value(gctl_t.dht11_hum_value);

	   }
	   
	   pro_t.run_process_step=pro_run_main_fun;
	   
	case pro_run_main_fun: //02
	
   
	  Wifi_Fast_Led_Blink();

	   Fan_Pro_Handler();
	   pro_t.run_process_step=pro_disp_works_time;
	 break;

	 case pro_disp_works_time: //display works times and timer timing .

		Wifi_Fast_Led_Blink();
	
	
	    TimeTimer_Pro_Handler();
			

		pro_t.run_process_step=pro_set_temperature;


    case pro_set_temperature:


	   Temperature_Ptc_Pro_Handler();
		
    
      pro_t.run_process_step=pro_disp_wifi_led;

	break;

	case pro_disp_wifi_led: //4
	
		  if(wifi_link_net_state() ==0){
		  
			if(pro_t.mode_key_select_flag ==1){

				LED_WIFI_ICON_OFF();

            }
            else{
             switch(pro_t.wifi_led_fast_blink_flag){

			 case 1:
				Wifi_Fast_Led_Blink();

			 	pro_t.run_process_step=1;
             break;

             case 0:
				if(pro_t.gTimer_pro_wifi_led > 1 && pro_t.gTimer_pro_wifi_led < 3){
					
					LED_WIFI_ICON_ON();
				}
				else if(pro_t.gTimer_pro_wifi_led > 2){

					pro_t.gTimer_pro_wifi_led=0;
					LED_WIFI_ICON_OFF();
				}
				
			 break;

             }

            }
			

		}
		else{

		  LED_WIFI_ICON_ON();

		}
		  
	  pro_t.run_process_step=pro_wifi_init;
	 break; 
		  
      // handler of wifi 
	  case pro_wifi_init: //7
	 

      Wifi_Pro_Runing_Init();
	  
	  pro_t.run_process_step=pro_disp_dht11_value;

	  break;


    default:
    break;
   	}
   }
  
   
}
/************************************************************************
	*
	*Function Name: static void Power_On_Fun(void)
	*Function : power on
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void Power_On_Fun(void)
{
  //led on 
  LED_Mode_Key_On();
  LED_Power_Key_On();
  Power_On_Led_Init();
  //smart phone control power on 
  if(wifi_t.smartphone_app_power_on_flag==0){
	  gctl_t.ptc_flag = 1;
      gctl_t.plasma_flag = 1;
	  gctl_t.ultrasonic_flag =1;
  }
   
   gctl_t.gSet_temperature_value =40;

 
   //timer timing
   gctl_t.mode_flag = works_time;
   gctl_t.timer_time_define_flag = 0;
    pro_t.timer_mode_flag=works_time;
	 gctl_t.gSet_timer_hours =0;
	 gctl_t.gSet_timer_minutes =0;

	//mode key long times 
	  pro_t.mode_key_confirm_flag=0xff;
	 gctl_t.mode_key_long_time_flag=0;
	 pro_t.long_key_flag =0;
    
     //works time
	gctl_t.gTimer_ctl_total_continue_time =0; //works total is two hours recoder.
	gctl_t.gTimer_ctl_disp_second=0; //works time seconds 
    pro_t.gTimer_pro_display_dht11_value = 30; //powe on display sensoe dht11 of value .
	


}
     


static void Power_Off_Fun(void)
{
	LED_Mode_Key_Off();
	LED_Power_Key_Off();

	Power_Off_Led();
   gctl_t.mode_flag = 0;
   pro_t.gPower_On = power_off;
   pro_t.mode_key_confirm_flag=0xff;
   gctl_t.plasma_flag = 0;
   gctl_t.ultrasonic_flag =0;
   gctl_t.ptc_flag = 0;
   //timer timing flag
     pro_t.timer_mode_flag=works_time;
	pro_t.timer_mode_flag=0;
	pro_t.wifi_led_fast_blink_flag=0;
	gctl_t.gSet_timer_hours =0;

	gctl_t.ptc_warning = 0;
	gctl_t.fan_warning=0;
	//clear set timer timing value and flag 
}
void power_off_fan_run(void)
{
	
    LED_Mode_Key_Off();
	Breath_Led();
	

}


/************************************************************************
	*
	*Function Name: static void Mode_Long_Key_Fun(void) 
	*Function : set timer timing is enable 
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
void Mode_Long_Key_Fun(void)  //MODE_KEY_LONG_TIME_KEY://case model_long_key:
{
	  if(power_on_state() ==power_on){
	   if(gctl_t.fan_warning ==0 && ptc_error_state() ==0){
	  	  pro_t.mode_key_confirm_flag = mode_key_timer_time;
		  pro_t.timer_mode_flag=timer_set_time; //set timer mode enable
		  gctl_t.timer_timing_words_changed_flag ++;
		  gctl_t.timing_words_changed_flag++;
		  pro_t.gTimer_pro_mode_key_timer=0;


	     TFT_Disp_Set_TimerTime_Init();

	   }
	  	 
      }
}
/************************************************************************
	*
	*Function Name: static void Power_On_Fun(void)
	*Function : power on
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
void ADD_Key_Fun(void)
{
 
 if(power_on_state()==power_on){

	if(gctl_t.ptc_warning ==0 && ptc_error_state() ==0){

		//Buzzer_KeySound();
		//pro_t.buzzer_sound_flag = 1;

		switch(pro_t.mode_key_confirm_flag){

		case 0xff:

			pro_t.mode_key_confirm_flag=mode_key_temp;

		case mode_key_temp: //set temperature value add number
			//pro_t.buzzer_sound_flag = 1;
			Buzzer_KeySound();
			gctl_t.gSet_temperature_value ++;
			if( gctl_t.gSet_temperature_value < 20)gctl_t.gSet_temperature_value=20;
			
            if(gctl_t.gSet_temperature_value > 40) gctl_t.gSet_temperature_value= 20;

             pro_t.gTimer_pro_set_tem_value_blink =0;
			 gctl_t.gSet_temperature_value_item = set_temp_value_item;

			TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);	
		break;

		case mode_key_timer_time:
           pro_t.buzzer_sound_flag = 1;
			gctl_t.mode_key_long_time_flag++;
			gctl_t.gSet_timer_minutes=0;
			gctl_t.gSet_timer_hours ++ ;//disp_t.disp_timer_time_hours++ ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes + 60;
			if(gctl_t.gSet_timer_hours  > 24){ //if(pro_t.dispTime_minutes > 59){

			gctl_t.gSet_timer_hours =0;//pro_t.dispTime_hours =0;


			}
			pro_t.gTimer_pro_mode_key_timer = 0; //counter starts after 4 seconds ,cancel this function
	
			TFT_Disp_Set_TimerTime(0);

		break;

		case mode_key_select:
			pro_t.buzzer_sound_flag = 1;
			pro_t.mode_key_confirm_flag = mode_key_confirm;


		break;


		}	
		}
	}

}
/************************************************************************
	*
	*Function Name: static void DEC_Key_Fun(void)
	*Function : KEY OF decrease
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
void DEC_Key_Fun(void)
{

	if(power_on_state() ==power_on){
	   	if(gctl_t.ptc_warning ==0 && ptc_error_state() ==0){
	   	
	     switch(pro_t.mode_key_confirm_flag){

		   case 0xff:

		 	pro_t.mode_key_confirm_flag= mode_key_temp;

		   case mode_key_temp:  //default tempearture value 
	        // pro_t.buzzer_sound_flag = 1;
	        Buzzer_KeySound();
			 gctl_t.gSet_temperature_value--;
			if( gctl_t.gSet_temperature_value<20)  gctl_t.gSet_temperature_value=40;
	        if( gctl_t.gSet_temperature_value >40) gctl_t.gSet_temperature_value=40;
             pro_t.gTimer_pro_mode_key_timer = 0;
			 pro_t.gTimer_pro_set_tem_value_blink =0;
			 gctl_t.gSet_temperature_value_item = set_temp_value_item;

			TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);
			break;

			case mode_key_timer_time: //timer timing set "decrease -down"
			   
			    pro_t.buzzer_sound_flag = 1;
	            gctl_t.mode_key_long_time_flag++;
				gctl_t.gSet_timer_minutes=0;
				gctl_t.gSet_timer_hours --;//disp_t.disp_timer_time_hours -- ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes - 1;
				if(gctl_t.gSet_timer_hours  < 0){//if(pro_t.dispTime_minutes < 0){

				    gctl_t.gSet_timer_hours  =24;//pro_t.dispTime_hours --;
					
					
				}
			 pro_t.gTimer_pro_mode_key_timer = 0;
		
			 	
			TFT_Disp_Set_TimerTime(0);
			break;

			 case mode_key_select:
			 	pro_t.buzzer_sound_flag = 1;
			
				pro_t.mode_key_confirm_flag = mode_key_confirm;
			break;


	    	}
	   	  }
		}
}


/**********************************************************************************************************
    **
    *Function Name:void Power_Key_Detected(void)
    *Function : 
    *Input Ref:lightNum--LED ,filterNum -filter number, unionNum - smart menu number
    *Return Ref:NO
    *
*********************************************************************************************************/
void Wifi_Fast_Led_Blink(void)
{
   if(pro_t.wifi_led_fast_blink_flag==1 && wifi_link_net_state()==0){
wifi_led: if(pro_t.gTimer_pro_wifi_led < 166){//2'46s

	if( pro_t.gTimer_pro_wifi_fast_led < 80 ){ //50ms

	         LED_WIFI_ICON_ON();
	}
	else if(pro_t.gTimer_pro_wifi_fast_led > 79 && pro_t.gTimer_pro_wifi_fast_led< 161){

        
		LED_WIFI_ICON_OFF();
	}
	else{

		pro_t.gTimer_pro_wifi_fast_led=0;
		goto wifi_led;

		
	  }
   }
   else{
	
	 pro_t.wifi_led_fast_blink_flag=0;
   }

  }
}
	

/**********************************************************************************************************
    **
    *Function Name:TFT_Donnot_Set_Timer_Time();
    *Function : 记录设置的定时时间，
    *Input Ref:
    *Return Ref:NO
    *
*********************************************************************************************************/



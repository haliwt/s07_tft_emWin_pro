#include "bsp.h"

PRO_T pro_t;

uint8_t led_blink_times;
uint8_t update_step;



static void Key_Speical_Power_Fun_Handler(void);
static void Key_Speical_Mode_Fun_Handler(void);
static void Ptc_Temperature_Compare_Value(void);


static void mode_key_fun_handler(void);



static void TFT_Pocess_Command_Handler(void);

static void Power_On_Fun(void);
static void Power_Off_Fun(void);



static void TFT_Donnot_Set_Timer_Time(void);
//static void ADD_Key_Fun(void);
//static void DEC_Key_Fun(void);
static void Key_Interrup_Handler(void);

static uint16_t mode_key_long_flag;


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
	
    
	if(pro_t.buzzer_sound_flag ==1){
		pro_t.buzzer_sound_flag=0;
		Buzzer_KeySound();
	}
	
	Key_Speical_Power_Fun_Handler();

	switch(pro_t.gPower_On){
	
	case power_on:
		
	    Key_Speical_Mode_Fun_Handler();
    	Key_Interrup_Handler();
	    TFT_Pocess_Command_Handler();

		break;

	case power_off:

	
   	
   	if(pro_t.power_off_flag == 1){
		pro_t.power_off_flag =0;
	    wifi_t.power_off_step=0; 
		TFT_BACKLIGHT_OFF();
		Power_Off_Fun();
   	}
	if(wifi_link_net_state() ==1  && wifi_t.gTimer_main_pro_times > 50){
		wifi_t.gTimer_main_pro_times=0;	
		MqttData_Publish_PowerOff_Ref();
		
    }
      
	wifi_t.repeat_login_tencent_cloud_init_ref=0;

	wifi_t.smartphone_app_power_on_flag=0; //手机定时关机和开机，设置参数的标志位
	LED_Mode_Key_Off();
	TFT_DonnotDisp_Works_Time();
	
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
static void Key_Interrup_Handler(void)
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
static void Key_Speical_Power_Fun_Handler(void)
{
	//be pressed long time key of function that link tencent cloud funtion 
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
			 TFT_BACKLIGHT_OFF();
		     Power_Off_Fun();
			
             wifi_t.power_off_step=0; 
	         pro_t.long_key_flag =0;
			 
			 pro_t.gPower_On = power_off;   
	    
			   
			pro_t.run_process_step=0xff;
			  
			 }
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
static void Key_Speical_Mode_Fun_Handler(void)
{
 //modke _key_long_time
	if(pro_t.mode_key_pressed_flag ==1){

		//mode key be pressed long times
		if(MODE_KEY_VALUE() ==KEY_DOWN && pro_t.gTimer_pro_mode_key_adjust > 2){
			
			pro_t.mode_key_pressed_flag =0;
            Buzzer_KeySound();
			pro_t.gTimer_pro_mode_key_timer = 0; 
			pro_t.gTimer_pro_set_timer_time=0;
			pro_t.mode_key_select_flag =0;
			Mode_Long_Key_Fun();

		   
		}
       //
       if(MODE_KEY_VALUE() ==KEY_UP && pro_t.mode_key_pressed_flag ==1){
		pro_t.mode_key_pressed_flag =0;
	   
		
		pro_t.mode_key_confirm_flag = mode_key_select;
	    pro_t.mode_key_select_flag =1;
		gctl_t.select_main_fun_numbers++; // 0,1,2
		if(gctl_t.select_main_fun_numbers > 2){
		  gctl_t.select_main_fun_numbers = 0;
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

      case mode_key_temp:

          if(pro_t.gTimer_pro_mode_key_timer < 4){
		  	TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);
          }
		  else{

                  if(pro_t.gTimer_pro_set_tem_value_blink < 5){

					 TFT_Disp_Temp_Value(1,gctl_t.gSet_temperature_value);  //1-don't display temp value , 0-display numbers 


				  }
				  else{

					TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);  //0-display numbers 
                    pro_t.gTimer_pro_set_tem_value_blink=0;
                    led_blink_times++;
				  }

                  if(led_blink_times ==1){
				  	led_blink_times=0;
					  pro_t.mode_key_confirm_flag = 0xff;
					  pro_t.gTimer_pro_tft =30; //at once display dht11 sensor temperature value 
					  pro_t.set_temperature_value_flag= 1;
					  

                  }

			}
			   
			
			break;


			case mode_key_select:

		     if(pro_t.gTimer_pro_mode_key_timer < 4){ //exit of rule

				Mode_Key_Select_Fun();
				
             }
			 else{
                
                pro_t.mode_key_confirm_flag = 0xff; //
                pro_t.mode_key_select_flag =0;
				
                Device_Action_Led_OnOff_Handler();
			 }


		   break;


		   case mode_key_confirm:
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
   //key input run function
	static uint8_t timer_blink_times;
   // static uint8_t power_times;
  

   if(power_on_state() == power_on){
  
    switch(pro_t.run_process_step){


	 case 0:
	 	
		pro_t.gKey_value =0XFF;
	    
		Power_On_Fun();
	    
        gctl_t.timer_time_define_flag =0;
		gctl_t.gTimer_ctl_disp_second=0;
		pro_t.long_key_flag =0;

        pro_t.gPower_On= power_on;
		
   

		pro_t.run_process_step=1;

		TFT_BACKLIGHT_ON();
		
		pro_t.long_key_flag =0;
		TFT_Display_WorksTime();
		
	  
		

	 break;

	 case pro_disp_dht11_value: //1 //display works time + "temperature value " + "humidity value"

	   Wifi_Fast_Led_Blink();

	   if(pro_t.gTimer_pro_tft > 9 &&  pro_t.wifi_led_fast_blink_flag==0){
	   	   pro_t.gTimer_pro_tft=0;
         
		    Update_DHT11_Value();
		
            if(pro_t.mode_key_confirm_flag != mode_key_temp){
			   TFT_Disp_Temp_Value(0,gctl_t.dht11_temp_value);
            }
			TFT_Disp_Humidity_Value(gctl_t.dht11_hum_value);

	   }
	   
	   pro_t.run_process_step=pro_run_main_fun;
	   
	case pro_run_main_fun: //02
      pro_t.run_process_step=0xf2;
	  Wifi_Fast_Led_Blink();
		
	  if(pro_t.gTimer_pro_key_select_fun >1 && pro_t.set_moke_key_select_fun ==1){ //8s
			 pro_t.gTimer_pro_key_select_fun =0;
			 pro_t.set_moke_key_select_fun =0;
			 Wifi_Fast_Led_Blink();

		     Device_Action_Handler();
	    }
	    pro_t.run_process_step=pro_disp_works_time;
	 break;

	 case pro_disp_works_time: //display works times and timer timing .
	 	
		Wifi_Fast_Led_Blink();
		switch(pro_t.timer_mode_flag){

			case timer_time: //timer_time 
				if(gctl_t.gTimer_ctl_set_timer_time_senconds >59){
					gctl_t.gTimer_ctl_set_timer_time_senconds =0;

                    gctl_t.gSet_timer_minutes --;

					if(gctl_t.gSet_timer_minutes <0){
					   gctl_t.gSet_timer_minutes =59;
                       gctl_t.gSet_timer_hours --;
					   

					}
					if(gctl_t.gSet_timer_hours < 0){

						pro_t.gPower_On = power_off;

					}
				}

				TFT_Disp_Set_TimerTime(0);
				TFT_DonnotDisp_Works_Time();
			break;

			case works_time:

			if(gctl_t.gTimer_ctl_disp_second > 59){
				TFT_Display_WorksTime();
			}

			TFT_Donnot_Set_Timer_Time();
    
			break;

			case timer_set_time:

			if(pro_t.gTimer_pro_mode_key_timer > 3){
                    
                    if(pro_t.gTimer_pro_set_timer_time < 6){
					     TFT_Disp_Set_TimerTime(1);//1-don't display numbers 0-display numbers
                    }
					else {

						TFT_Disp_Set_TimerTime(0); //1-don't display numbers, 0-display numbers //turn off disp timer time
                        timer_blink_times++;
					    
					}
					
			        if(timer_blink_times > 0 && mode_key_long_flag >0){
						timer_blink_times =0;
						if(gctl_t.gSet_timer_hours >0 ){

							pro_t.timer_mode_flag = timer_time;
							pro_t.mode_key_confirm_flag =0xff;
							gctl_t.gTimer_ctl_set_timer_time_senconds =0;
							gctl_t.timer_time_define_flag = 1;
							gctl_t.gSet_timer_minutes =0;
							mode_key_long_flag=0;
							
							

						}
						else{
							mode_key_long_flag=0;
							gctl_t.timer_time_define_flag = 0;
							pro_t.mode_key_confirm_flag =0xff;
							pro_t.timer_mode_flag = works_time;
						    TFT_Display_WorksTime();
						  

						}
					}

					if(timer_blink_times > 0 && mode_key_long_flag ==0){ //add key and dec key don't be pressed key
						timer_blink_times =0;
						if(gctl_t.timer_time_define_flag ==1){
							pro_t.timer_mode_flag = timer_time;
							pro_t.mode_key_confirm_flag =0xff;
						   

						}
						else{
						pro_t.mode_key_confirm_flag =0xff;
						pro_t.timer_mode_flag = works_time;
						TFT_Display_WorksTime();
						}
					}

			}
				
			TFT_DonnotDisp_Works_Time();
					

			break;
		}
		pro_t.run_process_step=pro_set_temperature;


    case pro_set_temperature:
        Ptc_Temperature_Compare_Value();

	
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

       if(wifi_link_net_state() ==1 && wifi_t.smartphone_app_power_on_flag==0){
	   if(wifi_link_net_state() ==1 && wifi_t.repeat_login_tencent_cloud_init_ref ==0 ){
	   	  wifi_t.repeat_login_tencent_cloud_init_ref ++;
		  update_step =1;
	      MqttData_Publish_Init();
	      wifi_t.gTimer_main_pro_times=0;

	   }
 
	     
	   if(wifi_link_net_state() ==1 && update_step==1 &&  wifi_t.gTimer_main_pro_times > 0){
	   	 
	   	  update_step ++ ;

		   MqttData_Publish_SetOpen(0x01);
	       wifi_t.gTimer_main_pro_times=0;
	   
	   }

	   if(wifi_link_net_state() ==1 && update_step==2 &&  wifi_t.gTimer_main_pro_times > 0){
	  	  update_step++;
    	  Publish_Data_ToTencent_Initial_Data();
	       wifi_t.gTimer_main_pro_times=0;
        
       }

       if(wifi_link_net_state() ==1 && update_step==3 &&  wifi_t.gTimer_main_pro_times > 0){
	  	  update_step++;
	  	
    	  Subscriber_Data_FromCloud_Handler();

		    wifi_t.gTimer_main_pro_times=0;
	     
        
       }

	   
      if(wifi_link_net_state() ==1 && update_step==4 &&  wifi_t.gTimer_main_pro_times > 0){
	  	  update_step++;
	       pro_t.run_process_step=pro_disp_dht11_value;
	        wifi_t.runCommand_order_lable = wifi_publish_update_tencent_cloud_data;
      }

	  if( update_step==5)  pro_t.run_process_step=pro_disp_dht11_value;
       }
	   else{

		   pro_t.run_process_step=pro_disp_dht11_value;


	   }

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
   
  LED_Mode_Key_On();
  LED_Power_Key_On();
  Power_On_Led_Init();

  if(wifi_t.smartphone_app_power_on_flag==0){
	  gctl_t.ptc_flag = 1;
      gctl_t.plasma_flag = 1;
	  gctl_t.ultrasonic_flag =1;
	  

  }
   
   gctl_t.gSet_temperature_value =40;

   pro_t.mode_key_confirm_flag=0xff;
   gctl_t.mode_flag = works_time;
   gctl_t.timer_time_define_flag = 0;
   //timer timing
     pro_t.timer_mode_flag=works_time;
	 gctl_t.gSet_timer_hours =0;
	 gctl_t.gSet_timer_minutes =0;
	 mode_key_long_flag=0;



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
	   if(gctl_t.fan_warning ==0 && gctl_t.ptc_warning ==0){
	  	  pro_t.mode_key_confirm_flag = mode_key_timer_time;
		  pro_t.timer_mode_flag=timer_set_time; //set timer mode enable
		  gctl_t.timer_timing_words_changed_flag ++;
		  gctl_t.timing_words_changed_flag++;
		  pro_t.gTimer_pro_mode_key_timer=0;
		  pro_t.gTimer_pro_set_timer_time=0;

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

	if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){

		//Buzzer_KeySound();
		//pro_t.buzzer_sound_flag = 1;

		switch(pro_t.mode_key_confirm_flag){

		case 0xff:

			pro_t.mode_key_confirm_flag=mode_key_temp;

		case mode_key_temp: //set temperature value add number
			pro_t.buzzer_sound_flag = 1;
			gctl_t.gSet_temperature_value ++;
			if( gctl_t.gSet_temperature_value < 20)gctl_t.gSet_temperature_value=20;
			
            if(gctl_t.gSet_temperature_value > 40) gctl_t.gSet_temperature_value= 20;


			pro_t.gTimer_pro_mode_key_timer = 0; //counter starts after 4 seconds ,cancel this function
			pro_t.gTimer_pro_set_tem_value_blink=0;

			//TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);	
		break;

		case mode_key_timer_time:
           pro_t.buzzer_sound_flag = 1;
			mode_key_long_flag++;
			gctl_t.gSet_timer_minutes=0;
			gctl_t.gSet_timer_hours ++ ;//disp_t.disp_timer_time_hours++ ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes + 60;
			if(gctl_t.gSet_timer_hours  > 23){ //if(pro_t.dispTime_minutes > 59){

			gctl_t.gSet_timer_hours =0;//pro_t.dispTime_hours =0;


			}
			pro_t.gTimer_pro_mode_key_timer = 0; //counter starts after 4 seconds ,cancel this function
			pro_t.gTimer_pro_set_timer_time=0; //TFT set the timer time blinking
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
	   	if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){
	   	
	     switch(pro_t.mode_key_confirm_flag){

		   case 0xff:

		 	pro_t.mode_key_confirm_flag= mode_key_temp;

		   case mode_key_temp:  //default tempearture value 
	         pro_t.buzzer_sound_flag = 1;
			 gctl_t.gSet_temperature_value--;
			if( gctl_t.gSet_temperature_value<20)  gctl_t.gSet_temperature_value=40;
	        if( gctl_t.gSet_temperature_value >40) gctl_t.gSet_temperature_value=40;
             pro_t.gTimer_pro_mode_key_timer = 0;
			 pro_t.gTimer_pro_set_tem_value_blink =0;

			//TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);
			break;

			case mode_key_timer_time: //timer timing set "decrease -down"
			    pro_t.buzzer_sound_flag = 1;
	            mode_key_long_flag++;
				gctl_t.gSet_timer_minutes=0;
				gctl_t.gSet_timer_hours --;//disp_t.disp_timer_time_hours -- ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes - 1;
				if(gctl_t.gSet_timer_hours  < 0){//if(pro_t.dispTime_minutes < 0){

				    gctl_t.gSet_timer_hours  =23;//pro_t.dispTime_hours --;
					
					
				}
			 pro_t.gTimer_pro_mode_key_timer = 0;
			 pro_t.gTimer_pro_set_timer_time=0;
			 	
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
    *Function Name:static void Ptc_Temperature_Compare_Value(void)
    *Function : 
    *Input Ref:lightNum--LED ,filterNum -filter number, unionNum - smart menu number
    *Return Ref:NO
    *
*********************************************************************************************************/
static void Ptc_Temperature_Compare_Value(void)
{
   
      switch(gctl_t.gSet_temperature_value_flag){

      case 1:
	  
	    if(pro_t.gTimer_pro_temp_delay> 61 && gctl_t.ptc_warning==0){
               pro_t.gTimer_pro_temp_delay =0;
		 
		  
		  if(set_temp_value() <= dht11_temp_value()|| dht11_temp_value() >40){//envirment temperature
	  
				gctl_t.ptc_flag = 0 ;//run_t.gDry = 0;
			    Ptc_Off();
		        LED_PTC_ICON_OFF();
                 

            }
			else if((set_temp_value() -2) > dht11_temp_value()){
	  
		         gctl_t.ptc_flag = 1;//run_t.gDry = 1;
		         Ptc_On();
			     LED_PTC_ICON_ON();
			    
            }
				 
	   }
	
       break;


       case 0:
           
           if(pro_t.gTimer_pro_temp_delay > 66  && gctl_t.ptc_warning==0 ){ //WT.EDIT 2023.07.27 over 40 degree shut of ptc off
                pro_t.gTimer_pro_temp_delay=0;

             if(dht11_temp_value() >40){//envirment temperature
               
                gctl_t.ptc_flag = 0 ;//run_t.gDry = 0;
			    Ptc_Off();
		        LED_PTC_ICON_OFF();
              
                
           
               }
               else if(dht11_temp_value() <38){
               
				 gctl_t.ptc_flag = 1;//run_t.gDry = 1;
		         Ptc_On();
			     LED_PTC_ICON_ON();
                
                
                 
                }

            }
          

        break;
        
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
static void TFT_Donnot_Set_Timer_Time(void)
{
    if(gctl_t.timer_time_define_flag == 1){

	if(gctl_t.gTimer_ctl_set_timer_time_senconds >59){
		gctl_t.gTimer_ctl_set_timer_time_senconds =0;

		gctl_t.gSet_timer_minutes --;

		if(gctl_t.gSet_timer_minutes <0){
		gctl_t.gSet_timer_minutes =59;
		gctl_t.gSet_timer_hours --;


		}
		if(gctl_t.gSet_timer_hours < 0){

			pro_t.gPower_On = power_off;

		}

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



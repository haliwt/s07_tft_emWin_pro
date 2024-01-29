#include "bsp.h"

PRO_T pro_t;

uint8_t led_blink_times;

static void Ptc_Temperature_Compare_Value(void);
static void Power_Key_Detected(void);
static void Mode_Key_Detected(void);
static void ADD_Key_Detected(void);
static void DEC_Key_Detected(void);



static void Mode_Long_Key_Fun(void);

static void TFT_Pocess_Command_Handler(void);

static void Power_On_Fun(void);
static void Power_Off_Fun(void);

static void Wifi_Fast_Led_Blink(void);

void bsp_Init(void);

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
*	函 数 名: void Key_Process_Handler(void)
*	功能说明: 处理按键输入和输出
*			 
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void Key_Process_Handler(void)
{
	 Power_Key_Detected();
	 if(pro_t.key_power_be_pressed_flag ==0){
			Mode_Key_Detected();
			ADD_Key_Detected();
			DEC_Key_Detected();
		
      }

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
	TFT_Pocess_Command_Handler();
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

   static uint8_t power_been_flag,timer_blink_times;
  
   if(power_on_state() == power_on){
  
    switch(pro_t.run_process_step){


	 case 0:
		Power_On_Fun();
		Buzzer_KeySound();

		pro_t.long_key_flag =0;
		pro_t.key_power_be_pressed_flag =0;
 


		pro_t.run_process_step=1;

		TFT_BACKLIGHT_ON();
		power_been_flag=1;
		pro_t.long_key_flag =0;
		pro_t.key_power_be_pressed_flag =0;

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
	   
	case pro_run_main_fun: //2
       pro_t.run_process_step=0xf2;
	 Wifi_Fast_Led_Blink();
		
	  if(pro_t.gTimer_pro_ms >4){ 
			 pro_t.gTimer_pro_ms =0;
			 pro_t.run_process_step=0xff;
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

			break;

			case works_time:

			if(gctl_t.gTimer_ctl_disp_second > 59){
				TFT_Display_WorksTime();
			}	

			break;

			case timer_set_time:

			    if(pro_t.gTimer_pro_mode_key_timer > 3 ){
                    
                    if(pro_t.gTimer_pro_set_timer_time < 2){
					     TFT_Disp_Set_TimerTime(0);//1-don't display numbers 0-display numbers
                    }
					else if(pro_t.gTimer_pro_set_timer_time >2  && pro_t.gTimer_pro_set_timer_time < 5){

						TFT_Disp_Set_TimerTime(1); //1-don't display numbers, 0-display numbers //turn off disp timer time

					}
					else{
						timer_blink_times++;
						pro_t.gTimer_pro_set_timer_time=0;

					}
					
					if(timer_blink_times > 2){
						timer_blink_times =0;
						if(gctl_t.gSet_timer_hours >0 ){

							pro_t.timer_mode_flag = timer_time;
							pro_t.mode_key_confirm_flag =0xff;
							gctl_t.gTimer_ctl_set_timer_time_senconds =0;
							pro_t.mode_key_be_changed_flag=0; //repeat set up tempeature value by TFT 

						}
						else{
							pro_t.mode_key_confirm_flag =0xff;
							pro_t.timer_mode_flag = works_time;
						    pro_t.mode_key_be_changed_flag=0; //repeat set up tempeature value by TFT 

						}
					}

				}
				
				TFT_DonnotDisp_Works_Time();
				
				if(pro_t.gTimer_pro_long_key_timer_flag > 2){ //exit mode key for long time key  flag

					pro_t.long_key_flag =0;
					pro_t.mode_key_be_changed_flag=0; //repeat set up tempeature value by TFT 
				}	

			break;
		}
		pro_t.run_process_step=pro_disp_wifi_led;

	case pro_disp_wifi_led: //4
		  
		//  Ptc_Temperature_Compare_Value();
		  
	    if(wifi_state() ==1){
			  pro_t.run_process_step=6;
        }
		else{

             switch(pro_t.wifi_led_fast_blink_flag){

			 case 1:
				Wifi_Fast_Led_Blink();
			     if(pro_t.gTimer_pro_long_key_timer_flag > 2){
				 	
			        pro_t.long_key_flag =0;

			     }
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
				pro_t.run_process_step=pro_mode_key_fun;
			 break;

             }

		}
		  
		 
	 break;

	case pro_mode_key_fun://5 //mode key function selection 

	    switch(pro_t.mode_key_confirm_flag){


			case mode_key_temp:
				

			if(pro_t.gTimer_pro_mode_key_timer > 3){

                  if(pro_t.gTimer_pro_set_tem_value_blink < 2){

					 TFT_Disp_Temp_Value(1,gctl_t.gSet_temperature_value);  //1-don't display temp value , 0-display numbers 


				  }
				  else if(pro_t.gTimer_pro_set_tem_value_blink  > 1 && pro_t.gTimer_pro_set_tem_value_blink < 3){

					  TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);  //0-display numbers 


				  }
				  else{
                    pro_t.gTimer_pro_set_tem_value_blink=0;
                    led_blink_times++;
				  }

                  if(led_blink_times ==1){
				  	led_blink_times=0;
					  pro_t.mode_key_confirm_flag = 0xff;
					  pro_t.gTimer_pro_tft =30; //at once display dht11 sensor temperature value 
					  pro_t.set_temperature_value_flag= 1;
					  pro_t.mode_key_be_changed_flag=0; //repeat set up tempeature value by TFT 

                  }

				}
			
			break;


			case mode_key_select:

		     if(pro_t.gTimer_pro_mode_key_timer < 5){ //exit of rule

				if(pro_t.timer_mode_flag == timer_time)pro_t.timer_mode_flag=works_time;
				else pro_t.timer_mode_flag = timer_time;
				Mode_Key_Select_Fun();
             

			 }
			 else{

                pro_t.mode_key_confirm_flag = 0xff;

			 }


		   break;


		   case mode_key_confirm:
			  if(pro_t.gTimer_pro_mode_key_timer < 5){ //exit of rule

				Mode_Key_Confirm_Fun();


			 }
			 else{

                pro_t.mode_key_confirm_flag = 0xff;

			 }


		   break;


		   default:

		   break;

          }
      
	
		pro_t.run_process_step=1;
      break;

	 case 6: //wif_fun
	 	
	   if(wifi_state() ==1){
		
		 // SendData_Set_Command(WIFI_CONNECT_SUCCESS);
		 // wifi_link_flag =0;
        }
		else{
		//	wifi_link_flag =0;

        }

	 pro_t.run_process_step=2;

	 break;

    default:
    break;
   	}
   }
   else{
   	if(power_been_flag == 1){
		power_been_flag =0;
		TFT_BACKLIGHT_OFF();
		Power_Off_Fun();
        Buzzer_KeySound();
	}
	LED_Mode_Key_Off();
	Breath_Led();

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
   gctl_t.ptc_flag = 1;

   pro_t.mode_key_confirm_flag=0xff;
   gctl_t.mode_flag = works_time;
   pro_t.timer_mode_flag =works_time;
   gctl_t.plasma_flag = 1;
   gctl_t.ultrasonic_flag =1;
   
 	gctl_t.gSet_temperature_value =0; //run_t.temperature_set_flag = 0; //WT.EDIT 2023.01.31
    gctl_t.gSet_timer_hours = 0; //run_t.setup_temperature_value=0; // //WT.EDIT 2023.01.31
  //timer timing
	 gctl_t.gSet_timer_hours =0;
	 gctl_t.gSet_timer_minutes =0;

}
     


static void Power_Off_Fun(void)
{
	 		 
     
	LED_Mode_Key_Off();
	LED_Power_Key_Off();

	Power_Off_Led();

 
   gctl_t.mode_flag = 0;
   gctl_t.plasma_flag = 0;
   gctl_t.ultrasonic_flag =0;



    pro_t.wifi_led_fast_blink_flag=0;
	

    gctl_t.gSet_timer_hours =0;

	gctl_t.ptc_warning = 0;
	gctl_t.fan_warning=0;


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

		  pro_t.gTimer_pro_long_key_timer_flag=0; //long key exit "mode_long_key flag" flag
		  pro_t.gTimer_pro_mode_key_timer=0;
		  pro_t.gTimer_pro_set_timer_time=0;
		  
		  TFT_Disp_Set_TimerTime(0);
		   
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
static void ADD_Key_Fun(void)
{
 
 if(power_on_state()==power_on){

	if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){

		Buzzer_KeySound();

		switch(pro_t.mode_key_confirm_flag){

		case 0xff:

			pro_t.mode_key_confirm_flag=mode_key_temp;

			case mode_key_temp: //set temperature value add number

			gctl_t.gSet_temperature_value ++;
			if( gctl_t.gSet_temperature_value < 20){
			gctl_t.gSet_temperature_value=20;
			}

			if(gctl_t.gSet_temperature_value > 40) gctl_t.gSet_temperature_value= 20;


			pro_t.gTimer_pro_mode_key_timer = 0; //counter starts after 4 seconds ,cancel this function

			TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);	
		break;

		case mode_key_timer_time:


			gctl_t.gSet_timer_hours ++ ;//disp_t.disp_timer_time_hours++ ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes + 60;
			if(gctl_t.gSet_timer_hours  > 24){ //if(pro_t.dispTime_minutes > 59){

			gctl_t.gSet_timer_hours =0;//pro_t.dispTime_hours =0;


			}
			pro_t.gTimer_pro_mode_key_timer = 0; //counter starts after 4 seconds ,cancel this function
			pro_t.gTimer_pro_set_timer_time=0; //TFT set the timer time blinking
			TFT_Disp_Set_TimerTime(0);

		break;

		case mode_key_select:
			pro_t.gTimer_pro_mode_key_timer = 0;
			gctl_t.select_main_fun_numbers++;
			if(gctl_t.select_main_fun_numbers > 3){
			gctl_t.select_main_fun_numbers = 1;
			}


		break;



		}	
		}
	}
       //  DisplayPanel_Ref_Handler();
}
/************************************************************************
	*
	*Function Name: static void DEC_Key_Fun(void)
	*Function : KEY OF decrease
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void DEC_Key_Fun(void)
{

	if(power_on_state() ==power_on){
	   	if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){

			Buzzer_KeySound();
	   	
	     switch(pro_t.mode_key_confirm_flag){

		   case 0xff:

		 	pro_t.mode_key_confirm_flag= mode_key_temp;

		   case mode_key_temp:  //default tempearture value 
	    
			 gctl_t.gSet_temperature_value--;
			if( gctl_t.gSet_temperature_value<20)  gctl_t.gSet_temperature_value=40;
	        if( gctl_t.gSet_temperature_value >40) gctl_t.gSet_temperature_value=40;
             pro_t.gTimer_pro_mode_key_timer = 0;

			TFT_Disp_Temp_Value(0,gctl_t.gSet_temperature_value);
			break;

			case mode_key_timer_time: //timer timing set "decrease -down"
	    
	
				
              
				
				gctl_t.gSet_timer_hours --;//disp_t.disp_timer_time_hours -- ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes - 1;
				if(gctl_t.gSet_timer_hours  < 0){//if(pro_t.dispTime_minutes < 0){

				    gctl_t.gSet_timer_hours  =24;//pro_t.dispTime_hours --;
					
					
				}
			 pro_t.gTimer_pro_mode_key_timer = 0;
			 pro_t.gTimer_pro_set_timer_time=0;
			TFT_Disp_Set_TimerTime(0);
			break;

			 case mode_key_select:
				    pro_t.gTimer_pro_mode_key_timer = 0;
					gctl_t.select_main_fun_numbers--;
					if(gctl_t.select_main_fun_numbers < 0){
						gctl_t.select_main_fun_numbers = 3;
					}
					
				 pro_t.gTimer_pro_mode_key_timer = 0;	
				break;

	    	}
	   	  }
		}

  //    DisplayPanel_Ref_Handler();
     



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
      //set up temparature value 
      switch(gctl_t.gSet_temperature_value_flag){

      case 1:
	  
	    if(pro_t.gTimer_pro_temp_delay> 61 && gctl_t.ptc_warning==0){
               pro_t.gTimer_pro_temp_delay =0;
		 
		  
		  if(smartphone_set_temp_value() <= dht11_temp_value()|| dht11_temp_value() >40){//envirment temperature
	  
				gctl_t.ptc_flag = 0 ;//run_t.gDry = 0;
			   // SendData_Set_Command(DRY_OFF_NO_BUZZER);
                 

            }
			else if((smartphone_set_temp_value() -3) > dht11_temp_value()||  dht11_temp_value() <38){
	  
		         gctl_t.ptc_flag = 1;//run_t.gDry = 1;
			    // SendData_Set_Command(DRY_ON_NO_BUZZER);
                    
		         }
				 
	   }

	   	//send temp value to smart phone 
	  	if(gctl_t.set_temp_has_been_flag==1){
			gctl_t.set_temp_has_been_flag =0;

		}
       break;


       case 0:
           
           if(pro_t.gTimer_pro_temp_delay > 66  && gctl_t.ptc_warning==0 ){ //WT.EDIT 2023.07.27 over 40 degree shut of ptc off
                pro_t.gTimer_pro_temp_delay=0;

            if(smartphone_set_temp_value() >19 && smartphone_set_temp_value() < 41){
           
               if(dht11_temp_value() >40 || smartphone_set_temp_value() <= dht11_temp_value()){//envirment temperature
               
                 gctl_t.ptc_flag = 0;
               
                }
               else if(dht11_temp_value() <38 || (smartphone_set_temp_value() -2) > dht11_temp_value() ){
               
                  gctl_t.ptc_flag = 1;
                

			   }
                          

            }
            else{

			 
                 if(dht11_temp_value() >40){//envirment temperature
               
                 	gctl_t.ptc_flag  = 0;
              
                
           
               }
               else if(dht11_temp_value() <38){
               
                  gctl_t.ptc_flag = 1;
                
                 
                }

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
void Power_Key_Detected(void)
{
   
	if(POWER_KEY_StateRead()==KEY_DOWN && pro_t.long_key_flag ==0){

	    

	      if( pro_t.gPower_On == power_off){
		  	  pro_t.key_power_be_pressed_flag =1;
	
			 pro_t.gPower_On = power_on;   
            pro_t.long_key_flag =0;
            pro_t.run_process_step=0;
			
		  }
		  else{
                pro_t.key_power_be_pressed_flag =1;
	           pro_t.long_key_flag =0;
			 
			   pro_t.gPower_On = power_off;   
	         
			 //  Power_Off_Fun();
		
		    pro_t.run_process_step=0xff;
			  
			  
           }


	   }

	if(POWER_KEY_StateRead()==KEY_POWER_LONG_DOWN && pro_t.long_key_flag ==1){

  
         pro_t.key_power_be_pressed_flag =0;

	    Buzzer_KeySound();
		 pro_t.gTimer_pro_wifi_led =0;
        pro_t.wifi_led_fast_blink_flag=1;
		pro_t.gTimer_pro_long_key_timer_flag=0;
        K1=0;
		

	}


}
/// @brief : detected mode key press
/// @param  
void Mode_Key_Detected(void)
{
	if(MODE_KEY_StateRead() == KEY_DOWN && pro_t.long_key_flag ==0){

		pro_t.mode_key_be_changed_flag = pro_t.mode_key_be_changed_flag ^ 0x01;
		
		if(pro_t.mode_key_be_changed_flag == 1){
		  Buzzer_KeySound();

		  pro_t.mode_key_confirm_flag = mode_key_select;
		  pro_t.gTimer_pro_mode_key_timer = 0; //counter starts after 4 seconds ,cancel this function
		  gctl_t.gTimer_ctl_select_led =0;
		 }
         else{
			Buzzer_KeySound();
			pro_t.mode_key_confirm_flag = mode_key_confirm;
			pro_t.gTimer_pro_mode_key_timer=0;

		}
	} 

	if(MODE_KEY_StateRead()==KEY_MODE_LONG_DOWN && pro_t.long_key_flag ==1){
       Buzzer_KeySound();
	   pro_t.gTimer_pro_mode_key_timer=0;
       Mode_Long_Key_Fun();
      

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
void ADD_Key_Detected(void)
{
	if(ADD_KEY_StateRead()==KEY_DOWN){
          ADD_Key_Fun();
    }


}
void DEC_Key_Detected(void)
{
	 if(DEC_KEY_StateRead()==KEY_DOWN){
	 	

		 DEC_Key_Fun();
	 }

}

static void Wifi_Fast_Led_Blink(void)
{
   if(pro_t.wifi_led_fast_blink_flag==1){
	if(pro_t.gTimer_pro_wifi_led < 166){//2'46s

wifi_led:	if( pro_t.gTimer_pro_wifi_fast_led < 80 ){ //50ms

	 LED_WIFI_ICON_ON();
	 

	}
	
	if(pro_t.gTimer_pro_wifi_fast_led > 80 && pro_t.gTimer_pro_wifi_fast_led< 161){

        
		LED_WIFI_ICON_OFF();
	}
	

	 
	 if(pro_t.gTimer_pro_wifi_fast_led > 159){

		pro_t.gTimer_pro_wifi_fast_led=0;
		if(pro_t.gTimer_pro_wifi_led > 165){ //2'46s
	      pro_t.wifi_led_fast_blink_flag=0;


	    }
		else{
		   LED_WIFI_ICON_OFF();
		   HAL_Delay(2);
		   goto wifi_led;

		}

	 }
	}
	if(pro_t.gTimer_pro_wifi_led > 165){ //2'46s
	    pro_t.wifi_led_fast_blink_flag=0;


	}
   }
	
}



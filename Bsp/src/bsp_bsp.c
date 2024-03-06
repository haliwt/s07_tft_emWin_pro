#include "bsp.h"


static void disp_works_or_timer_time_handler(void);
static void TFT_Donnot_Set_Timer_Time(void);
		
static void Ptc_Temperature_Compare_Value(void);

/******************************************************************************
	*
	*Function Name:void TFT_Pocess_Command_Handler(void)
	*Funcion: display of TFT lcd 
	*Input Ref:NO
	*Return Ref:NO
	*
******************************************************************************/
void TFT_Pocess_Command_Handler(void)
{
   
	static uint8_t timer_blink_times,fan_2_hours_stop,update_step;


    if(power_on_state() == power_on){
  
    switch(pro_t.run_process_step){


	case 0:
	 	
		pro_t.gKey_value =0XFF;
	    
		Power_On_Fun();
	    Fan_Run();
		gctl_t.gTimer_ctl_total_continue_time =0;
        gctl_t.timer_time_define_flag =0;
		gctl_t.gTimer_ctl_disp_second=0;
		pro_t.long_key_flag =0;

         pro_t.run_process_step=1;
	


		TFT_BACKLIGHT_ON();
		
		pro_t.long_key_flag =0;
		TFT_Display_WorksTime();
		
	break;

	 case pro_disp_dht11_value: //1 //display works time + "temperature value " + "humidity value"

	   Wifi_Fast_Led_Blink();
	

	   if(gctl_t.gTimer_ctl_det_dth11 > 35 &&  pro_t.wifi_led_fast_blink_flag==0){
	   	   gctl_t.gTimer_ctl_det_dth11 =0;
		
            Update_DHT11_Value();

		   TFT_Disp_Humidity_Value(gctl_t.dht11_hum_value);
	   }

	  
	   
	   pro_t.run_process_step=pro_run_continue_two_hours;
	   
	case pro_run_continue_two_hours: //02

	  Wifi_Fast_Led_Blink();

	  switch(gctl_t.time_out_flag){

	  	case 0:
		
	      if(fan_2_hours_stop==2){ //8s
		
		
             fan_2_hours_stop=0;
		     Fan_Run();
		
             
	      }
	   break;

	   case 1:
          Device_stop_Action_Fun();
		  if(fan_2_hours_stop ==0){
             
			 	fan_2_hours_stop=1;
                pro_t.gTimer_pro_fan=0;

			 }

			 if(pro_t.gTimer_pro_fan < 61 && fan_2_hours_stop==1){

                   Fan_Run();
			 }
			 else{

				 fan_2_hours_stop=2;
				 Fan_Stop();

			 }
          pro_t.run_process_step=pro_disp_works_time;
	 break;

	 case pro_disp_works_time://3 //display works times and timer timing .

		Wifi_Fast_Led_Blink();
		disp_works_or_timer_time_handler();
		
		pro_t.run_process_step=pro_disp_and_set_temperature;

    break;
	 
    case pro_disp_and_set_temperature:

       Wifi_Fast_Led_Blink();

	    switch(gctl_t.set_temperature_value_flag){

		case select_set_temp_fun:

	    if(gctl_t.set_temperature_value_flag==select_set_temp_fun && pro_t.gTimer_pro_set_tem_value_blink > 3){

            gctl_t.set_temperature_value_flag= select_temp_by_set; //2
            pro_t.gTimer_pro_temp_delay =66; //at once compare that set temperature value and real tempearture value compare.
		    

		}

		break;

		case select_temp_by_set:
		
        Ptc_Temperature_Compare_Value();

		
        case select_disp_temp:

		 if(pro_t.gTimer_pro_disp_tempe_value > 32 &&  pro_t.wifi_led_fast_blink_flag==0){
	   	    pro_t.gTimer_pro_disp_tempe_value =0;
		
            if(pro_t.mode_key_confirm_flag != mode_key_temp){
			   TFT_Disp_Temp_Value(0,gctl_t.dht11_temp_value);
            }
		}
		break;
	    }
	
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

	  if( update_step==5){
	  	  pro_t.run_process_step=pro_disp_dht11_value;
		  
	   }
      }
	   else{


	       if(update_step ==5 && wifi_t.gTimer_publish_action_item > 62){
		   	     wifi_t.gTimer_publish_action_item=0;

				 Device_Action_Publish_Handler();
		   }
		   TFT_DonnotDisp_Works_Time();
		   pro_t.run_process_step=pro_disp_dht11_value;
	


	   }

	  break;


    default:
    break;
   	}
   }
  
   
}
}
/************************************************************************
	*
	*Function Name: static void disp_works_or_timer_time_handler(void)
	*Function : display works time or timer timing other by select one
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void disp_works_or_timer_time_handler(void)
{

	switch(pro_t.key_input_model_timer_or_timing){
	
	case timer_time_id: //1= timer_time 
		gctl_t.timer_time_define_flag = 1;
		gctl_t.display_timer_timing =1;
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

			TFT_Disp_Set_TimerTime(0);
			TFT_Display_Timer_Timing_Value(0);


		}

		if(pro_t.gTimer_pro_display_timer_timing > 5){

			pro_t.gTimer_pro_display_timer_timing=0;

			TFT_Display_Timer_Timing_Value(0);

		}


	break;

	case works_time_id:

		gctl_t.display_timer_timing =0;

		if(gctl_t.gTimer_ctl_disp_second > 59){
		TFT_Display_WorksTime();
		gctl_t.display_timer_timing=0;
		}

		if(pro_t.gTimer_pro_display_timer_timing > 5){

		pro_t.gTimer_pro_display_timer_timing=0;
		TFT_Display_WorksTime();
		}

		TFT_Donnot_Set_Timer_Time();

	break;


	case timer_set_time_id:

	//TFT_Disp_Set_TimerTime_Init();
    TFT_Display_Timer_Timing_Value(1); //1-set up temperature value 

	if(pro_t.gTimer_pro_set_timer_time > 4){


		if(gctl_t.gSet_timer_hours >0 ){

		pro_t.key_input_model_timer_or_timing = timer_time_id;
		pro_t.mode_key_confirm_flag =0xff;
		gctl_t.gTimer_ctl_set_timer_time_senconds =0;
		gctl_t.timer_time_define_flag = 1;
		gctl_t.gSet_timer_minutes =0;
		pro_t.gTimer_pro_display_timer_timing =20;



		}
		else{
		
		gctl_t.timer_time_define_flag = 0;
		pro_t.mode_key_confirm_flag =0xff;
		pro_t.key_input_model_timer_or_timing = works_time_id;
		gctl_t.display_timer_timing=0;

       }
	}

	break;
	}



}

/************************************************************************
	*
	*Function Name: void TFT_Display_Timer_Timing_Value(void)
	*Function : power on
	*Input Ref: disp - 0 : display temperature value ; 1- set temperature value 
	*Return Ref:No
	*
************************************************************************/
void TFT_Display_Timer_Timing_Value(uint8_t disp)
{
   static uint8_t timer_decade_hours,timer_unit_hours,timer_decade_minutes,timer_unit_minutes;
   static uint8_t set_hours = 0xff,set_minutes=0xf0,first_input;
  

    timer_decade_hours = gctl_t.gSet_timer_hours /10;
	timer_unit_hours = gctl_t.gSet_timer_hours % 10;



	timer_decade_minutes= gctl_t.gSet_timer_minutes / 10;
	timer_unit_minutes =  gctl_t.gSet_timer_minutes % 10;



   if(disp ==0){


	TFT_Disp_WorkTime_Value_48_48_onBlack(100,188,0,timer_decade_hours);
	TFT_Disp_WorkTime_Value_48_48_onBlack(134,188,0,timer_unit_hours);

    TFT_Disp_WorkTime_Value_48_48_onBlack(186,188,0,timer_decade_minutes);
	TFT_Disp_WorkTime_Value_48_48_onBlack(220,188,0,timer_unit_minutes);
  }
   else{ //set up temperature value 


	   if(set_hours != gctl_t.gSet_timer_hours){
	   	   set_hours = gctl_t.gSet_timer_hours;
		   first_input =1;
	   TFT_Disp_WorkTime_Value_48_48_onBlack(100,188,0,timer_decade_hours);
	   TFT_Disp_WorkTime_Value_48_48_onBlack(134,188,0,timer_unit_hours);

	   }

	   if(first ==1){
	      first_input ++;
	      set_minutes++;

	   }

	   if(set_minutes != gctl_t.gSet_timer_minutes){
	        set_minutes = gctl_t.gSet_timer_minutes;

	   TFT_Disp_WorkTime_Value_48_48_onBlack(186,188,0,timer_decade_minutes);
	   TFT_Disp_WorkTime_Value_48_48_onBlack(220,188,0,timer_unit_minutes);

	   }

   }


}

/********************************************************************************
 * 
 * Function Name: static void TFT_Disp_Set_TimerTime(void)
 * Function: set timer time of TFT of numbers blink.
 * Input Ref: bc : 1-don't display numbers, 0-display numbers
 * Return Ref:
 * 
*********************************************************************************/
void TFT_Disp_Set_TimerTime(uint8_t bc)
{

   static uint8_t timer_decade_hours,timer_unit_hours,timer_decade_minutes,timer_unit_minutes;
   static uint8_t set_timer_hours=0xff,set_timer_minutes = 0xff,disp_timer_words=0xff;

    timer_decade_hours = gctl_t.gSet_timer_hours /10;
	timer_unit_hours = gctl_t.gSet_timer_hours % 10;

	timer_decade_minutes= gctl_t.gSet_timer_minutes / 10;
	timer_unit_minutes = gctl_t.gSet_timer_minutes % 10;

    //display works of words of chinese 
    if(disp_timer_words != gctl_t.timer_timing_words_changed_flag){
		disp_timer_words = gctl_t.timer_timing_words_changed_flag;
    TFT_Disp_WorksTime_24_24_onBlack(112,150,1,0);//works one "定"
	TFT_Disp_WorksTime_24_24_onBlack(136,150,1,1);//"时"
	TFT_Disp_WorksTime_24_24_onBlack(160,150,1,2);//“时”
	TFT_Disp_WorksTime_24_24_onBlack(184,150,1,3);//“间”

    }
	

	///if(set_timer_hours != gctl_t.gSet_timer_hours ){
	//	set_timer_hours = gctl_t.gSet_timer_hours;
	TFT_Disp_WorkTime_Value_48_48_onBlack(100,188,bc,timer_decade_hours);
	TFT_Disp_WorkTime_Value_48_48_onBlack(134,188,bc,timer_unit_hours);

	//}

	///if(set_timer_minutes != gctl_t.gSet_timer_minutes ){
	//	set_timer_minutes = gctl_t.gSet_timer_minutes;
	TFT_Disp_WorkTime_Value_48_48_onBlack(186,188,bc,timer_decade_minutes);
	TFT_Disp_WorkTime_Value_48_48_onBlack(220,188,bc,timer_unit_minutes);

	//}
	
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
   if(gctl_t.set_temperature_value_flag==2){
	  
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
	
       }
	   else{
           
           if(pro_t.gTimer_pro_temp_delay > 66  && gctl_t.ptc_warning==0 ){ //WT.EDIT 2023.07.27 over 40 degree shut of ptc off
                pro_t.gTimer_pro_temp_delay=0;

             if(dht11_temp_value() >40){//envirment temperature
               
                gctl_t.ptc_flag = 0 ;//run_t.gDry = 0;
			    Ptc_Off();
		        LED_PTC_ICON_OFF();
              
                
           
               }
               else if(dht11_temp_value() <39){
               
				 gctl_t.ptc_flag = 1;//run_t.gDry = 1;
		         Ptc_On();
			     LED_PTC_ICON_ON();
                
                
                 
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
static void TFT_Donnot_Set_Timer_Time(void)
{


   

	if(gctl_t.timer_time_define_flag == 1 && gctl_t.display_timer_timing ==0){

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



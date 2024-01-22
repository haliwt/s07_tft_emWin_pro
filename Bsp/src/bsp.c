#include "bsp.h"

PRO_T pro_t;

static void Ptc_Temperature_Compare_Value(void);
static void Power_Key_Detected(void);
static void Mode_Key_Detected(void);
static void ADD_Key_Detected(void);
static void DEC_Key_Detected(void);

static void Mode_Fun(void);

static void Mode_Long_Key_Fun(void);

static void TFT_Pocess_Command_Handler(void);

static void Power_On_Fun(void);
static void Power_Off_Fun(void);

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
	/* --- 喂狗 */
    if(pro_t.gTimer_pro_feed_dog > 4){ //16s
	pro_t.gTimer_pro_feed_dog = 0;	
	iwdg_feed();

    }


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
*	函 数 名: void TFT_Process_Handler(void)
*	功能说明: TFT显示的内容
*			 
*	形    参: 无
*	返 回 值: 无
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
	*Input Ref:
	*Return Ref:
	*
******************************************************************************/
static void TFT_Pocess_Command_Handler(void)
{
   //key input run function

   static uint8_t power_been_flag;
  
 

   if(power_on_state() == power_on){
  
    switch(pro_t.run_process_step){


	 case 0:
	 	Power_On_Fun();
	    Buzzer_KeySound();
	  
		pro_t.long_key_flag =0;
		pro_t.key_power_be_pressed_flag =0;
		pro_t.ack_power_on_sig=0; 
		

		
	  //  TFT_LCD_Init();
		//HAL_Delay(200);
		//TFT_ST7789_FillPicture(0,0,LCD_Width,LCD_Height,gImage_s07_main_picture);
		//LCD_Clear(BROWN);
		//TFT_ShowPicture(0,0,gImage_s07_main_picture,LCD_Width,LCD_Height);
		///HAL_Delay(300);
		///LCD_Clear(GBLUE);
		///HAL_Delay(300);
	     pro_t.run_process_step=1;



	 break;

	 case 1:  //display works time + "temperature value " + "humidity value"
	     TFT_BACKLIGHT_ON();
		// LCD_Clear(BROWN);
	    // HAL_Delay(300);
		 //LCD_Clear(GBLUE);
		 LCD_Clear(GBLUE);
		// DISPLAY_COLOR(GBLUE);
		 HAL_Delay(200);
		 LCD_Clear(YELLOW);
		 HAL_Delay(200);
		// Frame();//LCD_Clear(GREEN);
		//TFT_ShowPicture(0,0,gImage_s07_main_picture,(LCD_Width-1),(LCD_Height-1));
		 TFT_ST7789_FillPicture(0,0,(LCD_Width-1),(LCD_Height-1),gImage_s07_main_picture);
		 HAL_Delay(500);
		 
		//TFT_ShowPicture(0,0,gImage_s07_main_picture,LCD_Width,LCD_Height);

		 power_been_flag=1;
         pro_t.long_key_flag =0;
	     pro_t.key_power_be_pressed_flag =0;
	     if(pro_t.gTimer_pro_ms > 40){ //20 *10ms = 200ms
			 pro_t.gTimer_pro_ms =0;

		     Device_Action_Handler();
			 
         }
		  
		if(pro_t.gTimer_pro_disp_timer > 4){ //3s 
		  	pro_t.gTimer_pro_disp_timer =0;
		    TFT_Works_Or_Timer_times_Handler();

		  }

		  Ptc_Temperature_Compare_Value();
		  
	      if(wifi_state() ==1){
			  pro_t.run_process_step=4;
          }
		  else
            pro_t.run_process_step=2;
		 
	 break;

	

	 case 2: //set timer times pro
	 if(pro_t.gTimer_pro_disp_ms > 3 ){ 
			pro_t.gTimer_pro_disp_ms=0;
			TFT_Display_Handler();
       }
	   

	   pro_t.run_process_step=3;


	 break;

	 case 3:
      // KEY_POWER_ON_LED();
	  if(pro_t.set_timer_flag==1){ //
		  pro_t.set_timer_flag++;
             
	     // SendData_Time_Data(disp_t.disp_set_timer_timing);
		  
      }

	  pro_t.run_process_step=1;
      break;

	 case 4:
	 	// KEY_POWER_ON_LED();
	   if(wifi_state() ==1){
		
		 // SendData_Set_Command(WIFI_CONNECT_SUCCESS);
		 // wifi_link_flag =0;
        }
		else if(pro_t.ack_wifi_led ==0){
			
		  // SendData_Set_Wifi(0x01);

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
   gctl_t.ptc_flag = 1;
   gctl_t.mode_flag = works_time;
   gctl_t.plasma_flag = 1;
   gctl_t.ultrasonic_flag =1;
   
 
	
	gctl_t.gSet_temperature_value =0; //run_t.temperature_set_flag = 0; //WT.EDIT 2023.01.31
    gctl_t.gSet_timer_hours = 0; //run_t.setup_temperature_value=0; // //WT.EDIT 2023.01.31
  
	

     pro_t.temperature_set_flag = 0;

	  //timer timing
	 gctl_t.gSet_timer_hours =0;
	 gctl_t.gSet_timer_minutes =0;

}
     


static void Power_Off_Fun(void)
{
	 		 
     
	LED_Mode_Key_Off();
	LED_Power_Key_Off();

 
   gctl_t.mode_flag = 0;
   gctl_t.plasma_flag = 0;
   gctl_t.ultrasonic_flag =0;

	pro_t.temperature_set_flag = 0;

    pro_t.wifi_led_fast_blink_flag=0;
	pro_t.gTimer_mode_flag = 0;

    gctl_t.gSet_timer_hours =0;

	gctl_t.ptc_warning = 0;
	gctl_t.fan_warning=0;

//	if(fan_runContinue==2){
//		fan_runContinue=1;
//		pro_t.gTimer_pro_fan =0;

//	}

}
void power_off_fan_run(void)
{
	
    LED_Mode_Key_Off();
	Breath_Led();
	
//	if(fan_runContinue == 1 && power_off_first_flag!=0){
//	if(pro_t.gTimer_pro_fan < 61){
//		
//	}
//	else {
//	    fan_runContinue  =0;
//		

//	}

	

}

/************************************************************************
	*
	*Function Name: static void Power_On_Fun(void)
	*Function : power on
	*Input Ref:NO
	*Return Ref:No
	*
************************************************************************/
static void Mode_Fun(void)
{
	
	if(power_on_state() ==power_on){
		
			 
	   if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){

	          if(mode_state()==works_time){ //be chaned ai mode 
			   //isp_t.disp_timer_or_works_timing = timer_time;
				gctl_t.mode_flag = timer_time;
				
			  }
			  else{
				 gctl_t.mode_flag =works_time; //no_AI model
				  
				 
					
			  }
				
				
	  } 	
	}
		 
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
	  	
		   
		   gctl_t.mode_flag =timer_time;

		   pro_t.gTimer_mode_flag=1; //set timer timing enable,
		 
		   pro_t.gTimer_key_timing=0; //按键退出的限制，4秒以内
		
          // SendData_Set_Wifi(MODE_TIMER);
		   
		   
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
 
    uint8_t  temp_bit_1_hours,temp_bit_2_hours,temp_bit_2_minute,temp_bit_1_minute;

	 if(power_on_state()==power_on){

		   if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){

			Buzzer_KeySound();
		
			switch(pro_t.gTimer_mode_flag){

			case set_temperature: //set temperature value add number
      
		
				 gctl_t.gSet_temperature_value ++;
	            if( gctl_t.gSet_temperature_value < 20){
				     gctl_t.gSet_temperature_value=20;
				}
				
				if( gctl_t.gSet_temperature_value > 40) gctl_t.gSet_temperature_value= 20;

			
            
			   // decade_temp =   gctl_t.gSet_temperature_value / 10 ;
				//unit_temp =   gctl_t.gSet_temperature_value % 10; //
//                
//				lcd_t.number1_low=gctl_t.gSet_temperature_value / 10 ;
//				lcd_t.number1_high =gctl_t.gSet_temperature_value / 10 ;

//				lcd_t.number2_low = gctl_t.gSet_temperature_value % 10; //
//				lcd_t.number2_high = gctl_t.gSet_temperature_value % 10; //
				
				//lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led" timer timing
                pro_t.temperature_set_flag=1;  //set temperature value flag
               // DisplayPanel_Ref_Handler();
				
               break;

			   case set_timer_timing:
				    
					pro_t.gTimer_key_timing =0;
                   // disp_t.set_timer_timing_value_chaned_flag++;
			   	//	if(disp_t.set_timer_timing_value_chaned_flag > 254 ) disp_t.set_timer_timing_value_chaned_flag=0;
					
					gctl_t.gSet_timer_hours ++ ;//disp_t.disp_timer_time_hours++ ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes + 60;
				    if(gctl_t.gSet_timer_hours  > 24){ //if(pro_t.dispTime_minutes > 59){

		                 gctl_t.gSet_timer_hours =0;//pro_t.dispTime_hours =0;
		                

					}
				
                    temp_bit_2_hours = gctl_t.gSet_timer_hours  /10 ;
					temp_bit_1_hours = gctl_t.gSet_timer_hours  %10;
                 
					
					//DisplayPanel_Ref_Handler();
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

    uint8_t  decade_temp,unit_temp,temp_bit_1_hours,temp_bit_2_hours;
	uint8_t temp_bit_2_minute=0,temp_bit_1_minute=0;
	if(power_on_state() ==power_on){
	   	if(gctl_t.ptc_warning ==0 && gctl_t.fan_warning ==0){

			Buzzer_KeySound();
	   	
	     switch(pro_t.gTimer_mode_flag){

		   case set_temperature:  //default tempearture value 
	    
			 gctl_t.gSet_temperature_value--;
			if( gctl_t.gSet_temperature_value<20)  gctl_t.gSet_temperature_value=40;
	        if( gctl_t.gSet_temperature_value >40) gctl_t.gSet_temperature_value=40;

	

	        decade_temp =   gctl_t.gSet_temperature_value / 10;
			unit_temp =   gctl_t.gSet_temperature_value % 10; //
      
			//lcd_t.number1_low=decade_temp;
			//lcd_t.number1_high =decade_temp;

			//lcd_t.number2_low = unit_temp;
			//lcd_t.number2_high = unit_temp;

			//lcd_t.gTimer_numbers_one_two_blink=0;//display temperature of blink "led"
			pro_t.temperature_set_flag=1;  //set temperature value flag
			//DisplayPanel_Ref_Handler();
		    break;

			case set_timer_timing: //timer timing set "decrease -down"
	    
	
				pro_t.gTimer_key_timing =0;
               // disp_t.set_timer_timing_value_chaned_flag--;
			   // if(disp_t.set_timer_timing_value_chaned_flag==0)disp_t.set_timer_timing_value_chaned_flag=255;
				
				gctl_t.gSet_timer_hours --;//disp_t.disp_timer_time_hours -- ;//pro_t.dispTime_minutes = pro_t.dispTime_minutes - 1;
				if(gctl_t.gSet_timer_hours  < 0){//if(pro_t.dispTime_minutes < 0){

				    gctl_t.gSet_timer_hours  =24;//pro_t.dispTime_hours --;
					
					
				}
				temp_bit_2_hours = gctl_t.gSet_timer_hours  /10 ;
				temp_bit_1_hours = gctl_t.gSet_timer_hours  %10;

				temp_bit_2_minute=0;
				temp_bit_1_minute=0;


				
				//DisplayPanel_Ref_Handler();

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
			//SendData_Temp_Data(gctl_t.gSet_temperature_value);

		}
       break;


       case 0:
           
           if(pro_t.gTimer_pro_temp_delay > 66  && gctl_t.ptc_warning==0 ){ //WT.EDIT 2023.07.27 over 40 degree shut of ptc off
                pro_t.gTimer_pro_temp_delay=0;

            if(smartphone_set_temp_value() >19 && smartphone_set_temp_value() < 41){
           
               if(dht11_temp_value() >40 || smartphone_set_temp_value() <= dht11_temp_value()){//envirment temperature
               
                 gctl_t.ptc_flag = 0;
                // SendData_Set_Command(DRY_OFF_NO_BUZZER);
                
           
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


void Power_Key_Detected(void)
{
   
	if(POWER_KEY_StateRead()==KEY_DOWN && pro_t.long_key_flag ==0){

	    

	      if( pro_t.gPower_On == power_off){
		  	  pro_t.key_power_be_pressed_flag =1;
	
			 pro_t.gPower_On = power_on;   
            pro_t.long_key_flag =0;
            pro_t.run_process_step=0;
			
			
			//SendData_PowerOnOff(1);
			//KEY_POWER_ON_LED();
		  //  Power_On_Fun();
			//LCD_Backlight_On();
		


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
        pro_t.wifi_led_fast_blink_flag=1;
		pro_t.long_key_flag =0;
        K1=0;

	}


}


void Mode_Key_Detected(void)
{
	if(MODE_KEY_StateRead() == KEY_DOWN && pro_t.long_key_flag ==0){

		if(mode_state() == works_time ){
		  pro_t.long_key_flag =0;
		
		  gctl_t.mode_flag = timer_time;
		 // SendData_Set_Wifi(MODE_AI);
		  pro_t.gTimer_pro_disp_timer = 40; //at once be changed ai or no_ai timing.
		 //  Key_Sound();
		 
		
		 }
         else{
		  	 pro_t.long_key_flag =0;
			  gctl_t.mode_flag = works_time;
			//  SendData_Set_Wifi(MODE_TIMER);
			//  Key_Sound();
			 pro_t.gTimer_pro_disp_timer = 40;//at once be changed ai or no_ai timing.
          }



	} 

	if(MODE_KEY_StateRead()==KEY_MODE_LONG_DOWN && pro_t.long_key_flag ==1){

       Mode_Long_Key_Fun();


	}


}


void ADD_Key_Detected(void)
{
	if(ADD_KEY_StateRead()==KEY_DOWN){

		//Key_Sound();
		
		ADD_Key_Fun();
    }


}
void DEC_Key_Detected(void)
{
	 if(DEC_KEY_StateRead()==KEY_DOWN){

		 DEC_Key_Fun();
	 }

}



#include "interrupt_manager.h"
#include "bsp.h"

uint8_t voice_inputBuf[1];

/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    static uint8_t state=0,state_uart1;
    uint32_t temp ;
    //wifi usart2
    if(huart->Instance==USART2)
    {
           
         
        //  USART2->ISR = 0xf5; 
	     
	      if(wifi_t.linking_tencent_cloud_doing  ==1){ //link tencent netware of URL

			wifi_t.wifi_data[wifi_t.wifi_uart_counter] = wifi_t.usart2_dataBuf[0];
			wifi_t.wifi_uart_counter++;

			if(*wifi_t.usart2_dataBuf==0X0A) // 0x0A = "\n"
			{
				//wifi_t.usart2_rx_flag = 1;
				Wifi_Rx_InputInfo_Handler();
				wifi_t.wifi_uart_counter=0;
			}

	      } 
		  else{

		         if(wifi_t.get_rx_beijing_time_enable==1){
					wifi_t.wifi_data[wifi_t.wifi_uart_counter] = wifi_t.usart2_dataBuf[0];
					wifi_t.wifi_uart_counter++;
				}
				else if(wifi_t.get_rx_auto_repeat_net_enable ==1){

					wifi_t.wifi_data[wifi_t.wifi_uart_counter] = wifi_t.usart2_dataBuf[0];
					wifi_t.wifi_uart_counter++;

					if(*wifi_t.usart2_dataBuf==0X0A) // 0x0A = "\n"
					{
						
						Wifi_Rx_Auto_Link_Net_Handler();
						wifi_t.wifi_uart_counter=0;
					}


				}
				else{
					Subscribe_Rx_Interrupt_Handler();

				}
	      }
	  HAL_UART_Receive_IT(&huart2,wifi_t.usart2_dataBuf,1);
	  
	__HAL_UART_CLEAR_NEFLAG(&huart2);
	__HAL_UART_CLEAR_FEFLAG(&huart2);
	__HAL_UART_CLEAR_OREFLAG(&huart2);
	__HAL_UART_CLEAR_OREFLAG(&huart2);
	__HAL_UART_CLEAR_TXFECF(&huart2);
     
	}

	#if 1  //voice sound communcation
	if(huart->Instance==USART1) // Motor Board receive data (filter)
	{
		
	#if 1	
		switch(state_uart1)
		{
		case 0:  //#0
			if(voice_inputBuf[0]==0xA5)  //hex :4D - "M" -fixed mainboard
				state_uart1=1; //=1
			break;
		case 1: //#1
			if(voice_inputBuf[0]==0xFA) //hex : 41 -'A'  -fixed master
			{
				state_uart1=2; 
			}
			else
				state_uart1=0; 
			break;

	   case 2:
	      if(voice_inputBuf[0]==0) //hex : 41 -'A'	-fixed master
		   {
			   state_uart1=3; 
		   }
		   else
			  state_uart1=0; 


	   break;

	   case 3:
	      if(voice_inputBuf[0]==0x81) //hex : 41 -'A'	-fixed master
		   {
			   state_uart1=4; 
		   }
		   else
			  state_uart1=0; 


	   break;

	   case 4:
	      if(voice_inputBuf[0] >0 && voice_inputBuf[0] < 0x38) //hex : 41 -'A'	-fixed master
		   {
               v_t.RxBuf[0]=voice_inputBuf[0];
			   state_uart1=5; 
		   }
		   else
			  state_uart1=0; 


	   break;

	   case 5:
	      if(voice_inputBuf[0]==0x00) //hex : 41 -'A'	-fixed master
		   {
			   state_uart1=6; 
		   }
		   else
			  state_uart1=0; 


	   break;

	   case 6:
	      if(voice_inputBuf[0] >0x20 && voice_inputBuf[0] < 0x58) //hex : 41 -'A'	-fixed master
		   {
               v_t.RxBuf[1]=voice_inputBuf[0];
			   state_uart1=7; 
		   }
		   else
			  state_uart1=0; 


	   break;

	   case 7:
	      if(voice_inputBuf[0]==0xFB) //hex : 41 -'A'	-fixed master
		   {
               v_t.rx_voice_data_enable = 1;
			   state_uart1=0; 

		  }
		  

     break;
	  }
	#endif 
	HAL_UART_Receive_IT(&huart1,voice_inputBuf,1);//UART receive data interrupt 1 byte

	  
	__HAL_UART_CLEAR_NEFLAG(&huart1);
	__HAL_UART_CLEAR_FEFLAG(&huart1);
	__HAL_UART_CLEAR_OREFLAG(&huart1);
	__HAL_UART_CLEAR_OREFLAG(&huart1);
	__HAL_UART_CLEAR_TXFECF(&huart1);

	}
	
    #endif 
  
 }


/*******************************************************************************
	*
	*Function Name:void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	*Function : timer timing 1ms 
	*           sys_clk = 64MHz
	*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint16_t tm0;
  static uint8_t tm1,tm2;
 

    
   if(htim->Instance==TIM17){
    
    tm0++;  //1ms
    tm1++;
   
    pro_t.gTimer_pro_wifi_fast_led++;

	if(tm1 > 9){
		tm1=0;
		gctl_t.gTimer_ctl_select_led++;
	    pro_t.gTimer_pro_detect_key_ms =1;
	}
	
	
	if(tm0>999){ //1000 *1ms = 1000ms = 1s
		tm0=0;
		tm2++;

	 pro_t.gTimer_pro_key_select_fun ++;
	
	 pro_t.gTimer_pro_temp_delay++;
	 pro_t.gTimer_pro_temp++;

	 pro_t.gTimer_pro_feed_dog++;
	
     pro_t.gTimer_pro_tft++;
	 gctl_t.gTimer_ctl_disp_second++;
	 pro_t.gTimer_pro_fan++;  //fan continuce counter 60s
	 /*******************************************/
	  pro_t.gTimer_pro_time_split_symbol++;
	  pro_t.gTimer_pro_wifi_led++;

	
	  pro_t.gTimer_pro_mode_key_timer++;
	  pro_t.gTimer_pro_set_tem_value_blink++;
	 
	  pro_t.gTimer_pro_set_timer_time++;
	  pro_t.gTimer_pro_mode_key_adjust ++;
	  pro_t.gTimer_pro_power_key_adjust++;
	  pro_t.gTimer_pro_disp_tempe_value++;
	  pro_t.gTimer_pro_display_timer_timing++;

      //control timer 
      gctl_t.gTimer_ctl_det_dth11 ++ ;
	  gctl_t.gTimer_ctl_set_timer_time_senconds++;
      gctl_t.gTimer_ctl_disp_works_time++;
 
	  
	  //wifi counter 
	 
	  wifi_t.gTimer_login_tencent_times++;
	  wifi_t.gTimer_publish_dht11++;
	  wifi_t.gTimer_auto_detected_net_state_times++;
	  wifi_t.gTimer_get_beijing_time++;
	  wifi_t.gTimer_read_beijing_time++;
	
	  wifi_t.gTimer_linking_tencent_duration;
	  wifi_t.gTimer_power_first_link_tencent ++;
	  wifi_t.gTimer_main_pro_times++;
	  wifi_t.gTimer_publish_action_item ++;
	  

	  if(tm2 > 59){//1 minute
          tm2 =0;
		  gctl_t.gTimer_ctl_total_continue_time++;
	  }
	 
	  
	 
   }
  }
}








#include "interrupt_manager.h"
#include "bsp.h"

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
    static uint8_t state=0;
    uint32_t temp ;
    //wifi usart2
    if(huart->Instance==USART2)
    {
           
         
        //  USART2->ISR = 0xf5; 
	
	      if(wifi_t.linking_tencent_cloud_doing  ==1){

			wifi_t.wifi_data[wifi_t.wifi_uart_counter] = wifi_t.usart2_dataBuf[0];
			wifi_t.wifi_uart_counter++;

			if(*wifi_t.usart2_dataBuf==0X0A) // 0x0A = "\n"
			{
				wifi_t.usart2_rx_flag = 1;
				Wifi_Rx_InputInfo_Handler();
				wifi_t.wifi_uart_counter=0;
			}

	      } 
		  else{

		         if(wifi_t.get_rx_beijing_time_enable==1){
					wifi_t.wifi_data[wifi_t.wifi_uart_counter] = wifi_t.usart2_dataBuf[0];
					wifi_t.wifi_uart_counter++;
					//Subscribe_Rx_Interrupt_Handler();
				}
				else{
					Subscribe_Rx_Interrupt_Handler();

				}
	      }
	  __HAL_UART_CLEAR_OREFLAG(&huart2);
      HAL_UART_Receive_IT(&huart2,wifi_t.usart2_dataBuf,1);
	}

	#if 0
	if(huart->Instance==USART1)//if(huart==&huart1) // Motor Board receive data (filter)
	{
        //test_counter_usat1++;
		switch(state)
		{
		case 0:  //#0
			if(inputBuf[0] == 'T')  //hex :54 - "T" -fixed
				state=1; //=1
		
			break;
		case 1: //#1
             if(inputBuf[0] == 'K')  //hex :4B - "K" -fixed
				state=2; //=1
			else
			   state =0;
			break;
            
        case 2:
             inputCmd[0]= inputBuf[0];
             state = 3;
        
        break;
        
        case 3:
            inputCmd[1]= inputBuf[0];
            run_t.decodeFlag =1;
            state = 0;
        
        break;
	
		default:
			state=0;
			run_t.decodeFlag =0;
		}
		__HAL_UART_CLEAR_OREFLAG(&huart1); //WT.EDIT 2023.06.16
		HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
		
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
  static uint8_t tm1;
 

    
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

	 pro_t.gTimer_pro_key_select_fun ++;
	
	 pro_t.gTimer_pro_temp_delay++;
	 pro_t.gTimer_pro_temp++;

	 pro_t.gTimer_pro_feed_dog++;
	
     pro_t.gTimer_pro_tft++;
	 gctl_t.gTimer_ctl_disp_second++;
	 /*******************************************/
	  pro_t.gTimer_pro_time_split_symbol++;
	  pro_t.gTimer_pro_wifi_led++;
	 // pro_t.gTimer_pro_long_key_timer_flag++;
	  pro_t.gTimer_pro_timer_mode_times++;
	  pro_t.gTimer_pro_mode_key_timer++;
	  pro_t.gTimer_pro_set_tem_value_blink++;
	  gctl_t.gTimer_ctl_set_timer_time_senconds++;
	  pro_t.gTimer_pro_set_timer_time++;
	  pro_t.gTimer_pro_mode_key_adjust ++;
	  pro_t.gTimer_pro_power_key_adjust++;
	  //wifi counter 
	  wifi_t.gTimer_login_tencent_times++;
	  wifi_t.gTimer_publish_dht11++;
	  wifi_t.gTimer_auto_detected_net_link_state++;
	  wifi_t.gTimer_get_beijing_time++;
	  wifi_t.gTimer_read_beijing_time++;
	
	  wifi_t.gTimer_read_beijing_time++;
	  wifi_t.gTimer_publish_dht11++;
	  wifi_t.gTimer_linking_tencent_duration;
	 
	  
	 
   }
  }
}








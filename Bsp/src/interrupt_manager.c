#include "interrupt_manager.h"
#include "bsp.h"

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
	    pro_t.gTimer_pro_detect_key_ms = 1;
	}
	
	
	if(tm0>999){ //1000 *1ms = 1000ms = 1s
		tm0=0;

	 pro_t.gTimer_pro_ms ++;
	
	 pro_t.gTimer_pro_temp_delay++;
	 pro_t.gTimer_pro_temp++;

	 pro_t.gTimer_pro_feed_dog++;
	 wifi_t.gTimer_get_beijing_time++;
	 wifi_t.gTimer_read_beijing_time++;
	 wifi_t.gTimer_publish_dht11++;
	 wifi_t.gTimer_auto_detected_net_link_state ++;
	 wifi_t.gTimer_linking_tencen_counter++;
	 pro_t.gTimer_pro_tft++;
	 gctl_t.gTimer_ctl_disp_second++;
	 /*******************************************/
	  pro_t.gTimer_pro_time_split_symbol++;
	  pro_t.gTimer_pro_wifi_led++;
	  pro_t.gTimer_pro_long_key_timer_flag++;
	  pro_t.gTimer_pro_timer_mode_times++;
	  pro_t.gTimer_pro_mode_key_timer++;
	  pro_t.gTimer_pro_set_tem_value_blink++;
	  gctl_t.gTimer_ctl_set_timer_time_senconds++;
	  pro_t.gTimer_pro_set_timer_time++;
	  
	  
	 
   }
  }
}








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
  static uint8_t tm0;
  static uint16_t tm2;
    
   if(htim->Instance==TIM17){
    
    tm0++;  //1ms
	tm2++;
	if(tm0 > 9){ //10md
       tm0=0; 
		pro_t.gTimer_pro_ms ++;
	}
	if(tm2>999){ //1000 *1ms = 1000ms = 1s
		tm2=0;
     
	 pro_t.gTimer_pro_disp_timer++;
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
	  pro_t.gTimer_pro_time_split_symbol++;
	
	 
   }
  }
}








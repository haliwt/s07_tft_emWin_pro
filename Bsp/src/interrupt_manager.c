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
	if(tm2>999){ //1000 *1ms = 1000ms = 1s
		tm2=0;
     
	 pro_t.gTimer_pro_feed_dog++;
	
	
	 
   }
  }
}








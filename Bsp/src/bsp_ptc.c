#include "bsp_ptc.h"
#include "bsp.h"


void Ptc_On(void)
{

   PTC_SetHigh();


}

void Ptc_Off(void)
{

   PTC_SetLow();

}

void Ptc_OnOff_Handler(void)
{
   if(ptc_state()== 1){

     Ptc_On();
	 HAL_Delay(200);
	 LED_PTC_ICON_ON();
     MqttData_Publish_SetPtc(0x01);  
	 HAL_Delay(30);//350

  }
  else{
    Ptc_Off();
	LED_PTC_ICON_OFF();
    MqttData_Publish_SetPtc(0); 
	HAL_Delay(30);//350


  }
}






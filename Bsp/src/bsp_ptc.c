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

    // Ptc_On();
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

/********************************************************************************************
	*
	*Function Name:void Ptc_Pro_Handler(void)
	*Function: 
	*Input Ref:NO
	*Return Ref:NO
	*
********************************************************************************************/
void Ptc_Pro_Handler(void)
{
   switch(gctl_t.ptc_warning){

		  case ptc_no_warning:

		   if(gctl_t.gTimer_ctl_ptc_adc_times > 9 ){
              gctl_t.gTimer_ctl_ptc_adc_times =0;

			 Get_PTC_Temperature_Voltage(ADC_CHANNEL_1,5); //Modify :2023.09.03 Get_PTC_Temperature_Voltage(ADC_CHANNEL_1,10);
	        

		   }
  
		  break;

		  case ptc_waning:

		  

		  break;
	    }

	    switch(gctl_t.gSet_temperature_value_flag){

           case normal_disp_item:

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


		   break;


		   case disp_set_temp_value_item:

		      if(pro_t.gTimer_pro_temp_delay> 61 && gctl_t.ptc_warning==0){
               pro_t.gTimer_pro_temp_delay =0;
		 
		  
		  if(set_temp_value() <= dht11_temp_value()|| dht11_temp_value() >40){//envirment temperature
	  
				gctl_t.ptc_flag = 0 ;//run_t.gDry = 0;
			    Ptc_Off();
		        LED_PTC_ICON_OFF();
                 

            }
			else if(set_temp_value()> dht11_temp_value()){
	  
		         gctl_t.ptc_flag = 1;//run_t.gDry = 1;
		         Ptc_On();
			     LED_PTC_ICON_ON();
			    
            }
				 
	        }


		   break;

		   case set_temp_value_item:
	    
		   if(pro_t.gTimer_pro_set_tem_value_blink > 3){
			
               pro_t.gTimer_pro_set_tem_value_blink =0;
			   pro_t.gTimer_pro_temp_delay= 65;
			   pro_t.mode_key_confirm_flag = 0xff;
			   gctl_t.gSet_temperature_value_flag= disp_set_temp_value_item;

		   }


		   break;
	}



}



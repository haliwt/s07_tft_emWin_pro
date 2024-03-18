#include "bsp_ctl.h"
#include "bsp.h"

bsp_ctl gctl_t;




uint8_t (*power_on_state)(void);

uint8_t (*mode_state)(void);

uint8_t (*ptc_state)(void); //adjust of ptc is open or close
uint8_t (*plasma_state)(void); //adjust of plasma is open or close
uint8_t (*ultrasonic_state)(void); //adjust of ultrasoic is open or close

uint8_t (*dht11_humidity_value)(void);
uint8_t (*dht11_temp_value)(void);

uint8_t (*set_key_timer_timing)(void);
uint8_t (*set_temp_value)(void);



uint8_t (*ptc_error_state)(void);
uint8_t (*fan_error_state)(void);

static uint8_t power_default_fun(void);



static uint8_t Mode_Default_Handler(void);

static uint8_t Ptc_Default_Handler(void);
static uint8_t Plasma_Default_Handler(void);
static uint8_t Ultrasonic_Default_Handler(void);
static uint8_t Fan_Default_Handler(void);

static uint8_t dht11_humidity_default_Handler(void);
static uint8_t dht11_tmep_default_Handler(void);


static uint8_t Ptc_Error_Default_Handler(void);

static uint8_t Fan_Error_Default_Handler(void);

static uint8_t set_temp_value_default_handler(void);






void bsp_ctl_init(void)
{

   gctl_t.fan_warning =0;
   gctl_t.ptc_warning = 0;
   gctl_t.ptc_flag=1;
   gctl_t.plasma_flag =1;
   gctl_t.ultrasonic_flag =1;
   
  // UartVarInit();

   Power_Handler(power_default_fun);

   Buzzer_Sound_Fun_Init();
  
  
   Mode_State_Handler(Mode_Default_Handler);
   
   Ptc_State_Handler(Ptc_Default_Handler);
   
   Plasma_State_Handler(Plasma_Default_Handler);
   Ultrasonic_state_Handler(Ultrasonic_Default_Handler);

   Set_Temp_Handler(set_temp_value_default_handler);

   Dht11_humidity_Value_Handler(dht11_humidity_default_Handler);
   Dht11_temp_value_Handler(dht11_tmep_default_Handler);

   
   
   Ptc_error_state_Handler(Ptc_Error_Default_Handler);
   Fan_error_state_Handler(Fan_Error_Default_Handler);

}


/***********************************************************
 *  *
    *Function Name: static uint8_t power_default_fun(void);
    *Function: power turn on or turn off
    *Input Ref: NO
    *Return Ref:  1->turn on ,0-> turn off
    * 
***********************************************************/
static uint8_t power_default_fun(void)
{
      if(pro_t.gPower_On ==power_on) return 1;
	  else return 0;

}

void Power_Handler(uint8_t(* power_on_handler)(void))
{

	power_on_state =power_on_handler;


}


/*****************************************************************************
 * 
 * Function Name: void Wifi_State_Handler(uint8_t(*wifi_handler)(void))
 * Function: 
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/


void Mode_State_Handler(uint8_t(*mode_handler)(void))
{
     mode_state = mode_handler;

}

static uint8_t Mode_Default_Handler(void)
{
      if(gctl_t.mode_flag==1)return 1;
	  else return 0;

}


/*****************************************************************************
 * 
 * Function Name: uint8_t Ptc_State_Handler( uint8_t (*ptc_dat)(uint8_t idat))
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void Ptc_State_Handler( uint8_t (*ptc_handler)(void))
{
   	ptc_state = ptc_handler ;
    
}

uint8_t Ptc_Default_Handler(void)
{
    if(gctl_t.ptc_flag == 1){
        return 1;
	}
	else{
        return 0;

	}
	

}
/*****************************************************************************
 * 
 * Function Name: uint8_t Plasma_State_Handler(uint8_t(*plasma_handler)(uint8_t ipa))
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
void Plasma_State_Handler(uint8_t(*plasma_handler)(void))
{
	 plasma_state = plasma_handler;

}

uint8_t Plasma_Default_Handler(void)
{
  
	if(gctl_t.plasma_flag == 1){
        return 1;
	}
	else{
        return 0;

	}
	

}

/*****************************************************************************
 * 
 * Function Name: void Ptc_Default_Handler(void)
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
void  Ultrasonic_state_Handler(uint8_t(*ultrasonic_handler)(void))
{
		ultrasonic_state = ultrasonic_handler;
}

uint8_t Ultrasonic_Default_Handler(void)
{
	
	if(gctl_t.ultrasonic_flag == 1){
        return 1;
	}
	else{
        return 0;

	}
	
}

static uint8_t set_temp_value_default_handler(void)
{

       return gctl_t.gSet_temperature_value ;

}


void Set_Temp_Handler(uint8_t(*set_temp_value_handler)(void))
{
   set_temp_value = set_temp_value_handler;

}

/*****************************************************************************
 * 
 * Function Name: sensor temp and humidity of function
 * Function:Read temperature value and humidity value
 * Input Ref:NO
 * Return Ref:NO
 * 
*****************************************************************************/
void Dht11_humidity_Value_Handler(uint8_t(*hum_handler)(void))
{
	 dht11_humidity_value = hum_handler;
}

static uint8_t dht11_humidity_default_Handler(void)
{

      return gctl_t.dht11_hum_value;

}

void Dht11_temp_value_Handler(uint8_t(*temp_handler)(void))
{

   dht11_temp_value = temp_handler;

}
static uint8_t dht11_tmep_default_Handler(void)
{
      return gctl_t.dht11_temp_value;

}


/*****************************************************************************
 * 
 * Function Name: uint8_t Error_state_Handeler(uint8_t(*error_handler)(uint8_t idat))
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
void  Ptc_error_state_Handler(uint8_t(*ptc_error_handler)(void))
{
      ptc_error_state = ptc_error_handler;
}

uint8_t Ptc_Error_Default_Handler(void)
{
    
	if(gctl_t.ptc_warning == 1){
        return 1;
	}
	else{
		return 0;

	}
    


}
/*****************************************************************************
 * 
 * Function Name: uint8_t Fan_error_state_Handler(uint8_t(*fan_error_handler)(uint8_t fan_data))
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
void Fan_error_state_Handler(uint8_t(*fan_error_handler)(void))
{
      fan_error_state = fan_error_handler;
}

uint8_t Fan_Error_Default_Handler(void)
{

	if(gctl_t.fan_warning == 1){

	    return 1;
	}
	else{
	   return 0;
	}
    
}

/*****************************************************************************
 * 
 * Function Name: void Device_Action_Publish_Handler(void)
 * Function:
 * Input Ref: NO
 * Return Ref: NO
 * 
*****************************************************************************/
void Device_Action_Publish_Handler(void)
{


  static uint8_t ptc_flag =0xff,plasma_flag=0xff,ultr_flag=0xff;

  if(ptc_flag != ptc_state()){
  	   ptc_flag = ptc_state();
 
	  if(ptc_state()== 1){

	     Ptc_On();
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
   
  if(plasma_flag != plasma_state()){
  	   plasma_flag = plasma_state();
	   if(plasma_state() == 1){
	       Plasma_On();
		   LED_KILL_ICON_ON();
	       MqttData_Publish_SetPlasma(0x01);
		   HAL_Delay(30);
	   }
	   else{
	      Plasma_Off();
		  LED_KILL_ICON_OFF();
	      MqttData_Publish_SetPlasma(0);
		  HAL_Delay(30);

	   }

  }

  if(ultr_flag != ultrasonic_state()){
  	
  	 ultr_flag = ultrasonic_state();
   if(ultrasonic_state()==1){

      Ultrasonic_Pwm_Output();
	  LED_RAT_ICON_ON();
      MqttData_Publish_SetUltrasonic(1);
	  HAL_Delay(30);
	  
   }
   else{

	  Ultrasonic_Pwm_Stop();
	  LED_RAT_ICON_OFF();
      MqttData_Publish_SetUltrasonic(0);
	  HAL_Delay(30);

   }

  }



}
/*****************************************************************************
 * 
 * Function Name: void Device_Action_No_Wifi_Handler(void)
 * Function:
 * Input Ref: NO
 * Return Ref: NO
 * 
*****************************************************************************/
void Device_Action_No_Wifi_Handler(void)
{


   Fan_Run();

   if(wifi_link_net_state() == 1){
      LED_WIFI_ICON_ON();

   }
   

  if(ptc_state()== 1){

      //Ptc_On();
	 LED_PTC_ICON_ON();
   

  }
  else{
   /// Ptc_Off();
	LED_PTC_ICON_OFF();
   


  }
   

   if(plasma_state() == 1){
       Plasma_On();
	   LED_KILL_ICON_ON();
      
   }
   else{
      Plasma_Off();
	  LED_KILL_ICON_OFF();
     

   }

   if(ultrasonic_state()==1){

      Ultrasonic_Pwm_Output();
	  LED_RAT_ICON_ON();
     
   }
   else{

	  Ultrasonic_Pwm_Stop();
	  LED_RAT_ICON_OFF();
     

   }



}
/*****************************************************************************
 * 
 * Function Name: void Device_Action_No_Wifi_Handler(void)
 * Function:
 * Input Ref: NO
 * Return Ref: NO
 * 
*****************************************************************************/
void Device_Action_No_Wifi_Power_On_Handler(void)
{


   Fan_Run();

   if(wifi_link_net_state() == 1){
      LED_WIFI_ICON_ON();

   }
   

  if(ptc_state()== 1){

      Ptc_On();
	 LED_PTC_ICON_ON();
   

  }
  else{
    Ptc_Off();
	LED_PTC_ICON_OFF();
   


  }


   if(plasma_state() == 1){
       Plasma_On();
	   LED_KILL_ICON_ON();
      
   }
   else{
      Plasma_Off();
	  LED_KILL_ICON_OFF();
     

   }

   if(ultrasonic_state()==1){

      Ultrasonic_Pwm_Output();
	  LED_RAT_ICON_ON();
     
   }
   else{

	  Ultrasonic_Pwm_Stop();
	  LED_RAT_ICON_OFF();
     

   }



}


void Device_NoAction_Power_Off(void)
{
	
	Ptc_Off();
	LED_PTC_ICON_OFF();
	
	Plasma_Off();
	LED_KILL_ICON_OFF();
		
	
	Ultrasonic_Pwm_Stop();
	LED_RAT_ICON_OFF();
		
}

/*****************************************************************************
 * 
 * Function Name: void Device_Stop_Action_Handler(void)
 * Function:
 * Input Ref: NO
 * Return Ref: NO
 * 
*****************************************************************************/
void Device_stop_Action_Fun(void)
{
    Ptc_Off();
	Plasma_Off();
    Ultrasonic_Pwm_Stop();
}

/*****************************************************************************
 * 
 * Function Name: void Device_Stop_Action_Handler(void)
 * Function:
 * Input Ref: NO
 * Return Ref: NO
 * 
*****************************************************************************/
void Device_Action_Led_OnOff_Handler(void)
{


  if(ptc_state()== 1){

    
	 LED_PTC_ICON_ON();

  }
  else{
    
	LED_PTC_ICON_OFF();
 }

 if(plasma_state() == 1){
     
	   LED_KILL_ICON_ON();
   }
   else{
    
	  LED_KILL_ICON_OFF();

   }

   if(ultrasonic_state()==1){

    
	  LED_RAT_ICON_ON();
	  
   }
   else{
      LED_RAT_ICON_OFF();

   }



}




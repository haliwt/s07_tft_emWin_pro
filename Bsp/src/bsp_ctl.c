#include "bsp_ctl.h"
#include "bsp.h"

bsp_ctl gctl_t;


uint8_t (*wifi_state)(void);
uint8_t (*mode_state)(void);

uint8_t (*ptc_state)(void); //adjust of ptc is open or close
uint8_t (*plasma_state)(void); //adjust of plasma is open or close
uint8_t (*ultrasonic_state)(void); //adjust of ultrasoic is open or close

uint8_t (*dht11_humidity_value)(void);
uint8_t (*dht11_temp_value)(void);

uint8_t (*smartphone_set_timer_timing)(void);
uint8_t (*smartphone_set_temp_value)(void);



uint8_t (*ptc_error_state)(void);
uint8_t (*fan_error_state)(void);

static uint8_t Wifi_Default_Handler(void);
static uint8_t Mode_Default_Handler(void);

static uint8_t Ptc_Default_Handler(void);
static uint8_t Plasma_Default_Handler(void);
static uint8_t Ultrasonic_Default_Handler(void);
static uint8_t Fan_Default_Handler(void);

static uint8_t dht11_humidity_default_Handler(void);
static uint8_t dht11_tmep_default_Handler(void);


static uint8_t Ptc_Error_Default_Handler(void);

static uint8_t Fan_Error_Default_Handler(void);




void bsp_ctl_init(void)
{

   gctl_t.fan_warning =0;
   gctl_t.ptc_warning = 0;
   gctl_t.ptc_flag=1;
   gctl_t.plasma_flag =1;
   gctl_t.ultrasoinc_flag =1;
   UartVarInit();
   Wifi_State_Handler(Wifi_Default_Handler);
   Mode_State_Handler(Mode_Default_Handler);
   
   Ptc_State_Handler(Ptc_Default_Handler);
   
   Plasma_State_Handler(Plasma_Default_Handler);
   Ultrasonic_state_Handler(Ultrasonic_Default_Handler);

   Dht11_humidity_Value_Handler(dht11_humidity_default_Handler);
   Dht11_temp_value_Handler(dht11_tmep_default_Handler);

   
   Ptc_error_state_Handler(Ptc_Error_Default_Handler);
   Fan_error_state_Handler(Fan_Error_Default_Handler);

}

/*****************************************************************************
 * 
 * Function Name: void Wifi_State_Handler(uint8_t(*wifi_handler)(void))
 * Function: 
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void Wifi_State_Handler(uint8_t(*wifi_handler)(void))
{
       wifi_state = wifi_handler;              
      
}
static uint8_t Wifi_Default_Handler(void)
{
     if(gctl_t.wifi_flag == 1)return 1;
	 else return 0;

}

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
	
	if(gctl_t.ultrasoinc_flag == 1){
        return 1;
	}
	else{
        return 0;

	}
	
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




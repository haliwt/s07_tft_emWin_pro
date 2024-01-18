#include "bsp_led.h"
#include "bsp.h"




static void Delay(int16_t count);

volatile uint32_t led_k,led_i;


void LED_Power_Key_On(void)
{
    LED_POWER_KEY_SetHigh() ;


}
void LED_Power_Key_Off(void)
{
	LED_POWER_KEY_SetLow() ;
}

void LED_Mode_Key_On(void)
{
  LED_MODE_KEY_SetHigh();	

}
void LED_Mode_Key_Off(void)
{

	LED_MODE_KEY_SetLow();


}


static void Delay(int16_t count)
{
   
    if(count ==0 || count <0){
       return;
    
    }
    else{
    while(count){

       count--;
   }
   }

}


/***************************************************************
*
*Function Name: void LED_TempHum(void)
*Function : display temperature and humidity and times led 
*
*
*
**************************************************************/
void Breath_Led(void)
{
   {
    static uint32_t i,j;
    led_k++;

	if(led_k<2001){
        i=0;
        j=0;
		LED_Power_Key_On();
		Delay(led_k);
	   LED_Power_Key_Off();
	   Delay(8000-led_k);

    }
    if(led_k>1999 && led_k <4001){
        j++;
		LED_Power_Key_Off();
		Delay(j);
        LED_Power_Key_On();
        Delay(2000-j);
        

    }
    else if(led_k>3999 && led_k <6001){
		led_i++;

	  
	   LED_Power_Key_On();
       LED_Power_Key_Off();
	   Delay(2300+led_i);
      

	}
    else if(led_k>5999){
        led_k =30000;
        i++; 
      if(i<50000){
          LED_Power_Key_Off();
      }
      else{
        led_i=0;
		led_k=0;
        
        
      }
	}
	

}
	

}






#include "bsp_lcd.h"
#include "bsp.h"

lcd_ref glcd_t; 


#define WIFI_Symbol     		0x01 //addr 0xC5 -high word
#define WIFI_NO_Symbol          0

#define AI_Symbol    			0x01 //addr 0xC4 -high word
#define AI_NO_Symbol            0x0

#define DRY_Symbol              0x01  //addr 0xC9 ->T3 high word
#define DRY_NO_Symbol           0x0

#define PLASMA_Symbol             0x01  //addr 0xCA ->T4  high word
#define PLASMA_NO_Symbol          0x0

#define BUG_Symbol            	0x01   //addr 0xCC ->T5 high word
#define BUG_NO_Symbol         	0x0

#define TEMP_Symbol              0x01     //addr 0xC2 ->T7 high word

#define HUMI_Symbol              0x01     //addr  0xC3 ->T6  high word



//wind symbol 0xCE
//low word 
#define T9                       0x01      //addr 0xCE --> high word
#define T14                      0x02     // addr 0xCE -> high word
#define T13                      0x04     //addr 0xCE -->high word
#define T16_WIND_SPEED_ONE       0x08     // high word

//high word
#define T10                      0x10      //addr 0xCE  --> low word
#define T15  					 0x20     // addr 0xCE -> low word  -> circle
#define T12                      0x40      //addr 0xCE -->low word
#define T17_WIND_SPEED_TWO       0x80//addr 0xCE


//wind symbol 0xCF
//low word
#define T11                      0x01      //addr 0xCF
#define T18_WIND_SPEED_FULL      0x02   //addr 0xCF
//
////Low Bit
//#define   seg_b  0x02      //SEG1 , //seg_f = 0x20
//#define   seg_g  0x04      //SEG2 , //seg_g = 0x40
//#define   seg_c  0x08      //SEG3 , //seg_d = 0x08
////High BIT
//#define   seg_a  0x10      //SEG4 , //seg_c = 0x04
//#define   seg_f  0x20      //SEG5   //seg_a = 0x01
//#define   seg_e  0x40      //SEG6   //seg_b = 0x02 
//#define   seg_d  0x80      //SEG7 -> ":"

//squear LCD 

//Low 4bit 
#define seg_f   		0x02
#define seg_g   		0x04
#define seg_e	        0x08

//High 4bit
#define seg_a              0x10
#define seg_b              0x20
#define seg_c              0x40
#define seg_d              0x80


#define LUM_VALUE       0x94//0x92//0x93//0x95//0x94//0x97(max)

const unsigned char segNumber_Low[]={
 
         seg_b+seg_c,        		      	// char "0"  	0x00
		 seg_b+seg_c,                      	// char "1"  	0x01
		 seg_b+seg_g,              		  	// char "2"  	0x02
		 seg_b+seg_g+seg_c,               	// char "3"  	0x03
		 seg_b+seg_g+seg_c,               	// char "4"  	0x04
		 seg_g+seg_c,              			// char "5"  	0x05
		 seg_g+seg_c,              			// char "6"  	0x06
		 seg_b+seg_c,                    	// char "7"  	0x07
		 seg_b+seg_g+seg_c,  		        // char "8"  	0x08
		 seg_b+seg_g+seg_c,        			// char "9"  	0x09
	     0                                  // char "null"  0x0A



};


const unsigned char segNumber_High[]={
         seg_a+seg_f+seg_e+seg_d,        // char "0"  		0x00
		 0,                				 // char "1"  		0x01
		 seg_a+seg_e+seg_d,              // char "2"  		0x02
		 seg_a+seg_d,                    // char "3"  		0x03
		 seg_f,                          // char "4"  		0x04
		 seg_a+seg_f+seg_d,              // char "5"  		0x05
		 seg_a+seg_f+seg_e+seg_d,        // char "6"  		0x06
		 seg_a,                    		 // char "7"  		0x07
		 seg_a+seg_f+seg_e+seg_d,  		 // char "8"  		0x08
		 seg_a+seg_f+seg_d,        		 // char "9"  		0x09
         0                               // char "NLL"  	0x16



};

static const uint8_t lcdNumber1_Low[]  ={0x0F,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber1_High[] ={0xA0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber2_Low[]  ={0x0F,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber2_High[] ={0xA0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber3_Low[]  ={0x0F,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber3_High[] ={0xA0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber4_Low[]  ={0x0F,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber4_High[] ={0xA0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber5_Low[]  ={0x0F,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber5_High[] ={0xA0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber6_Low[]  ={0x0F,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber6_High[] ={0xA0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber7_Low[]  ={0x0F,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber7_High[] ={0xA0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

static const uint8_t lcdNumber8_Low[]  ={0x0F,0x00,0x0C,0x04,0x06,0x06,0x0E,0x00,0x0E,0x06,0x0};
static const uint8_t lcdNumber8_High[] ={0xA0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0,0x0};

//"Er" ->digital positon '5''6'

static const uint8_t lcdNumber5_Low_E[]  ={0x06};
static const uint8_t lcdNumber5_High_E[] ={0x90};

static const uint8_t lcdNumber6_Low_r[]={0x0C};
static const uint8_t lcdNumber6_High_r[] ={0x0};



lcd_ref glcd_t; 

static void TM1723_Start(void);
static void TM1723_Stop(void);
static void TM1723_Write_OneByte(uint8_t data);
static void TIM1723_Write_Cmd(uint8_t cmd);
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat);


static void LCD_Number_OneTwo_Humidity(void);
static void LCD_Number_ThreeFour_Temperature(void);
static void LCD_Number_FiveSix_Hours(void);
static void LCD_Number_SevenEight_Minutes(void);
static void LCD_Wind_Icon(void);
static uint8_t Detecting_Fault_Code(void);
static void LCD_Fault_Numbers_Code(void);
static void LCD_Timer_Colon_Flicker(void);
static void Lcd_Display_Temp_Digital_Blink(void);



static uint8_t	ptc_error_flag ,fan_error_flag;
uint8_t Colon_Symbol     ;


/*****************************************************
 * 
 * Function Name:
 * Function:
 * Input Ref:
 * Return Ref:
 * 
******************************************************/
static void TM1723_Start(void)
{
  TM1723_STB_SetLow();
	
}
static void TM1723_Stop(void)
{
   TM1723_STB_SetHigh();

}

static void TM1723_Write_OneByte(uint8_t data)
{
	uint8_t i; 
	
	for(i=0;i<8;i++){
		
	TM1723_CLK_SetLow();
	 if(data & 0x01){
	     TM1723_DIO_SetHigh(); //TM1723 high of data to IC
		  
	 }
	 else{
	     TM1723_DIO_SetLow(); //TM1723 low level of data to IC
		  
	 }
   
    delay_us(100);
    data =data>>1;//
	 
	 TM1723_CLK_SetHigh();
	 //data =data>>1;//
	  delay_us(2);
	// data >>=1;//
	
  
     
 }

}
static void TIM1723_Write_Cmd(uint8_t cmd)
{
    TM1723_CLK_SetHigh();
	TM1723_Start();
	TM1723_Write_OneByte(cmd);

	TM1723_Stop();
 
}
static void TM1723_Write_Display_Data(uint8_t addr,uint8_t dat)
{
  
   TM1723_CLK_SetHigh();
   TM1723_STB_SetLow();
   TM1723_Write_OneByte(addr);
  
   TM1723_Write_OneByte(dat);
   
   TM1723_STB_SetHigh();

}



/*****************************************************
 * 
 * Function Name: void Lcd_Display_Detials(void)
 * Function: display content
 * Input Ref: NO
 * Return Ref: NO
 * 
******************************************************/
void Lcd_Display_Detials(void)
{
     static uint8_t fault_code;
     fault_code =  Detecting_Fault_Code();
	 
	 TIM1723_Write_Cmd(0x00); // 0x00 -> display setup model
	 TIM1723_Write_Cmd(0x40); // 0x40 ->write data to display of register
	 TIM1723_Write_Cmd(0x44); // 0x44 -> write fix of address model

   /* display humidity number 1, 2 */

   LCD_Number_OneTwo_Humidity();

  /* display temperature  number 3, 4 */
  if(gProcess_t.set_temp_confirm == 0){
    LCD_Number_ThreeFour_Temperature();
   }
   else{ //display key input set up temperature value 
     Lcd_Display_Temp_Digital_Blink();

   }


  if(fault_code ==0){
   /* display temperature  number 5, 6 */
   LCD_Number_FiveSix_Hours();


   /* display temperature  number 7, 8 */
   LCD_Number_SevenEight_Minutes();

 }
 else{
	LCD_Fault_Numbers_Code();

 }

   /* fan of degree numbers*/
   LCD_Wind_Icon();


   //open display
   TIM1723_Write_Cmd(LUM_VALUE);//(0x97);//(0x94);//(0x9B);


}

/*****************************************************
 * 
 * Function Name:  void LCD_Number_OneTwo_Humidity(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
******************************************************/
void LCD_Number_OneTwo_Humidity(void)
{
   //number '1'
  TM1723_Write_Display_Data(0xC4,(lcdNumber1_High[glcd_t.number1_high] + lcdNumber1_Low[glcd_t.number1_low]) & 0xff); //numbers : '1' addr: 0xC4

  //number '2'
  TM1723_Write_Display_Data(0xC5,(lcdNumber2_High[glcd_t.number2_high] + lcdNumber2_Low[glcd_t.number2_low]) & 0xff); //numbers : '2' addr: 0xC5
}
/*****************************************************************************
 * 
 * Function Name:  void LCD_Number_ThreeFour_Temperature(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Number_ThreeFour_Temperature(void)
{
  //number '3' 
  TM1723_Write_Display_Data(0xC2,(lcdNumber3_High[glcd_t.number3_high] + lcdNumber3_Low[glcd_t.number3_low] + TEMP_Symbol ) & 0xff); //numbers : '3' addr: 0xC2

 //number '4' 
 TM1723_Write_Display_Data(0xC3,(lcdNumber4_High[glcd_t.number4_high] + lcdNumber4_Low[glcd_t.number4_low] + HUMI_Symbol) & 0xff); //numbers : '4' addr: 0xC3


}
/*****************************************************************************
 * 
 * Function Name:  void LCD_Number_FiveSix_Hours(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
void LCD_Number_FiveSix_Hours(void)
{

  //judge icon 'dry' is on or off 
   static uint8_t ptc_symbol,plasma_symbol;
   if(ptc_state()==open){

      ptc_symbol = 1;
     
   }
   else{
     ptc_symbol = 0;
   }

   if(plasma_state() == open){
      plasma_symbol =1;
   }
   else{
	  plasma_symbol = 0;
   }
  



  //number '5' and 'ptc' icon
  TM1723_Write_Display_Data(0xC9,(lcdNumber5_High[glcd_t.number5_high] + lcdNumber5_Low[glcd_t.number5_low] + ptc_symbol ) & 0xff); 

 //number '6' 
 TM1723_Write_Display_Data(0xCA,(lcdNumber6_High[glcd_t.number6_high] + lcdNumber6_Low[glcd_t.number6_low] + plasma_symbol) & 0xff); 

}

/*****************************************************************************
 * 
 * Function Name:  static void LCD_Number_SevenEight_Minutes(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
static void LCD_Number_SevenEight_Minutes(void)
{

  static uint8_t ultrasonic_symbol;

     LCD_Timer_Colon_Flicker();
     if(ultrasonic_state() == open){

	     ultrasonic_symbol =1;

	  }
	  else{

	    ultrasonic_symbol =0;

	  }

	   //number '7' ":"
	  TM1723_Write_Display_Data(0xCB,(lcdNumber7_High[glcd_t.number7_high] + lcdNumber7_Low[glcd_t.number7_low] + Colon_Symbol ) & 0xff); //numbers : '1' addr: 0xC4

	  //number '8'
	  TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[glcd_t.number8_high] + lcdNumber8_Low[glcd_t.number8_low] + ultrasonic_symbol) & 0xff); //numbers : '2' addr: 0xC

}

/*****************************************************************************
 * 
 * Function Name: static LCD_Fault_Numbers_Code(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
static uint8_t Detecting_Fault_Code(void)
{
  

     if(ptc_error_state() == error){
		  ptc_error_flag = 1;
	 }
	 else{
		 ptc_error_flag =0;
	
	 }
	
	 if(fan_error_state()== error){
		fan_error_flag =1;

	 }
	 else{
	   fan_error_flag =0;
	
	 }

	 if(ptc_error_flag ==1 || fan_error_flag==1){

        return 1;
	 }
	 else
	    return 0;

	 

}
/*************************************************************************************
	*
	*Function Name: LCD_Fault_Numbers_Code(void)
	*Function : display error of code
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
static void LCD_Fault_Numbers_Code(void)
{

 LCD_Timer_Colon_Flicker();
 
 // display "E"
 TM1723_Write_Display_Data(0xC9,(lcdNumber5_Low_E[0]  + lcdNumber5_High_E[0] + DRY_Symbol ) & 0xff); //numbers : '3' addr: 0xC2

 //display 'r' 
 TM1723_Write_Display_Data(0xCA,(lcdNumber6_Low_r[0] + lcdNumber6_High_r[0] + PLASMA_Symbol) & 0xff); //numbers : '4' 

 //display error code "01"--ptc_warning , "02"--fan_warning

  //number '0' ":"
  TM1723_Write_Display_Data(0xCB,(lcdNumber7_High[0] + lcdNumber7_Low[0] + Colon_Symbol) & 0xff); //numbers : '1' addr: 0xC4

  //number '1' or '2'
 
  //"01" or "o2" blink
  if(glcd_t.gTimer_error_times < 1){
  	if(ptc_error_flag ==1){ 
    	TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[1] + lcdNumber8_Low[1] +BUG_Symbol) & 0xff); //numbers : '2' addr: 0xC
  	 }
	 else{
         	if(fan_error_flag ==1){
  	       		TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xff); //numbers : '2' addr: 0xC
        	}
		

	 }
  }
  else if(glcd_t.gTimer_error_times > 0 && glcd_t.gTimer_error_times < 2){

   if(fan_error_flag ==1 && ptc_error_flag ==1 ){
  	  TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[2] + lcdNumber8_Low[2] +BUG_Symbol) & 0xff); //numbers : '2' addr: 0xC
   }
   else{
   	  
   	   TM1723_Write_Display_Data(0xCC,(lcdNumber8_High[10] + lcdNumber8_Low[10] +BUG_Symbol) & 0xff); //numbers : '2' addr: 0xC

       
      
   }
  }
  else if(glcd_t.gTimer_error_times ==2 || glcd_t.gTimer_error_times > 2){
      glcd_t.gTimer_error_times =0;

  }
 


}
/*****************************************************************************
 * 
 * Function Name:  static void LCD_Fan_Icon(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
static void LCD_Wind_Icon(void)
{

   if(glcd_t.gTimer_fan_blink >9 && glcd_t.gTimer_fan_blink<20){ //open 
		
	   TM1723_Write_Display_Data(0xCE,T16_WIND_SPEED_ONE+T17_WIND_SPEED_TWO+T15+T9+T13);//display  wind icon
	   TM1723_Write_Display_Data(0xCF,T18_WIND_SPEED_FULL+T11);//display  wind icon	
	}
    else if(glcd_t.gTimer_fan_blink <10){ //close
		
	   TM1723_Write_Display_Data(0xCE,T16_WIND_SPEED_ONE+T17_WIND_SPEED_TWO+T15 +T10+T12+T14 );//display  wind icon
	   TM1723_Write_Display_Data(0xCF,T18_WIND_SPEED_FULL);//display  wind icon	

	}
	else if(glcd_t.gTimer_fan_blink > 19){
		glcd_t.gTimer_fan_blink=0;
	}
	  
}

/*****************************************************************************
 * 
 * Function Name:  static LCD_Timer_Colon_Flicker(void)
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
static void LCD_Timer_Colon_Flicker(void)
{
   if(glcd_t.gTimer_colon_blink < 1){

        Colon_Symbol = 0x01;
   }
   else if(glcd_t.gTimer_colon_blink >0 && glcd_t.gTimer_colon_blink < 2){

      Colon_Symbol = 0x0;

   }
   else if(glcd_t.gTimer_colon_blink ==2 || glcd_t.gTimer_colon_blink >2){

      glcd_t.gTimer_colon_blink =0;

   }

}

/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Temp_Digital_Blink(void)
	*Function : digital '3' '4' blink 3 times 
	*Input Ref: temperature of value 
	*Return Ref:NO
	*
*************************************************************************************/
static void Lcd_Display_Temp_Digital_Blink(void)
{
    static uint8_t times_blink;
	if(glcd_t.gTimer_lcd_blink  < 100){ //200ms

          //number '3' 
		  TM1723_Write_Display_Data(0xC2,(lcdNumber3_High[glcd_t.number3_high] + lcdNumber3_Low[glcd_t.number3_low] + TEMP_Symbol ) & 0xff); //numbers : '3' addr: 0xC2

		 //number '4' 
		 TM1723_Write_Display_Data(0xC3,(lcdNumber4_High[glcd_t.number4_high] + lcdNumber4_Low[glcd_t.number4_low] + HUMI_Symbol) & 0xff); //numbers : '4' addr: 0xC3

     }
	 else if(glcd_t.gTimer_lcd_blink  > 99 && glcd_t.gTimer_lcd_blink  < 201){ //lef off

		  //number '3' 
		  TM1723_Write_Display_Data(0xC2,(lcdNumber3_High[0x0A] + lcdNumber3_Low[0x0A] + TEMP_Symbol ) & 0xff); //numbers : '3' addr: 0xC2

		 //number '4' 
		 TM1723_Write_Display_Data(0xC3,(lcdNumber4_High[0x0A] + lcdNumber4_Low[0x0A] + HUMI_Symbol) & 0xff); //numbers : '4' addr: 0xC3

     }
	 else{
       times_blink ++ ;
	   glcd_t.gTimer_lcd_blink =0;

	 }


	 if(times_blink > 3){

	   times_blink =0 ;
       gProcess_t.set_temp_confirm = 0; //设置温度的值，完成，清零，回到正常温湿度传感器显示值
       gProcess_t.gTimer_run_dht11 = 70;

	 }




}
/*************************************************************************************
	*
	*Function Name: static void LCD_DisplayNumber_OneTwo_Icon_Handler(void)
	*Function : display wind icon
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void LCD_Display_Wind_Icon_Handler(void)
{
		TIM1723_Write_Cmd(0x00);
		TIM1723_Write_Cmd(0x40);
		TIM1723_Write_Cmd(0x44);

		TM1723_Write_Display_Data(0xC2,0x0);
		TM1723_Write_Display_Data(0xC3,0x0);
		TM1723_Write_Display_Data(0xC4,0x0);
		TM1723_Write_Display_Data(0xC5,0x0);
		TM1723_Write_Display_Data(0xC9,0x0);
		TM1723_Write_Display_Data(0xCA,0x0);
		TM1723_Write_Display_Data(0xCB,0x0);
		TM1723_Write_Display_Data(0xCC,0x0);


	//open display
	 TIM1723_Write_Cmd(LUM_VALUE);//(0x9B);

}
/*************************************************************************************
	*
	*Function Name: void Lcd_Display_Off(void)
	*Function : don't display any one
	*Input Ref:NO
	*Return Ref:NO
	*
*************************************************************************************/
void Lcd_Display_Off(void)
{

	 TIM1723_Write_Cmd(CloseDispTM1723);//(0x80);

}



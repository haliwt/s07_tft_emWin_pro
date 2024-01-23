#include "bsp_font.h"
#include "bsp.h"





const typFNT_GB16 font1616_temp[]={

	0x00,0x00,0x23,0xF8,0x12,0x08,0x12,0x08,0x83,0xF8,0x42,0x08,0x42,0x08,0x13,0xF8,
	0x10,0x00,0x27,0xFC,0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x00,0x00,/*"温",0*/
	0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,
	0x23,0xE0,0x20,0x00,0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E,/*"度",1*/

};

/*************************************************************************************************
	*
	*Functin Name:void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
	*Function :TFT screen display chinese of words
	*Input Ref: x, y start pointer ,fc---fonts color , bc --backgroud color,fonts lib. 
	*Return Ref:NO
	*
*************************************************************************************************/
void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
{
   uint8_t i,j;
   uint16_t k;
   uint16_t HZnum;
   uint16_t x0=x;
   HZnum=sizeof(font1616_temp)/sizeof(typFNT_GB16);	//自动统计汉字数目
   for (k=0;k<HZnum;k++) 
   {
       if((font1616_temp[k].Index[0]==*(s))&&(font1616_temp[k].Index[1]==*(s+1)))
       { 	
          // LCD_SetWindows(x,y,x+16-1,y+16-1);
		  LCD_Address_Set(x,y,x+16-1,y+16-1);
	   for(i=0;i<16*2;i++)
           {
		for(j=0;j<8;j++)
		{	
		     if(!mode) //非叠加模式：字体带有背景色，显示时会将原来显示的内容覆盖掉
		     {
			  if(font1616_temp[k].Msk[i]&(0x80>>j))
              {	
                  // Lcd_WriteData_16Bit(fc);
                  LCD_Write_Data(fc >> 8);
                  LCD_Write_Data(fc);
              }			  
              else 
              {
                //Lcd_WriteData_16Bit(bc);
                LCD_Write_Data(bc >> 8);
   				LCD_Write_Data(bc);
			  }
		     }
		     else //叠加模式：字体不带背景色，直接叠加显示到原来显示的内容上
		     {
			 // POINT_COLOR=fc;
			  if(font1616_temp[k].Msk[i]&(0x80>>j))						
                          {
                        //LCD_DrawPoint(x,y);//画一个点
                    TFT_DrawPoint(x,y,WHITE);
			  }
			  x++;
			  if((x-x0)==16)
			  {
			       x=x0;
			       y++;
			       break;
			  }
		     }
	        }
	    }
	 }				  	
	 continue;  //找到对应点阵字库立即退出，防止多个汉字重复取模带来影响
    }
   // LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);//恢复窗口为全屏 
   TFT_SetWindow(0,0,(LCD_Width-1),(LCD_Height-1));
}

 
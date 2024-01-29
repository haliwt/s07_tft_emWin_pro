#include "bsp_font.h"
#include "bsp.h"

#define  CMD_SetPixel	0x2C	     //填充像素

/***************************** ILI934 显示区域的起始坐标和总行列数 ***************************/
#define      ILI9341_DispWindow_X_Star		    0     //起始点的X坐标
#define      ILI9341_DispWindow_Y_Star		    0     //起始点的Y坐标


uint16_t LCD_X_LENGTH = 320;
uint16_t LCD_Y_LENGTH = 240;



//static uint16_t CurrentTextColor   = WHITE;//前景色
//static uint16_t CurrentBackColor   = BLACK;//背景色
//static uint32_t lcd_pow(uint8_t m, uint8_t n);





/*************************************************************************************************
	*
	*Functin Name:void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
	*Function :TFT screen display chinese of words
	*Input Ref: x, y start pointer ,fc---fonts color , bc --backgroud color,fonts lib. 
	*Return Ref:NO
	*
*************************************************************************************************/
#if 0
void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fc, uint16_t bc, uint8_t *s,uint8_t mode)
{
   uint8_t i,j;
   uint16_t k;
   uint16_t HZnum;
   uint16_t x0=x;
	#if 0
   HZnum=sizeof(font1616_temp)/sizeof(font1616_temp[0][0]);	//自动统计汉字数目
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
   #endif 
}
#endif 

/**************************************************************************************************************
*@brief TFT_display_char16_16_noBackColor
*@details 显示16x16的汉字(不带背景颜色，镂空)
*		  显示规则：一行一行显示，首先显示第一行的前八位，
*		  然后显示后八位，显示完成之后显示第二行，
*		  注意：数据取模时是低位在前高位在后（逆序），具体根
*		  据取模方向来确定
*@param[in] address:图片数据地址
*			startX：X起始坐标
*			startY：Y起始坐标
*			color：字体显示颜色
*@return void
*@author zx
*@date 2023-06-04
**************************************************************************************************************/
#if 0
void TFT_display_char16_16_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;
	for(column = 0; column < 16; column++) //2个字 1个字是16 
	{
		temp =* address;
	   for(tm = 8; tm > 0; tm--)//for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm, startY+ y ,color);
				 TFT_DrawPoint(startX+tm, startY+ y ,color);
			}
			
			temp >>= 1;
		}
		address++;
		temp =* address;
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+8, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
//		if(column>0 && column%2 == 0)//如果开启字体的高读会压缩到之前的一半
		y++;
		address++;
	}	

}
#endif 
/**************************************************************************************************************
*
*@brief TFT_display_char16_16_noBackColor
*@details 显示16x16的汉字(不带背景颜色，镂空)
*		  显示规则：一行一行显示，首先显示第一行的前八位，
*		  然后显示后八位，显示完成之后显示第二行，
*		  注意：数据取模时是低位在前高位在后（逆序），具体根
*		  据取模方向来确定
*@param[in] address:图片数据地址
*			startX：X起始坐标
*			startY：Y起始坐标
*			color：字体显示颜色
*@return void
*
**************************************************************************************************************/
#if 0
void TFT_display_char16_16_Tow_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;

	//the second words display 
	for(column = 0; column < 16; column++) //2个字 1个字是16 
	{
	   temp =*(address+32);
	   
	   for(tm = 8; tm > 0; tm--)//for(tm = 0; tm < 8; tm++)
	   {			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm, startY+ y ,color);
				 TFT_DrawPoint(startX+tm, startY+ y ,color);
			}
			
			temp >>= 1;
		}
	  
		address ++;
		temp =*(address+32);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+8, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
//		if(column>0 && column%2 == 0)//如果开启字体的高读会压缩到之前的一半
		y++;
		address++;
	}

	

}

/**************************************************************************************************************
*
*@brief TFT_display_char16_16_noBackColor
*@details 显示16x16的汉字(不带背景颜色，镂空)
*		  显示规则：一行一行显示，首先显示第一行的前八位，
*		  然后显示后八位，显示完成之后显示第二行，
*		  注意：数据取模时是低位在前高位在后（逆序），具体根
*		  据取模方向来确定
*@param[in] address:图片数据地址
*			startX：X起始坐标
*			startY：Y起始坐标
*			color：字体显示颜色
*@return void
*
**************************************************************************************************************/
void TFT_display_char16_16_Three_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;

	//the second words display 
	for(column = 0; column < 16; column++) //2个字 1个字是16 
	{
	   temp =*(address+64);
	   
	   for(tm = 8; tm > 0; tm--)//for(tm = 0; tm < 8; tm++)
	   {			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm, startY+ y ,color);
				 TFT_DrawPoint(startX+tm, startY+ y ,color);
			}
			
			temp >>= 1;
		}
	  
		address ++;
		temp =*(address+64);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+8, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
//		if(column>0 && column%2 == 0)//如果开启字体的高读会压缩到之前的一半
		y++;
		address++;
	}

	

}

/**************************************************************************************************************
*
*@brief TFT_display_char16_16_noBackColor
*@details 显示16x16的汉字(不带背景颜色，镂空)
*		  显示规则：一行一行显示，首先显示第一行的前八位，
*		  然后显示后八位，显示完成之后显示第二行，
*		  注意：数据取模时是低位在前高位在后（逆序），具体根
*		  据取模方向来确定
*@param[in] address:图片数据地址
*			startX：X起始坐标
*			startY：Y起始坐标
*			color：字体显示颜色
*@return void
*
**************************************************************************************************************/
void TFT_display_char16_16_Four_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;

	
	//the second words display 
	for(column = 0; column < 16; column++) //2个字 1个字是16 
	{
	   temp =*(address+96);
	   
	   for(tm = 8; tm > 0; tm--)//for(tm = 0; tm < 8; tm++)
	   {			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm, startY+ y ,color);
				 TFT_DrawPoint(startX+tm, startY+ y ,color);
			}
			
			temp >>= 1;
		}
	  
		address ++;
		temp =*(address+96);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+8, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
//		if(column>0 && column%2 == 0)//如果开启字体的高读会压缩到之前的一半
		y++;
		address++;
	}

	

}

#endif 
/****************************************************************************************
	*@brief TFT_display_char16_16
	*@details 显示16x16的汉字
	*@param[in] address:图片数据地址
	*			startX：X起始坐标
	*			startY：Y起始坐标
	*			textColor：字体显示颜色
	*			backgroundColor:背景色
	*@return void
	*@author zx
	*@date 2023-06-04
******************************************************************************************/
void TFT_display_char16_16(const uint8_t *address ,uint16_t startX,uint16_t startY,
							uint16_t textColor, uint16_t backgroundColor)
{
	unsigned int column;
	unsigned char tm=0,temp;

	//TFT_SetWindows(startX, startY, 16, 16);
    TFT_SetWindow(startX, startY, 32, 32);
	
	for(column = 0; column < 32; column++)  //column loop
	{
		temp =* address;
		for(tm = 8; tm > 0; tm--)//for(tm = 0; tm < 8; tm++)
		{
			if(temp&0x01)
			{
				LCD_Write_Data(textColor>>8);//TFT_SEND_DATA(textColor>>8);
				LCD_Write_Data(textColor);//TFT_SEND_DATA(textColor);
			}
			else 
			{
				LCD_Write_Data(backgroundColor>>8);//TFT_SEND_DATA(backgroundColor>>8);
				LCD_Write_Data(backgroundColor);//TFT_SEND_DATA(backgroundColor);
			}
			temp >>= 1;
		}
		address++;
	}
} 

/**************************************************************************************************************
*@brief TFT_display_char16_16_noBackColor
*@details 显示16x16的汉字(不带背景颜色，镂空)
*		  显示规则：一行一行显示，首先显示第一行的前八位，
*		  然后显示后八位，显示完成之后显示第二行，
*		  注意：数据取模时是低位在前高位在后（逆序），具体根
*		  据取模方向来确定
*@param[in] address:图片数据地址
*			startX：X起始坐标
*			startY：Y起始坐标
*			color：字体显示颜色
*@return void
*@author zx
*@date 2023-06-04
**************************************************************************************************************/
#if 0
void TFT_display_char16_16_English_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;
	for(column = 0; column < 16; column++) //2个字 1个字是16 
	{
		temp =* address;
	   for(tm = 8; tm > 0; tm--)//for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm, startY+ y ,color);
				 TFT_DrawPoint(startX+tm, startY+ y ,color);
			}
			
			temp >>= 1;
		}
//		if(column>0 && column%2 == 0)//如果开启字体的高读会压缩到之前的一半
		y++;
		address++;
	}	

}

#endif 


/**************************************************************************************************************
*@brief TFT_display_char48_48_noBackColor
*@details 显示16x16的汉字(不带背景颜色，镂空)
*		  显示规则：一行一行显示，首先显示第一行的前八位，
*		  然后显示后八位，显示完成之后显示第二行，
*		  注意：数据取模时是低位在前高位在后（逆序），具体根
*		  据取模方向来确定
*@param[in] address:图片数据地址
*			startX：X起始坐标
*			startY：Y起始坐标
*			color：字体显示颜色
*@return void
*@author zx
*@date 2023-06-04
**************************************************************************************************************/
#if 0
void TFT_display_char32_32_English_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;
	for(column = 0; column < 16; column++) //2个字 1个字是16 
	{
	   temp =* address;
	   for(tm = 8; tm > 0; tm--)//for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm, startY+ y ,color);
				 TFT_DrawPoint(startX+tm, startY+ y ,color);
			}
			
			temp >>= 1;
		}

	    address++;
		temp =* address;
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+8, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
       //2
		address++;
		temp =*(address+32);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+9, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
		address++;
		temp =* (address+32);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+17, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
        //3
		address++;
		temp =* (address+64);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+18, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
		address++;
		temp =*(address+64);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+26, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
		//4
		address++;
		temp =* (address+96);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+27, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
		address++;
		temp =*(address+96);
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+35, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
		
		
			 
		
//		if(column>0 && column%2 == 0)//如果开启字体的高读会压缩到之前的一半
		y++;
		address++;
	}	

}

void TFT_display_char32_32_OneEnglish_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;
	for(column = 0; column < 32; column++) //2个字 1个字是16 
	{
	  temp =* address;
	   for(tm = 8; tm > 0; tm--)//for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm, startY+ y ,color);
				 TFT_DrawPoint(startX+tm, startY+ y ,color);
			}
			
			temp >>= 1;
		}
		address++;
		temp =* address;
		for(tm = 8; tm > 0; tm--) //for(tm = 0; tm < 8; tm++)
		{			
			if(temp&0x01)
			{
				//TFT_display_point(startX+ tm+8, startY+ y ,color);
				TFT_DrawPoint(startX+tm+8, startY+ y ,color);
			}
			
			temp >>= 1;
			 
		}
		
//		if(column>0 && column%2 == 0)//如果开启字体的高读会压缩到之前的一半
		y++;
		address++;
	}	

}
#endif 



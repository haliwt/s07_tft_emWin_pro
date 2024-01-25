#include "bsp_font.h"
#include "bsp.h"

#define  CMD_SetPixel	0x2C	     //填充像素

/***************************** ILI934 显示区域的起始坐标和总行列数 ***************************/
#define      ILI9341_DispWindow_X_Star		    0     //起始点的X坐标
#define      ILI9341_DispWindow_Y_Star		    0     //起始点的Y坐标


uint16_t LCD_X_LENGTH = 320;
uint16_t LCD_Y_LENGTH = 240;


static sFONT *LCD_Currentfonts = &Font8x16;  //英文字体
static uint16_t CurrentTextColor   = WHITE;//前景色
static uint16_t CurrentBackColor   = BLACK;//背景色
static uint32_t lcd_pow(uint8_t m, uint8_t n);


/**
  * @brief  获取当前字体类型
  * @param  None.
  * @retval 返回当前字体类型
  */
sFONT *LCD_GetFont(void)
{
  return LCD_Currentfonts;
}




/*************************************************************************************************
	*
	*Functin Name:void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode)
	*Function :TFT screen display chinese of words
	*Input Ref: x, y start pointer ,fc---fonts color , bc --backgroud color,fonts lib. 
	*Return Ref:NO
	*
*************************************************************************************************/
#if 1
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
void TFT_display_char16_16_Tow_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;

	#if 0
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
	#endif 
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

/***********************************************************************************
 * @brief  在 ILI9341 显示器上显示一个英文字符
 * @param  usX ：在特定扫描方向下字符的起始X坐标
 * @param  usY ：在特定扫描方向下该点的起始Y坐标
 * @param  cChar ：要显示的英文字符
 * @note 可使用LCD_SetBackColor、LCD_SetTextColor、LCD_SetColors函数设置颜色
 * @retval 无
 ************************************************************************************/
void TFT_DispChar_EN ( uint16_t usX, uint16_t usY, const char cChar )
{
	uint8_t  byteCount, bitCount,fontLength;	
	uint16_t ucRelativePositon;
	uint8_t *Pfont;
	
	//对ascii码表偏移（字模表不包含ASCII表的前32个非图形符号）
	ucRelativePositon = cChar - ' ';
	
	//每个字模的字节数
	fontLength = (LCD_Currentfonts->Width*LCD_Currentfonts->Height)/8;
		
	//字模首地址
	/*ascii码表偏移值乘以每个字模的字节数，求出字模的偏移位置*/
	Pfont = (uint8_t *)&LCD_Currentfonts->table[ucRelativePositon * fontLength];
	
	//设置显示窗口
	//ILI9341_OpenWindow ( usX, usY, LCD_Currentfonts->Width, LCD_Currentfonts->Height);
	TFT_SetWindow( usX, usY, LCD_Currentfonts->Width, LCD_Currentfonts->Height);
	
	LCD_Write_Cmd(CMD_SetPixel);//ILI9341_Write_Cmd ( CMD_SetPixel );			

	//按字节读取字模数据
	//由于前面直接设置了显示窗口，显示数据会自动换行
	for ( byteCount = 0; byteCount < fontLength; byteCount++ )
	{
			//一位一位处理要显示的颜色
			for ( bitCount = 0; bitCount < 8; bitCount++ )
			{
					if ( Pfont[byteCount] & (0x80>>bitCount) ){
						//ILI9341_Write_Data ( CurrentTextColor );	
						LCD_Write_Data(CurrentTextColor);
					}	
					else
						LCD_Write_Data(CurrentBackColor);//ILI9341_Write_Data ( CurrentBackColor );
			}	
	}	
}



/**
 * @brief  在 ILI9341 显示器上显示英文字符串
 * @param  usX ：在特定扫描方向下字符的起始X坐标
 * @param  usY ：在特定扫描方向下字符的起始Y坐标
 * @param  pStr ：要显示的英文字符串的首地址
 * @note 可使用LCD_SetBackColor、LCD_SetTextColor、LCD_SetColors函数设置颜色
 * @retval 无
 */
void LCD_DispString_EN ( 	uint16_t usX ,uint16_t usY,  char * pStr )
{
	while ( * pStr != '\0' )
	{
		if ( ( usX - ILI9341_DispWindow_X_Star + LCD_Currentfonts->Width ) > LCD_X_LENGTH  )
		{
			usX = ILI9341_DispWindow_X_Star;
			usY += LCD_Currentfonts->Height;
		}
		
		if ( ( usY - ILI9341_DispWindow_Y_Star + LCD_Currentfonts->Height ) > LCD_Y_LENGTH )
		{
			usX = ILI9341_DispWindow_X_Star;
			usY = ILI9341_DispWindow_Y_Star;
		}
		
		TFT_DispChar_EN ( usX, usY, * pStr);
		
		pStr ++;
		
		usX += LCD_Currentfonts->Width;
		
	}
	
}

/**
 * @brief  在 ILI9341 显示器上显示英文字符串
 * @param  line ：在特定扫描方向下字符串的起始Y坐标
  *   本参数可使用宏LINE(0)、LINE(1)等方式指定文字坐标，
  *   宏LINE(x)会根据当前选择的字体来计算Y坐标值。
	*		显示中文且使用LINE宏时，需要把英文字体设置成Font8x16
 * @param  pStr ：要显示的英文字符串的首地址
 * @note 可使用LCD_SetBackColor、LCD_SetTextColor、LCD_SetColors函数设置颜色
 * @retval 无
 */
void LCD_DispStringLine_EN (  uint16_t line,  char * pStr )
{
	uint16_t usX = 0;
	
	while ( * pStr != '\0' )
	{
		if ( ( usX - ILI9341_DispWindow_X_Star + LCD_Currentfonts->Width ) > LCD_X_LENGTH )
		{
			usX = ILI9341_DispWindow_X_Star;
			line += LCD_Currentfonts->Height;
		}
		
		if ( ( line - ILI9341_DispWindow_Y_Star + LCD_Currentfonts->Height ) > LCD_Y_LENGTH )
		{
			usX = ILI9341_DispWindow_X_Star;
			line = ILI9341_DispWindow_Y_Star;
		}
		
		//ILI9341_DispChar_EN ( usX, line, * pStr);
		TFT_DispChar_EN(usX, line, * pStr);
		pStr ++;
		
		usX += LCD_Currentfonts->Width;
		
	}
	
}

/********************************************************************
*
* name         : 
* description  : 绘制字符串，可设置前景色和背景色
* Input        : 字体宽度，高度，字符，字符颜色，背景颜色
* Return       : 
*
********************************************************************/
void St7789DrawChar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *str, uint16_t forecolor, uint16_t backcolor)
{
    uint32_t i, j;
    uint8_t  mask;
    
   // SetWindow( x, y, x + w - 1, y + h -1);
	
    TFT_SetWindow(x, y, x + w - 1, y + h -1);
    for(i = 0; i < h; i++)
    {
        mask = 0x80;//取模时：阴码，高位在前
        for(j = 0; j < w; j++)
        {
            if(*str & mask){
                //Write16Bits(forecolor);
                LCD_Write_Data(forecolor >>8);
				 LCD_Write_Data(forecolor );

            }
            else{
               // Write16Bits(backcolor);
                LCD_Write_Data(backcolor >>8);
			    LCD_Write_Data(backcolor);

            }
            
            mask >>= 1;
            if(mask == 0)
            {
                mask = 0x80;
                str++;
            }
        }
        
        if(mask != 0x80)
            str++;
    }
}


/**********************************************
函数名：LCD_write_english
功能：选定Lcd上写一个英文或数字
入口参数：data 要写的字符
          color 字符的颜色
          xcolor 字符的背景色
          size  字体的大小
返回值：无
***********************************************/
void LCD_write_english(int8_t data,uint16_t color,uint16_t xcolor ,uint8_t mode)//写字符
{
//  uint8_t i=0,j=0,n=0;
//  uint8_t avl=0;
//  data -=32;                     
//  for (i=0;i<120;i++) //为 20x40字库      
//  {     
//    avl=english[data][i];         
//    for (j=0;j<8;j++)           
//    {
//      n++;
//      if(avl&0x80)LCD_WriteOneDot(color);        
//      else if(mode==0) LCD_WriteOneDot(xcolor);
//      avl<<=1;
//      if(n>19) {
//        n=0;
//        break;
//      }//部分字体如英文20*40，形成的字库3个8位一组，每一组最后4位不显示，用该语句进行判断有几位不需要显示
//    }     
//   }
}
/******************************************************************************************************
*
//在指定位置显示一个字符,包括部分字符
//函数说明：显示字符
//入口数据：x,y    起点坐标
//		chr    要显示的字符
//		mode   1叠加方式  0非叠加方式
*
******************************************************************************************************/
void TFT_ShowChar(uint16_t x,uint16_t y,uint8_t chr,uint8_t fw,uint8_t fh,uint8_t mode)
{
    uint8_t temp, t, tbit;
    uint8_t y0=y;
    uint8_t *p;	
	uint16_t LCD_HEIGHT,LCD_WIDTH,color,csize;

	LCD_WIDTH =320;
	LCD_HEIGHT = 240;
	
	
	//csize=(fh/8+((fh%8)?1:0))*fw/2;// 得到字体一个字符对应点阵集所占的字节数	
 
    chr=chr-' ';//得到偏移后的值
 
    //if(fw==6&&fh==8)        p = (uint8_t *)asc2_0608[chr];	//调用0608ascii字体
    //else if(fw==6&&fh==12)  p = (uint8_t *)asc2_0612[chr];	//调用0612ascii字体
    //else if(fw==8&&fh==16)  p = (uint8_t *)asc2_0816[chr];	//调用0612ascii字体
    if(fw==12&&fh==24){
		p = (uint8_t *)asc2_1224[chr];   //调用1224ascii字体
        csize =36;
    }
    else if(fw==24 && fh ==48){
		p= (uint8_t *)font2448_no[chr];
		csize =96;

    }
    else return;	//没有的字库
	for(t = 0; t < csize; t++)	/*遍历打印所有像素点到LCD */
	{   
		temp = p[t];
		for(tbit = 0; tbit < 8; tbit++)	/* 打印一个像素点到液晶 */
		{	
			
			
			if(temp & 0x80)	color = WHITE;
			else if(0 == mode)	color = BLACK;
			else color = BLACK;
			TFT_DrawPoint(x, y,color );
			
			temp <<= 1;			
			y++;
			
			if(y >= LCD_HEIGHT) return;		/* 超区域了 */
 
			if((y - y0) == fh){
				y = y0;
				x++;
				if(x >= LCD_WIDTH)	return;	/* 超区域了 */
				break;
			}
		}  	 
	}  	  
}


/**
 * @brief       平方函数, m^n
 * @param       m: 底数
 * @param       n: 指数
 * @retval      m的n次方
 */
static uint32_t lcd_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;

    while (n--)result *= m;

    return result;
}



//显示数字
//x,y :起点坐标
//len :数字的位数
//fw:字宽
//fh:字高
//num:数值(0~4294967295);
void TFT_ShowNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint8_t fw,uint8_t fh)
{
    uint8_t t,temp;
    uint8_t enshow=0;
    for(t=0; t<len; t++)
    {
       temp=(num/lcd_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                TFT_ShowChar(x+(fw)*t,y,' ',fw,fh,0);
                continue;
            }
            else
                enshow=1;
        }
        TFT_ShowChar(x+(fw)*t,y,temp+'0',fw,fh,0);
    }
}




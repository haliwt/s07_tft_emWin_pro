#include "bsp.h"
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
	static uint16_t LCD_HEIGHT,LCD_WIDTH,color,csize;

	LCD_WIDTH =320;
	LCD_HEIGHT = 240;
	
	
	csize=(fh/8+((fh%8)?1:0))*fw/2;// 得到字体一个字符对应点阵集所占的字节数	
 
    chr=chr-' ';//得到偏移后的值
 
    //if(fw==6&&fh==8)        p = (uint8_t *)asc2_0608[chr];	//调用0608ascii字体
    //else if(fw==6&&fh==12)  p = (uint8_t *)asc2_0612[chr];	//调用0612ascii字体
    //else if(fw==8&&fh==16)  p = (uint8_t *)asc2_0816[chr];	//调用0612ascii字体
    if(fw==12&&fh==24){
	//	p = (uint8_t *)asc2_1224[chr];   //调用1224ascii字体
        csize =36;
    }
    else if(fw==48 && fh ==48){
		p= (uint8_t *)font4848_no[chr];
		csize =144;

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
			y++; //
			
			if(y >= LCD_HEIGHT){
				pro_t.lcd_over_height_flag;
				return;		/* 超区域了 */

			}
 
			if((y - y0) == fh){
				y = y0;
				x++;
				if(x >= LCD_WIDTH){
                    pro_t.lcd_over_width_flag =1;
					return;	/* 超区域了 */

				}
				break;
			}
		}  	 
	}  	  
}


/******************************************************************************************************
*
*Function Name:void TFT_ShowChar_144(uint16_t x,uint16_t y,uint8_t num,uint8_t mode)
*Function :
	//在指定位置显示一个字符,包括部分字符
	//函数说明：显示字符
*Input Ref：x,y    起点坐标
	//		chr    要显示的字符
	//		mode   1叠加方式  0非叠加方式
*Return Ref: NO
*
******************************************************************************************************/
void TFT_ShowChar_144(uint16_t x,uint16_t y,uint8_t num,uint8_t mode)
{
    uint8_t temp, t, tbit;
    uint8_t x0=x;
    
	static uint16_t LCD_HEIGHT,LCD_WIDTH,color,csize;

	LCD_WIDTH =320;
	LCD_HEIGHT = 240;
	
   
	for(t = 0; t < 144; t++)	/*遍历打印所有像素点到LCD */
	{   
	
		temp = font4848_no[num][t]; 
		
		for(tbit = 0; tbit < 8; tbit++)	/* 打印一个像素点到液晶 */
		{	
			
			
			if(temp & 0x80)	color = WHITE;
			else if(0 == mode)	color = BLACK;
			else color = BLACK;
			TFT_DrawPoint(x, y,color );
			
			temp <<= 1;			
			//y++; // 垂直扫描
			x++;//水平扫描

			if(x >= LCD_WIDTH){
                    pro_t.lcd_over_width_flag =1;
					return;	/* 超区域了 */

			}
			
			if((x - x0) == 24){
				x = x0;
				y++;
				
			    if(y >= LCD_HEIGHT){
				pro_t.lcd_over_height_flag=1;
				return;		/* 超区域了 */

			     }
 
				break;
			}
		}  	 
	}  
  
	
}

/******************************************************************************************************
*
*Function Name:void TFT_ShowChar_144(uint16_t x,uint16_t y,uint8_t num,uint8_t mode)
*Function :
	//在指定位置显示一个字符,包括部分字符
	//函数说明：显示字符
*Input Ref：x,y    起点坐标
	//		chr    要显示的字符
	//		mode   1叠加方式  0非叠加方式
*Return Ref: NO
*
******************************************************************************************************/
void TFT_ShowChar_256(uint16_t x,uint16_t y,uint8_t num,uint8_t mode)
{
    uint16_t temp, t, tbit;
    uint16_t x0=x;
    
	static uint16_t LCD_HEIGHT,LCD_WIDTH,color,csize;

	LCD_WIDTH =320;
	LCD_HEIGHT = 240;
	
   
	for(t = 0; t < 256; t++)	/*遍历打印所有像素点到LCD */
	{   
	
		temp = font6464_no[num][t]; 
		
		for(tbit = 0; tbit < 8; tbit++)	/* 打印一个像素点到液晶 */
		{	
			
			
			if(temp & 0x80)	color = WHITE;
			else if(0 == mode)	color = BLACK;
			else color = BLACK;
			TFT_DrawPoint(x, y,color );
			
			temp <<= 1;			
			//y++; // 垂直扫描
			x++;//水平扫描

			if(x >= LCD_WIDTH){
                    pro_t.lcd_over_width_flag =1;
					return;	/* 超区域了 */

			}
			
			if((x - x0) == 32){
				x = x0;
				y++;
				
			    if(y >= LCD_HEIGHT){
				pro_t.lcd_over_height_flag=1;
				return;		/* 超区域了 */

			     }
 
				break;
			}
		}  	 
	}  
  
	
}


void TFT_ShowChar_576(uint16_t x,uint16_t y,uint8_t num,uint8_t mode)
{
    uint16_t temp, t, tbit;
    uint16_t x0=x;
    
	static uint16_t LCD_HEIGHT,LCD_WIDTH,color,csize;

	LCD_WIDTH =320;
	LCD_HEIGHT = 240;
	
   
	for(t = 0; t < 576; t++)	/*遍历打印所有像素点到LCD */
	{   
	
		temp = font9696_no[num][t]; 
		
		for(tbit = 0; tbit < 8; tbit++)	/* 打印一个像素点到液晶 */
		{	
			
			
			if(temp & 0x80)	color = WHITE;
			else if(0 == mode)	color = BLACK;
			else color = BLACK;
			TFT_DrawPoint(x, y,color );
			
			temp <<= 1;			
			//y++; // 垂直扫描
			x++;//水平扫描

			if(x >= LCD_WIDTH){
                    pro_t.lcd_over_width_flag =1;
					return;	/* 超区域了 */

			}
			
			if((x - x0) == 48){
				x = x0;
				y++;
				
			    if(y >= LCD_HEIGHT){
				pro_t.lcd_over_height_flag=1;
				return;		/* 超区域了 */

			     }
 
				break;
			}
		}  	 
	}  
  
	
}


/****************************************************************************************
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

/**************************************************************************************************************
*
*Function Name:void TFT_display_char32_32_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
*Function: 显示16x16的汉字(不带背景颜色，镂空)
*		  显示规则：一行一行显示，首先显示第一行的前八位，
*		  然后显示后八位，显示完成之后显示第二行，
*Input Ref:address:图片数据地址
*			startX：X起始坐标
*			startY：Y起始坐标
*			color：字体显示颜色
*Return Ref:NO
*
**************************************************************************************************************/
void TFT_display_char32_32_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color)
{

	uint16_t column;
	uint8_t tm=0;
	uint8_t temp;
	uint16_t x = 0;
	uint16_t y = 0;
	for(column = 0; column < 128; column++) //2个字 1个字是16 
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
/****************************************************************************************
	*
	*Function  Name :void TFT_Disp_Humidity_32_32_onBlack(uint16_t x,uint16_t y,uint8_t num)
	*Function:
	*
	*
****************************************************************************************/
void TFT_Disp_Humidity_32_32_onBlack(uint16_t x,uint16_t y,uint8_t num)
{
    uint16_t temp, t, tbit,mode;
    uint16_t x0=x;
    mode =0;
	static uint16_t LCD_HEIGHT,LCD_WIDTH,color,csize;

	LCD_WIDTH =320;
	LCD_HEIGHT = 240;
	
   
	for(t = 0; t < 128; t++)	/*遍历打印所有像素点到LCD */
	{   
	
		temp = font3232_humidity[num][t]; 
		
		for(tbit = 0; tbit < 8; tbit++)	/* 打印一个像素点到液晶 */
		{	
			
			
			if(temp & 0x80)	color = WHITE;
			else if(0 == mode)	color = BLACK;
			else color = BLACK;
			TFT_DrawPoint(x, y,color );
			
			temp <<= 1;			
			//y++; // 垂直扫描
			x++;//水平扫描

			if(x >= LCD_Width){
                    pro_t.lcd_over_width_flag =1;
					return;	/* 超区域了 */

			}
			
			if((x - x0) == 32){
				x = x0;
				y++;
				
			    if(y >= LCD_Height){
				pro_t.lcd_over_height_flag=1;
				return;		/* 超区域了 */

			     }
 
				break;
			}
		}  	 
	}  
}
/****************************************************************************************
	*
	*Function  Name :void TFT_Disp_Humidity_32_32_onBlack(uint16_t x,uint16_t y,uint8_t num)
	*Function:
	*
	*
****************************************************************************************/
void TFT_Disp_Humidity_24_24_onBlack(uint16_t x,uint16_t y,uint8_t num)
{
    uint16_t temp, t, tbit,mode;
    uint16_t x0=x;
    mode =0;
	static uint16_t LCD_HEIGHT,LCD_WIDTH,color,csize;

	LCD_WIDTH =320;
	LCD_HEIGHT = 240;
	
   
	for(t = 0; t < 72; t++)	/*遍历打印所有像素点到LCD */
	{   
	
		temp = font2424_humidity[num][t]; 
		
		for(tbit = 0; tbit < 8; tbit++)	/* 打印一个像素点到液晶 */
		{	
			
			
			if(temp & 0x80)	color = WHITE;
			else if(0 == mode)	color = BLACK;
			else color = BLACK;
			TFT_DrawPoint(x, y,color );
			
			temp <<= 1;			
			//y++; // 垂直扫描
			x++;//水平扫描

			if(x >= LCD_Width){
                    pro_t.lcd_over_width_flag =1;
					return;	/* 超区域了 */

			}
			
			if((x - x0) == 24){
				x = x0;
				y++;
				
			    if(y >= LCD_Height){
				pro_t.lcd_over_height_flag=1;
				return;		/* 超区域了 */

			     }
 
				break;
			}
		}  	 
	}  

}
/****************************************************************************************
	*
	*Function  Name :void TFT_Disp_WorksTime_24_24_onBlack(uint16_t x,uint16_t y,uint8_t num)
	*Function:
	*
	*
****************************************************************************************/
void TFT_Disp_WorksTime_24_24_onBlack(uint16_t x,uint16_t y,uint8_t num)
{
    uint16_t temp, t, tbit,mode;
    uint16_t x0=x;
    mode =0;
	static uint16_t color;

	for(t = 0; t < 72; t++)	/*遍历打印所有像素点到LCD */
	{   
	
		temp = font2424_works_time[num][t]; 
		
		for(tbit = 0; tbit < 8; tbit++)	/* 打印一个像素点到液晶 */
		{	
			
			
			if(temp & 0x80)	color = WHITE;
			else if(0 == mode)	color = BLACK;
			else color = BLACK;
			TFT_DrawPoint(x, y,color );
			
			temp <<= 1;			
			//y++; // 垂直扫描
			x++;//水平扫描

			if(x >= LCD_Width){
                    pro_t.lcd_over_width_flag =1;
					return;	/* 超区域了 */

			}
			
			if((x - x0) == 24){
				x = x0;
				y++;
				
			    if(y >= LCD_Height){
				pro_t.lcd_over_height_flag=1;
				return;		/* 超区域了 */

			     }
 
				break;
			}
		}  	 
	}  

}

/****************************************************************************************
	*
	*Function  Name :void TFT_Disp_Temp_24_24_onBlack(uint16_t x,uint16_t y,uint8_t num)
	*Function:
	*Input Ref:NO
	*Return Ref:NO
	*
****************************************************************************************/
void TFT_Disp_Temp_24_24_onBlack(uint16_t x,uint16_t y,uint8_t num)
{
    uint16_t temp, t, tbit,mode;
    uint16_t x0=x;
    mode =0;
	static uint16_t color;

	for(t = 0; t < 72; t++)	/*遍历打印所有像素点到LCD */
	{   
	
		temp = font2424_temp[num][t]; 
		
		for(tbit = 0; tbit < 8; tbit++)	/* 打印一个像素点到液晶 */
		{	
			
			
			if(temp & 0x80)	color = WHITE;
			else if(0 == mode)	color = BLACK;
			else color = BLACK;
			TFT_DrawPoint(x, y,color );
			
			temp <<= 1;			
			//y++; // 垂直扫描
			x++;//水平扫描

			if(x >= LCD_Width){
                    pro_t.lcd_over_width_flag =1;
					return;	/* 超区域了 */

			}
			
			if((x - x0) == 24){
				x = x0;
				y++;
				
			    if(y >= LCD_Height){
				pro_t.lcd_over_height_flag=1;
				return;		/* 超区域了 */

			     }
 
				break;
			}
		}  	 
	}  

}


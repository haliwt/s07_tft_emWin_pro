#include "bsp_lcd_gui.h"
#include "bsp.h"
#include "bsp_tft_font.h"

uint16_t BACK_COLOR=BLACK;
uint16_t  POINT_COLOR=WHITE;


static void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);


/***********************************************************************
 *
 * Function Name: void TFT_Display_Handler(void)
 * Function: TFT LCD 显示全部的内容
 * Inpurt Ref: NO           
 * Return Ref: NO 
 *
************************************************************************/
void TFT_Display_Handler(void)
{

    
    TFT_Display_Temp_Symbol();

	TFT_Display_Humidity_Symbol();
	
	lcd_draw_rectangle(157,35,163,110,WHITE);
	TFT_St7789_FillBlock(157,35,6,75,WHITE);

	TFT_Display_WorksTime();

   //temperature value 
   //TFT_ShowChar_576(10,5,0,0); //位移是48
   //TFT_ShowChar_576(58,5,4,0);
  // TFT_Disp_Numbers_110_110(10,5,0);
  /// TFT_Disp_Numbers_110_110(65,5,3);
   TFT_Disp_Numbers_Pic_414(10,40,0);
   TFT_Disp_Numbers_Pic_414(70,40,3);
   //huimidity value
   //TFT_ShowChar_576(174,5,1,0);
   //TFT_ShowChar_576(222,5,3,0);
  // TFT_Disp_Numbers_110_110(174,5,1);
  // TFT_Disp_Numbers_110_110(229,5,2);
   TFT_Disp_Numbers_Pic_414(173,40,4);
   TFT_Disp_Numbers_Pic_414(233,40,2);
 


}

/***********************************************************************************************
	*
	*Function Name:void TFT_Display_Temp_Symbol(void)
	*Function : special TFT of itme
	*Input: NO
	*Return: NO 
	*
***********************************************************************************************/
void TFT_Display_Temp_Symbol(void)
{

   

	TFT_Disp_Temp_Symbol_24_24(122,40); //temp symbol 
#if TFT_DISP_TEMP_24
	TFT_Disp_Temp_24_24_onBlack(122,10,2); //temp symbol 

	TFT_Disp_Temp_24_24_onBlack(102,100,0);
	TFT_Disp_Temp_24_24_onBlack(126,100,1);
#else
	 TFT_Disp_Temp_20_20(111,90,0);
	 TFT_Disp_Temp_20_20(131,90,1);
#endif 
}


void TFT_Display_Humidity_Symbol(void)
{

    TFT_Disp_Humidity_Symbol_24_24(286,40);
    
#if TFT_DISP_TEMP_24 
	TFT_Disp_Humidity_24_24_onBlack(286,10,2); //humidity symbol %

    TFT_Disp_Humidity_24_24_onBlack(268,100,0);
    TFT_Disp_Humidity_24_24_onBlack(292,100,1);
#else
    TFT_Disp_Humidity_20_20(275,90,0);
	TFT_Disp_Humidity_20_20(295,90,1);

#endif 


}
void TFT_Display_WorksTime(void)
{
    //display works of words of chines 
    TFT_Disp_WorksTime_24_24_onBlack(112,150,0);//works one "工"
	TFT_Disp_WorksTime_24_24_onBlack(136,150,1);//
	TFT_Disp_WorksTime_24_24_onBlack(160,150,2);//
	TFT_Disp_WorksTime_24_24_onBlack(184,150,3);//
	
	//works time value
	
	TFT_Disp_WorkTime_Value_48_48_onBlack(112,185,2);
	TFT_Disp_WorkTime_Value_48_48_onBlack(136,185,1);
	TFT_Disp_WorkTime_Value_48_48_onBlack(160,180,10); //时间分割符号
	TFT_Disp_WorkTime_Value_48_48_onBlack(184,185,2);
	TFT_Disp_WorkTime_Value_48_48_onBlack(218,185,3);

}


/**************************************************************************
*
* Function Name:void TFT_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
* Function : 画点
* Input Ref:x，y:起始坐标  color:颜色
* Return Ref: NO
*
***********************************************************************/
void TFT_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
   LCD_Write_Cmd(0x2a);
   LCD_Write_Data(x >>8);
   LCD_Write_Data(x);

   LCD_Write_Cmd(0x2b);
   LCD_Write_Data(y >>8);
   LCD_Write_Data(y);

   LCD_Write_Cmd(0x2c);
   LCD_Write_Data(color >>8);
   LCD_Write_Data(color);
}
/**************************************************************************
*
* Function Name:void TFT_SetWindow(uint32_t xstart,uint32_t ystart,uint32_t xend,uint32_t yend)
* Function : windows set 
* Input Ref:xtart，ystart:起始坐标  终点坐标：xend,yend
* Return Ref: NO
*
***********************************************************************/
void TFT_SetWindow(uint16_t xstart,uint16_t ystart,uint16_t xend,uint16_t yend)
{
   LCD_Write_Cmd(0x2a);
    LCD_Write_Data(xstart >>8);
   LCD_Write_Data(xstart);                      //Column start

    LCD_Write_Data(xend >>8);
   LCD_Write_Data(xend);

   LCD_Write_Cmd(0x2b);
    LCD_Write_Data(ystart >>8);
   LCD_Write_Data(ystart);
   
     LCD_Write_Data(yend >>8);
   LCD_Write_Data(yend);                     //Row start

   LCD_Write_Cmd(0x2c);


}
/**************************************************************************
*
* Function Name:void TFT_St7789_SetBGColor(uint32_t color)
* Function : set background color
* Input Ref: color
* Return Ref: NO
*
***********************************************************************/
void TFT_St7789_SetBGColor(uint32_t color)
{
   uint32_t i,j;
   TFT_SetWindow(0,0,(LCD_Width-1),(LCD_Height -1));
   for(i=0;i<LCD_Height;i++){
       for(j=0;j<LCD_Width;j++){
           LCD_Write_16bit_Data(color);
       }
   }


}
/**************************************************************************
*
* Function Name:void TFT_St7789_FillBlock(uint32_t xstart,uint32_t ystart,uint32_t block_width,uint32_t block_height,uint32_t colo)
* Function : set background color
* Input Ref: color
* Return Ref: NO
*
***********************************************************************/
void TFT_St7789_FillBlock(uint16_t xstart,uint16_t ystart,uint16_t block_width,uint16_t block_height,uint16_t color)
{
    uint32_t i,j;
    TFT_SetWindow(xstart,ystart,(xstart+block_width-1),(ystart+block_height-1));
    for(i=0;i<block_width;i++){
        for(j=0;j<block_height;j++){
            LCD_Write_Data(color >>8);
			LCD_Write_Data(color );
        }
    }
}
/*******************************************************************************************
*
* Function Name:void TFT_ST7789_FillPicture(uint32_t xstart,uint32_t ystart,uint32_t block_width,uint32_t block_height,uint32_t *black_data)
* Function : fill picture 
* Input Ref: xstart,ystart ->start pointer, picture of block_width,picture of block_height
*            block_data is picture of array of data
* Return Ref: NO
*
******************************************************************************************/
#if 0
void TFT_ST7789_FillPicture(uint16_t xstart,uint16_t ystart,uint16_t block_width,uint16_t block_height,const uint8_t *block_data)
{
   uint16_t i,j;
  
   // TFT_SetWindow(xstart,ystart,(xstart+block_width-1),(ystart+block_height-1));
  // LCD_Address_Set(xstart,ystart,block_width,block_height);
   if(z==9600)z=0;
   DISP_WINDOWS();

  for(i=0;i<block_width;i++){

       for(j=0;j<block_height;j++){
         
         LCD_Write_Data(*(block_data +z));
		 z++;
		 LCD_Write_Data(*(block_data+z));
		 z++;
		 if(z==9600)z=0;
		
	     
	   }



  }
}
#endif 


/**********************************************************************
 * Function Name:void TFT_ShowString(u16 x,u16 y,char *str,u8 fw,u8 fh,u8 mode)
 * Function: 在指定位置开始显示一个字符串,支持自动换行
 * Input Ref: (x,y):起始坐标,width,height:区域
            //str  :字符串
            //fw:字宽
            //fh:字高
            //mode:0,非叠加方式;1,叠加方式
 * Return Ref: NO 
**********************************************************************/
//void TFT_ShowString(uint16_t x,uint16_t y,char *str,uint8_t fw,uint8_t fh,uint8_t mode)
//{
//    while((*str<='~')&&(*str>=' '))//判断是不是非法字符!
//    {
//        if(x>(LCD_Width-(fw))) {
//            x=0;
//            y+=fh;
//        }
//        if(y>(LCD_Height-fh)) {
//            y=x=0;   //TFT_Clear();
//        }
//        TFT_ShowChar(x,y,*str,fw,fh,mode);
//        x+=fw;
//        str++;
//    }
//}

/***************************************************************************************
 * @brief       指定的区域填充颜色块
 * @param       (sx,sy),(ex,ey):填充矩形对角坐标，区域大小:(ex - sx + 1) * (ey - sy + 1)
 * @param       color: 填充颜色的首地址
 * @retval      ÎÞ
 ***************************************************************************************/

/*********************************************************************
 * 
 * Function Name:void TFT_ShowText(uitn16_t x,uint16_t y,char *str,uint8_t fw,uint8_t fh,uint8_t mode)
 * Function : TFT display chinese of word 
 * Input Ref: x,y start position, *str of input chinese word,fw ,fh -> tft of sieze
 *            mode: 0 normal . 1->叠加
 * 
*********************************************************************/
void TFT_ShowText(uint16_t x,uint16_t y,char *str,uint8_t fw,uint8_t fh,uint8_t mode)
{
    while(*str!=0)
    {
       // TFT_ShowFont(x,y,str,fw,fh,mode); //显示这个汉字,空心显示
        str+=2;
        x+=fh;//下一个汉字偏移
    }
}









/***********************************************************************
 *
 * Function Name: void TFT_Works_Or_Timer_times_Handler(void)
 * Function: TFT LCD显示定时的时间设置或者显示北京时间 
 * Inpurt Ref: x,y:起点坐标 pw:图片宽（单位像素）ph:图片高（单位像素）
 *             p:图片起始地址
 * Return Ref: NO 
 *
************************************************************************/
void TFT_Works_Or_Timer_times_Handler(void)
{
            



}
/*******************************************************************************************
	 *
	 * @brief       画线
	 * @param       x1,y1: 起始坐标
	 * @param       x2,y2: 终点坐标
	 * @param       color: 线的颜色
	 * @retval      无
	 *
 *******************************************************************************************/
static void lcd_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, row, col;
    delta_x = x2 - x1;          /* 计算坐标增量 */
    delta_y = y2 - y1;
    row = x1;
    col = y1;

    if (delta_x > 0)incx = 1;   /* 设置单布方向 */
    else if (delta_x == 0)incx = 0; /* 垂直线 */
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0; /* 水平线*/
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if ( delta_x > delta_y)distance = delta_x;  /* 选取基本增量坐标轴 */
    else distance = delta_y;

    for (t = 0; t <= distance + 1; t++ )   /* 画线输出 */
    {
        //lcd_draw_point(row, col, color); /* 画点 */
        TFT_DrawPoint(row,col,color);
        xerr += delta_x ;
        yerr += delta_y ;

        if (xerr > distance)
        {
            xerr -= distance;
            row += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            col += incy;
        }
    }
}

/*************************************************************************************************
 * @brief       画矩形
 * @param       x1,y1: start
 * @param       x2,y2: end 
 * @param       color: rectangle is color
 * @retval      ÎÞ
 *************************************************************************************************/
void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    lcd_draw_line(x1, y1, x2, y1, color);
    lcd_draw_line(x1, y1, x1, y2, color);
    lcd_draw_line(x1, y2, x2, y2, color);
    lcd_draw_line(x2, y1, x2, y2, color);
}





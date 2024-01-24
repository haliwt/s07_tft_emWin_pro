#ifndef __BSP_FONT_H
#define __BSP_FONT_H
#include "main.h"


#define  ST7789V_DispWindow_X_Star    0 

#define  ST7789V_DispWindow_X_Star		    0     //起始点的X坐标
#define  ST7789V_DispWindow_Y_Star		    0     //起始点的Y坐标

#define  ST7789V_LESS_PIXEL	  							240			//液晶屏较短方向的像素宽度
#define  ST7789V_MORE_PIXEL	 


/*******************中文********** 在显示屏上显示的字符大小 ***************************/
#define      WIDTH_CH_CHAR		                16	    //中文字符宽度 
#define      HEIGHT_CH_CHAR		              	16		  //中文字符高度 



//16x16中文字体结构体定义
typedef struct 
{
   uint8_t Index[2];	//存放汉字GBK码
   char Msk[32]; //存放汉字取模数据
}typFNT_GB16;  //结构体名称可以自己定义







void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fontcolor, uint16_t backgroundcolor, uint8_t *s,uint8_t mode);



void TFT_display_char16_16_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);


void TFT_display_char16_16(const uint8_t *address ,uint16_t startX,uint16_t startY,
							uint16_t textColor, uint16_t backgroundColor);

void TFT_display_char16_16(const uint8_t *address ,uint16_t startX,uint16_t startY,
							uint16_t textColor, uint16_t backgroundColor);
void TFT_display_char16_16_Tow_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);




#endif 


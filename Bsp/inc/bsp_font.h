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

#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->Height))
#define LINEY(x) ((x) * (((sFONT *)LCD_GetFont())->Width))



typedef struct _tFont
{    
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;
  
} sFONT;

extern sFONT Font24x32;
extern sFONT Font16x24;
extern sFONT Font8x16;





void GUI_DrawFont16(uint16_t x, uint16_t y, uint16_t fontcolor, uint16_t backgroundcolor, uint8_t *s,uint8_t mode);



void TFT_display_char16_16_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);


void TFT_display_char16_16(const uint8_t *address ,uint16_t startX,uint16_t startY,
							uint16_t textColor, uint16_t backgroundColor);

void TFT_display_char16_16(const uint8_t *address ,uint16_t startX,uint16_t startY,
							uint16_t textColor, uint16_t backgroundColor);
void TFT_display_char16_16_Tow_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);

void TFT_display_char16_16_Three_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);

void TFT_display_char16_16_Four_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);


void TFT_display_char16_16_English_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);

void TFT_display_char32_32_English_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);

void LCD_DispString_EN ( 	uint16_t usX ,uint16_t usY,  char * pStr );

void TFT_DispChar_EN ( uint16_t usX, uint16_t usY, const char cChar );

void LCD_DispString_EN ( uint16_t usX ,uint16_t usY,  char * pStr );
void LCD_DispStringLine_EN (  uint16_t line,  char * pStr );

void St7789DrawChar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *str, uint16_t forecolor, uint16_t backcolor);

void TFT_ShowChar(uint16_t x,uint16_t y,uint8_t chr,uint8_t fw,uint8_t fh,uint8_t mode);

void TFT_ShowNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint8_t fw,uint8_t fh);

void TFT_ShowChar_144(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);

void TFT_ShowChar_256(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);



#endif 


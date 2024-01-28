#ifndef __BSP_LCD_GUI_H
#define __BSP_LCD_GUI_H
#include "main.h"

#define TFT_DISP_TEMP_24   0


void TFT_DrawPoint(uint16_t x,uint16_t y,uint16_t color);

void TFT_SetWindow(uint16_t xstart,uint16_t ystart,uint16_t xend,uint16_t yend);


void TFT_St7789_SetBGColor(uint32_t color);

void TFT_St7789_FillBlock(uint16_t xstart,uint16_t ystart,uint16_t block_width,uint16_t block_height,uint16_t color);


void TFT_ST7789_FillPicture(uint16_t xstart,uint16_t ystart,uint16_t block_width,uint16_t block_height,const uint8_t *black_data);


void TFT_Disp_Temp_Value(uint8_t bc,uint8_t temp_value);
void TFT_Disp_Humidity_Value(uint8_t hum_value);







void TFT_ShowString(uint16_t x,uint16_t y,char *str,uint8_t fw,uint8_t fh,uint8_t mode);

//void TFT_ShowFont(uint8_t x,uint8_t y,char *font,uint8_t fw,uint8_t fh,uint8_t mode);

void TFT_ShowText(uint16_t x,uint16_t y,char *str,uint8_t fw,uint8_t fh,uint8_t mode);

void TFT_ShowPicture(uint16_t x,uint16_t y,const uint8_t *p,uint8_t pw,uint8_t ph);

void TFT_Works_Or_Timer_times_Handler(void);

void TFT_Display_Handler(void);

void TFT_Works_Or_Timer_times_Handler(void);

void lcd_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

void TFT_Display_Temp_Symbol(void);

void TFT_Display_Humidity_Symbol(void);

void TFT_Display_WorksTime(void);

void TFT_Disp_Set_TimerTime(uint8_t bc);

void TFT_DonnotDisp_Works_Time(void);



#endif

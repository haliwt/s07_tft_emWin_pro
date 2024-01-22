#ifndef __BSP_LCD_GUI_H
#define __BSP_LCD_GUI_H
#include "main.h"

void TFT_DrawPoint(uint16_t x,uint16_t y,uint16_t color);

void TFT_SetWindow(uint32_t xstart,uint32_t ystart,uint32_t xend,uint32_t yend);


void TFT_St7789_SetBGColor(uint32_t color);

void TFT_St7789_FillBlock(uint32_t xstart,uint32_t ystart,uint32_t block_width,uint32_t block_height,uint32_t color);

void TFT_ST7789_FillPicture(uint32_t xstart,uint32_t ystart,uint32_t block_width,uint8_t block_height,const uint8_t *black_data);

void TFT_ShowChar(uint16_t x,uint16_t y,uint8_t chr,uint8_t fw,uint8_t fh,uint8_t mode);

void TFT_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t fw,uint8_t fh);

void TFT_ShowString(uint16_t x,uint16_t y,char *str,uint8_t fw,uint8_t fh,uint8_t mode);

void TFT_ShowFont(uint8_t x,uint8_t y,char *font,uint8_t fw,uint8_t fh,uint8_t mode);

void TFT_ShowText(uint16_t x,uint16_t y,char *str,uint8_t fw,uint8_t fh,uint8_t mode);

void TFT_ShowPicture(uint16_t x,uint16_t y,const uint8_t *p,uint8_t pw,uint8_t ph);

void TFT_Works_Or_Timer_times_Handler(void);

void TFT_Display_Handler(void);

void TFT_Works_Or_Timer_times_Handler(void);

#endif

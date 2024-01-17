#ifndef __BSP_LCD_GUI_H
#define __BSP_LCD_GUI_H
#include "main.h"

void SetWindow(uint32_t xstart,uint32_t ystart,uint32_t xend,uint32_t yend);

void SetPixel(uint32_t x,uint32_t y,uint32_t color);

void St7789_SetBGColor(uint32_t color);

void St7789_FillBlock(uint32_t color);








#endif

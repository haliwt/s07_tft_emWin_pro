#ifndef __BSP_FONT_APP_H
#define __BSP_FONT_APP_H
#include "main.h"




//void St7789DrawChar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *str, uint16_t forecolor, uint16_t backcolor);

//void TFT_ShowChar(uint16_t x,uint16_t y,uint8_t chr,uint8_t fw,uint8_t fh,uint8_t mode);

void TFT_ShowNum(uint16_t x,uint16_t y,uint16_t num,uint8_t len,uint8_t fw,uint8_t fh);

void TFT_ShowChar_144(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);

void TFT_ShowChar_256(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);

void TFT_ShowChar_576(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);

void TFT_display_char32_32_noBackColor(const uint8_t *address ,uint16_t startX,uint16_t startY,uint16_t color);


void TFT_Disp_Humidity_32_32_onBlack(uint16_t x,uint16_t y,uint8_t num);

void TFT_Disp_WorksTime_24_24_onBlack(uint16_t x,uint16_t y,uint8_t num);

void TFT_Disp_Temp_24_24_onBlack(uint16_t x,uint16_t y,uint8_t num);

void TFT_Disp_WorkTime_Value_48_48_onBlack(uint16_t x,uint16_t y,uint8_t num);






#endif 



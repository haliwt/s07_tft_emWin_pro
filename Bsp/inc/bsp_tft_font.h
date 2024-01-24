#ifndef __BSP_TFT_FONT_H
#define __BSP_TFT_FONT_H
#include "main.h"



extern const uint8_t font1616_temp[];//[][16];
extern const uint8_t font1616_temp_symbol[];

extern const uint8_t font1616_humidity_symbol[];

extern const uint8_t font1616_humidity[];

extern const uint8_t font1616_works_time[];

void TFT_Display_Tmep_Symbol(void);

void TFT_Display_Humidity_Symbol(void);
void TFT_Display_WorksTime(void);

#endif 







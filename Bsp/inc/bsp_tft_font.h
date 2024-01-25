#ifndef __BSP_TFT_FONT_H
#define __BSP_TFT_FONT_H
#include "main.h"

extern const unsigned char asc2_1224[95][36];


extern const uint8_t font1616_temp[];//[][16];
extern const uint8_t font1616_temp_symbol[];

extern const uint8_t font1616_humidity_symbol[];

extern const uint8_t font1616_humidity[];

extern const uint8_t font1616_works_time[];



extern const uint8_t font2448_no[4][96];


extern const uint8_t ASCII8x16_Table [] ;




void TFT_Display_Tmep_Symbol(void);

void TFT_Display_Humidity_Symbol(void);
void TFT_Display_WorksTime(void);

void TFT_Display_Number_32x32(void);


#endif 







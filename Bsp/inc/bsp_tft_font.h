#ifndef __BSP_TFT_FONT_H
#define __BSP_TFT_FONT_H
#include "main.h"

//extern const unsigned char asc2_1224[95][36];
//extern const uint8_t font1616_temp[];//[][16];
//extern const uint8_t font1616_temp_symbol[];

//extern const uint8_t font1616_humidity_symbol[];
//extern const uint8_t font3232_humidity_symbol[];

//extern const uint8_t font1616_humidity[];
//extern const uint8_t font3232_humidity[2][128];

//extern const uint8_t font1616_works_time[];

//extern const uint8_t font4848_no[4][144];

//extern const uint8_t font6464_no[1][256];

//extern const uint8_t ASCII8x16_Table [] ;

#if TFT_DISP_TEMP_24 

extern const uint8_t font2424_temp[3][72];
extern const uint8_t font2424_humidity[3][72];



extern const uint8_t font9696_no[10][576];


#endif 

extern const uint8_t font2424_temp_symbol[72];


extern const uint8_t font2424_humidity_symbol[72];

extern const uint8_t font2424_works_time[4][72];
extern const uint8_t font2424_timer_time[4][72];



extern const uint8_t font_pic_time_value[10][116];

extern const uint8_t font4848_works_time_value[11][144];



extern const uint8_t font2020_temp[2][60];


extern const uint8_t font2020_humidity[2][60];

//extern const uint8_t font90120_num[4][720];


//extern const uint8_t font110110_num[4][770];

extern const uint8_t font_pic_num[10][413];













#endif 







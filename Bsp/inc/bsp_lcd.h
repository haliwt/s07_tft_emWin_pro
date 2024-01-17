#ifndef __BSP_LCD_H
#define __BSP_LCD_H
#include "main.h"


//LCD屏幕分辨率定义
#define LCD_Width   240
#define LCD_Height  320
//颜色定义
#define WHITE   0xFFFF  //白色
#define YELLOW  0xFFE0  //黄色
#define BRRED   0XFC07  //棕红色
#define PINK    0XF81F  //粉色
#define RED     0xF800  //红色
#define BROWN   0XBC40  //棕色
#define GRAY    0X8430  //灰色
#define GBLUE   0X07FF  //兰色
#define GREEN   0x07E0  //绿色
#define BLUE    0x001F  //蓝色
#define BLACK   0x0000  //黑色


#define LCD_RST_SetHigh()  (HAL_GPIO_WritePin(FT_RESET_GPIO_Port,TFT_RESET_Pin,GPIO_PIN_SET))

#define LCD_RST_SetLow()   (HAL_GPIO_WritePin(FT_RESET_GPIO_Port,TFT_RESET_Pin,GPIO_PIN_RESET))

#define LCD_NSS_SetHigh()   (HAL_GPIO_WritePin(TFT_NSS_GPIO_Port,TFT_NSS_Pin,GPIO_PIN_SET))

#define LCD_NSS_SetLow()    (HAL_GPIO_WritePin(TFT_NSS_GPIO_Port,TFT_NSS_Pin,GPIO_PIN_RESET))

void LCD_Init(void);

void LCD_Display_BacklightOn(void);

void LCD_Display_BacklightOff(void);

void LCD_Write_Cmd(uint8_t cmd);

void LCD_Write_Data(uint8_t data);

void LCD_Write_16bit_Data(uint16_t data);

void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);




#endif 


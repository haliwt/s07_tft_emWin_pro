#include "bsp_lcd.h"
#include "bsp.h"

#define LCD_TOTAL_BUF_SIZE  (240*320*2)
#define LCD_Buf_Size 1152

static uint8_t SPI_WriteByte(uint8_t *txdata,uint16_t size);
static uint8_t lcd_buf[LCD_Buf_Size];

static void LCD_GPIO_Reset(void);
static void LCD_Clear(uint16_t color);

/*******************************************************************************
 * 
 * Function Name: uint8_t SPI_WriteByte(uint8_t *txdata,uint16_t size)
 * Function : to write data to TFT register
 * Input Ref: need write data, data of length
 * Return Ref: 0--success 1 - fail
 * 
***********************************************************************************/
static uint8_t SPI_WriteByte(uint8_t *txdata,uint16_t size)
{

  return HAL_SPI_Transmit_DMA(&hspi1,txdata,size);

}
static void LCD_GPIO_Reset(void)
{
    LCD_RST_SetLow();
    HAL_Delay(100);
    LCD_RST_SetHigh();

}
/*******************************************************************************
 * 
 * Function Name: static void LCD_Write_Cmd(uint8_t cmd)
 * Function : to write data to TFT register
 * Input Ref: write data 
 * Return Ref: NO
 * 
***********************************************************************************/
void LCD_Write_Cmd(uint8_t cmd)
{

    LCD_NSS_SetLow(); //To write command to TFT is low level 
    SPI_WriteByte(&cmd,1);

}

void LCD_Write_Data(uint8_t data)
{
    LCD_NSS_SetHigh(); //To write data to TFT is high level
    SPI_WriteByte(&data,1);
}

void LCD_Write_16bit_Data(uint16_t data)
{
    uint8_t temp_data;
    LCD_NSS_SetHigh(); //To write data to TFT is high level
    SPI_WriteByte((uint8_t *)data,1);
    temp_data = data >>8;
    SPI_WriteByte((uint8_t *)temp_data,1);

}
/*******************************************************************************
 * 
 * Function Name: void LCD_Display_BacklightOn(void)
 * Function : turn on TFT LCD back light
 * Input Ref: NO
 * Return Ref: NO
 * 
***********************************************************************************/
void LCD_Display_BacklightOn(void)
{
   

}

void LCD_Display_BacklightOff(void)
{


}

/*******************************************************************************
 * 
 * Function Name: void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
 * Function : turn on TFT LCD back light
 * Input Ref: from x to y of point (x1,y1) to (x2,y2)
 * Return Ref: NO
 * 
***********************************************************************************/
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    /* 指定X方向操作区域 */
    LCD_Write_Cmd(0x2a); //display column
    LCD_Write_Data(x1 >> 8);
    LCD_Write_Data(x1);
    LCD_Write_Data(x2 >> 8);
    LCD_Write_Data(x2);

    /* 指定Y方向操作区域 */
    LCD_Write_Cmd(0x2b); //display row 
    LCD_Write_Data(y1 >> 8);
    LCD_Write_Data(y1);
    LCD_Write_Data(y2 >> 8);
    LCD_Write_Data(y2);

    /* 发送该命令，LCD开始等待接收显存数据 */
    LCD_Write_Cmd(0x2C);

}

/*******************************************************************************
 * 
 * Function Name: static void LCD_Clear(uint16_t color)
 * Function : display TFT color
 * Input Ref: NO
 * Return Ref: NO
 * 
***********************************************************************************/
static void LCD_Clear(uint16_t color)
{
    uint16_t i, j;
    uint8_t data[2] = {0};  //color是16bit的，每个像素点需要两个字节的显存

    /* 将16bit的color值分开为两个单独的字节 */
    data[0] = color >> 8;
    data[1] = color;

    /* 显存的值需要逐字节写入 */
    for(j = 0; j < LCD_Buf_Size / 2; j++)
    {
        lcd_buf[j * 2] =  data[0];
        lcd_buf[j * 2 + 1] =  data[1];
    }
    /* 指定显存操作地址为全屏幕 */
    LCD_Address_Set(0, 0, LCD_Width - 1, LCD_Height - 1);
    /* 指定接下来的数据为数据 */
     LCD_NSS_SetHigh();//LCD_WR_RST(1);
    /* 将显存缓冲区的数据全部写入缓冲区 */
    for(i = 0; i < (LCD_TOTAL_BUF_SIZE / LCD_Buf_Size); i++)
    {
        SPI_WriteByte(lcd_buf, (uint16_t)LCD_Buf_Size);
    }
}
/*******************************************************************************
 * 
 * Function Name: static void LCD_Clear(uint16_t color)
 * Function : display TFT color
 * Input Ref: NO
 * Return Ref: NO
 * 
***********************************************************************************/
void LCD_Init(void)
{
    /* 关闭睡眠模式 */
    LCD_Write_Cmd(0x11);
    HAL_Delay(120);

    /* 开始设置显存扫描模式，数据格式等 */
    LCD_Write_Cmd(0x36);//修改此处，可以改变屏幕的显示方向，横屏，竖屏等
    LCD_Write_Data(0x00);
    /* RGB 5-6-5-bit格式  */
    LCD_Write_Cmd(0x3A);
    LCD_Write_Data(0x65);
    /* porch 设置 */
    LCD_Write_Cmd(0xB2);
    LCD_Write_Data(0x0C);//< Back porch in normal mode
    LCD_Write_Data(0x0C);//< Front porch in normal mode
    LCD_Write_Data(0x00);//< Disable separate porch control
    LCD_Write_Data(0x33);//< Back and front porch in idle mode
    LCD_Write_Data(0x33);//< Back and front porch in partial mode
    /* VGH设置 */
    LCD_Write_Cmd(0xB7);
    LCD_Write_Data(0x72);
    /* VCOM 设置 */
    LCD_Write_Cmd(0xBB);
    LCD_Write_Data(0x3D);
    /* LCM 设置 */
    LCD_Write_Cmd(0xC0);
    LCD_Write_Data(0x2C);
    /* VDV and VRH 设置 */
    LCD_Write_Cmd(0xC2);
    LCD_Write_Data(0x01);
    /* VRH 设置 */
    LCD_Write_Cmd(0xC3);
    LCD_Write_Data(0x19);
    /* VDV 设置 */
    LCD_Write_Cmd(0xC4);
    LCD_Write_Data(0x20);
    /* 普通模式下显存速率设置 60Mhz */
    LCD_Write_Cmd(0xC6);
    LCD_Write_Data(0x0F);
    /* 电源控制 */
    LCD_Write_Cmd(0xD0);
    LCD_Write_Data(0xA4);
    LCD_Write_Data(0xA1);
    /* 电压设置 */
    LCD_Write_Cmd(0xE0);
    LCD_Write_Data(0xD0);
    LCD_Write_Data(0x04);
    LCD_Write_Data(0x0D);
    LCD_Write_Data(0x11);
    LCD_Write_Data(0x13);
    LCD_Write_Data(0x2B);
    LCD_Write_Data(0x3F);
    LCD_Write_Data(0x54);
    LCD_Write_Data(0x4C);
    LCD_Write_Data(0x18);
    LCD_Write_Data(0x0D);
    LCD_Write_Data(0x0B);
    LCD_Write_Data(0x1F);
    LCD_Write_Data(0x23);
    /* 电压设置 */
    LCD_Write_Cmd(0xE1);
    LCD_Write_Data(0xD0);
    LCD_Write_Data(0x04);
    LCD_Write_Data(0x0C);
    LCD_Write_Data(0x11);
    LCD_Write_Data(0x13);
    LCD_Write_Data(0x2C);
    LCD_Write_Data(0x3F);
    LCD_Write_Data(0x44);
    LCD_Write_Data(0x51);
    LCD_Write_Data(0x2F);
    LCD_Write_Data(0x1F);
    LCD_Write_Data(0x1F);
    LCD_Write_Data(0x20);
    LCD_Write_Data(0x23);
    /* 显示开 */
    LCD_Write_Cmd(0x21);
    LCD_Write_Cmd(0x29);

    /* 清屏为白色 */
    LCD_Clear(WHITE);

    /*打开显示*/
    LCD_Display_BacklightOn();

}




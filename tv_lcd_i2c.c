
#include"lcd_i2c_header.h"

void SEND_TO_LCD_I2C(unsigned char data)
{
    i2c_start();
    i2c_write(0x4E);
    i2c_write(data);
    i2c_stop();
}

void PULSE_ENA_I2C(unsigned char data)
{
    data = data | 0x04;
    SEND_TO_LCD_I2C(data);
//	__delay_us(20);
    data = data & 0xfb;
    SEND_TO_LCD_I2C(data);
//	__delay_us(20);
}

void SEND_NIBBLES_LCD_I2C(unsigned char nibbles, unsigned char type) //RS:P0, RW:P1, E:P2
{
    if      (type==1) nibbles = (nibbles & 0xf0) | LCD_BACKLIGHT | 0x01;
    else if (type==0) nibbles = (nibbles & 0xf0) | LCD_BACKLIGHT | 0x00;
    else;
    SEND_TO_LCD_I2C(nibbles);
    PULSE_ENA_I2C(nibbles);
}

void LCD_I2C_COMMAND(unsigned char cmd)
{
    SEND_NIBBLES_LCD_I2C(cmd, 0);
    SEND_NIBBLES_LCD_I2C((unsigned char)(cmd<<4), 0);
}

void LCD_I2C_INIT()
{
    __delay_ms(20);
    SEND_NIBBLES_LCD_I2C(0x30, 0);
    __delay_ms(5);
    SEND_NIBBLES_LCD_I2C(0x30, 0);
    __delay_ms(1);
    SEND_NIBBLES_LCD_I2C(0x30, 0);
    SEND_NIBBLES_LCD_I2C(0x20, 0);
    LCD_I2C_COMMAND (0x28);
	LCD_I2C_COMMAND (0x08);
    LCD_I2C_COMMAND (0x01);
    __delay_ms(2); 
    LCD_I2C_COMMAND (0x0C);
    LCD_I2C_COMMAND (0x80);
}

void LCD_I2C_CHAR (unsigned char char_data)	
{
    SEND_NIBBLES_LCD_I2C(char_data, 1);
    SEND_NIBBLES_LCD_I2C((unsigned char)(char_data<<4), 1);
}

//void LCD_I2C_STRING (char *str)
//{
//    while ((*str)!=0)
//    {
//        LCD_I2C_CHAR(*str);
//        str++;
//    }
//}


void LCD_I2C_GOTO_XY (unsigned char x, unsigned char y)
{
    if (y <= 4 && y > 0 && x > 0 && x <= 20) {
        if (y == 1) LCD_I2C_COMMAND(0x7F + x);
        else if (y == 2) LCD_I2C_COMMAND(0xBF + x);
        else if (y == 3) LCD_I2C_COMMAND(0x93 + x);
        else if (y == 4) LCD_I2C_COMMAND(0xD3 + x);
    }
}

void LCD_BACKLIGHT_ON()
{
    LCD_BACKLIGHT = LCD_BL_ON;
    SEND_TO_LCD_I2C(LCD_BACKLIGHT);
}

void LCD_BACKLIGHT_OFF()
{
    LCD_BACKLIGHT = LCD_BL_OFF;
    SEND_TO_LCD_I2C(LCD_BACKLIGHT);
}
//void putch(char data) {
//    LCD_I2C_CHAR (data)	;
//}


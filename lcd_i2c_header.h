/* 
 * File:   lcd_i2c_header.h
 * Author: Admin
 *
 * Created on January 17, 2024, 4:22 PM
 */

#ifndef LCD_I2C_HEADER_H
#define	LCD_I2C_HEADER_H
#include<stdio.h>
#include <xc.h>
#include"i2c_header.h"
#define LCD_BL_ON       0x08
#define LCD_BL_OFF      0
unsigned char LCD_BACKLIGHT=LCD_BL_ON;
#define _XTAL_FREQ 16000000 


void SEND_TO_LCD_I2C(unsigned char data);

void PULSE_ENA_I2C(unsigned char data);

void SEND_NIBBLES_LCD_I2C(unsigned char nibbles, unsigned char type); //RS:P0, RW:P1, E:P2;

void LCD_I2C_COMMAND(unsigned char cmd);

void LCD_I2C_INIT(void);

void LCD_I2C_CHAR (unsigned char char_data);

//void LCD_I2C_STRING (char *str);


void LCD_I2C_GOTO_XY (unsigned char x, unsigned char y);

//void putch(char data);

void LCD_BACKLIGHT_ON();

void LCD_BACKLIGHT_OFF();

#endif	/* LCD_I2C_HEADER_H */


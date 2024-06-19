/* 
 * File:   uart_header.h
 * Author: khoav
 *
 * Created on March 24, 2024, 8:55 PM
 */

#ifndef UART_HEADER_H
#define	UART_HEADER_H

#include <xc.h>
#define _XTAL_FREQ 16000000 
void USART_Init(void);
void USART_TransmitChar(unsigned char out);
void USART_TransmitString(unsigned char *out);
unsigned char USART_ReceiveChar();
void USART_ReceiveString(unsigned char *buffer, unsigned char length_max);
//void putch(char data);

#endif	/* UART_HEADER_H */



#include"cf.h"
#include"lcd_i2c_header.h"
#include"uart_header.h"
#include"aht10_header.h"
#include"math.h"
#include"stdio.h"
#include <stdbool.h>
#define _XTAL_FREQ 16000000// khai bao tan so thach anh noi
//////////////////////////////////////////////////////////////////
#define printf_uart 0 // chon che do cho ham printf
#define printf_lcd  1
unsigned char printf_mode = printf_uart;
volatile unsigned char byte_rx, rx_index = 0;
volatile __bit ena_rx = 0, ena_send = 0;

void putch(char data) {
    if (printf_mode == printf_uart) USART_TransmitChar(data);
    else if (printf_mode == printf_lcd) LCD_I2C_CHAR(data);
}
////////////////////////////////////////////////////////////////
unsigned char bf_rx[3] = {}; // bo dem nhan uart
unsigned char bf_tx[20] = {};
// khung truyen du lieu 1 byte Start, 1 byte ID, 6 byte nhiet do , 4 byte mq2, 4 byte mp2, 1 byte Stop

unsigned long read_temp(void) {
    unsigned long dt1, dt2, dt3, temp;
    i2c_start();
    i2c_write(0x71);
    i2c_read(1);
    i2c_read(1);
    i2c_read(1);
    dt1 = i2c_read(1) & 0x0f;
    dt2 = i2c_read(1);
    dt3 = i2c_read(0);
    i2c_stop();
    temp = (dt1 & 0x0f) << 16 | dt2 << 8 | dt3;
    if (temp > 781189) temp = 781189;
    if (temp < 314573) temp = 314573;
    return temp;
}
///////////////////////////////////////////////////////////////

unsigned int mq2 = 0, mp2 = 0;
unsigned long temp=0;

void main(void) {
    OSCCON = 0X7f; // cau hinh thach anh noi 16MHz

    TRISAbits.TRISA4 = 0; //MD0
    LATAbits.LATA4 = 0;

    TRISCbits.TRISC3 = 0; //MD1
    LATCbits.LATC3 = 0;

    ANSELCbits.ANSC2 = 0; // SDA

    TRISAbits.TRISA2 = 1; //MQ2
    ANSELAbits.ANSA2 = 1;

//    TRISCbits.TRISC0 = 1; //MP2
//    ANSELCbits.ANSC0 = 1;

    USART_Init();

    ADCON1 = 0X80; // cau hinh ADC module

    printf_mode = printf_uart;
    bf_tx[0] = 'S';
    bf_tx[1] = 1;
    bf_tx[16] = 'P';
    mp2 = 1111;
    bf_tx[12] = (unsigned char) (mp2 / 1000 % 10 + 48);
    bf_tx[13] = (unsigned char) (mp2 / 100 % 10 + 48);
    bf_tx[14] = (unsigned char) (mp2 / 10 % 10 + 48);
    bf_tx[15] = (unsigned char) (mp2 / 1 % 10 + 48);
    while (1) {
        ////////////////////////////////////////////////////
        Cmd_Aht10(); // gui yeu cau chuyen doi nhiet do
        __delay_ms(80); // thoi gian cho chuyen doi nhiet do
        temp = read_temp(); // cap nhat gia tri nhiet do
        bf_tx[2] = (unsigned char) (temp / 100000 % 10 + 48);
        bf_tx[3] = (unsigned char) (temp / 10000 % 10 + 48);
        bf_tx[4] = (unsigned char) (temp / 1000 % 10 + 48);
        bf_tx[5] = (unsigned char) (temp / 100 % 10 + 48);
        bf_tx[6] = (unsigned char) (temp / 10 % 10 + 48);
        bf_tx[7] = (unsigned char) (temp / 1 % 10 + 48);
        ///////////////////////////////////////////////////
        ADCON0 = 0X09; // doc gia tri ADC cam bien MQ2
        __delay_us(50);
        ADCON0bits.ADGO = 1;
        __delay_ms(50);
        mq2 = ADRES;
        bf_tx[8] = (unsigned char) (mq2 / 1000 % 10 + 48);
        bf_tx[9] = (unsigned char) (mq2 / 100 % 10 + 48);
        bf_tx[10] = (unsigned char) (mq2 / 10 % 10 + 48);
        bf_tx[11] = (unsigned char) (mq2 / 1 % 10 + 48);
        ///////////////////////////////////////////////////
        // gui du lieu khi nhan duoc yeu cau
        if (ena_send == 1) {
            ena_send = 0;
            USART_TransmitString(bf_tx);
        }
    }
}

void __interrupt() ngat_uart() {
    byte_rx = USART_ReceiveChar();
    if (byte_rx == 'S') {
        ena_rx = 1;
        rx_index = 0;
    } else if (byte_rx != 'P' && ena_rx == 1) {
        bf_rx[rx_index] = byte_rx;
        rx_index++;
        if (rx_index > 1) ena_rx = 0;
    } else if (byte_rx == 'P' && ena_rx == 1) {
        if (bf_rx[0] == '1') {
            ena_send = 1;
            ena_rx = 0;
        }
    }
}

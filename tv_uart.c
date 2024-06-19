

#include "uart_header.h"

void USART_Init(void) {////  mac dinh 115200
    TRISC4 = 0;
    TRISC5 = 1;
    SPBRG = 34;
    TXSTA = 0x20;
    RCSTA = 0x90;
    BRG16 = 1;
    BRGH = 1;
    INTCONbits.GIE = 1; /* Enable Global Interrupt */
    INTCONbits.PEIE = 1; /* Enable Peripheral Interrupt */
    PIE1bits.RCIE = 1; /* Enable Receive Interrupt */
}

void USART_TransmitChar(unsigned char out) {
    while (TXIF == 0);
    TXREG = out;
}

void USART_TransmitString(unsigned char *out) {
    for (unsigned char i = 0; i < 17; i++) {
        USART_TransmitChar(out[i]);
    }
}

unsigned char USART_ReceiveChar() {
    //        TMR0 = 0;
    //        OPTION_REG = 0x03;
    //        while (PIR1bits.RCIF == 0 && TMR0 < 250) {
    while (PIR1bits.RCIF == 0) {
    };
    //    __delay_us(50);
    return (RCREG);
}

void USART_ReceiveString(unsigned char *buffer, unsigned char length_max) {
    unsigned char length = 0;
    if (USART_ReceiveChar() == 'S') {
        *buffer = USART_ReceiveChar();
        length++;
        //        TMR0 = 0;
        //        OPTION_REG = 0b00000111;
        while ((*buffer != 'P')) {
            buffer++;
            *buffer = USART_ReceiveChar();
            length++;
            if (length > length_max) {
                while (USART_ReceiveChar() != 'P');
                break;
            }
        }
        *buffer = 0;
    }
}
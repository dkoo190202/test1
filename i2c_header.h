
#ifndef I2C_HEADER_H
#define	I2C_HEADER_H

#include <xc.h>
#define _XTAL_FREQ 16000000 

#define SDA_IN     PORTCbits.RC2
#define SDA_OUT    LATC2
#define SCL        LATC1
#define SDA_TRIS   TRISC2
#define SCL_TRIS   TRISC1

void i2c_start(void);
void i2c_stop(void);
void i2c_write(unsigned char DATA);
unsigned char i2c_read(unsigned char ACK);

#endif	/* I2C_HEADER_H */



#include "i2c_header.h"
void i2c_start(void)
{
    SDA_TRIS = 0;
    SCL_TRIS = 0;
    SDA_OUT = 1;
    SCL = 1;
    SDA_OUT = 0;
    SCL = 0;
}

void i2c_stop(void)
{
    SDA_TRIS = 0;
    SCL_TRIS = 0;
    SDA_OUT = 0;
    SCL = 0;
    SCL = 1;
    SDA_OUT = 1; 
}

void i2c_write(unsigned char DATA)
{
    unsigned char i,j;
    SDA_TRIS=0;
    SCL_TRIS=0;
    for(i=0;i<=8;i++)
    {
        if((DATA<<i) & 0x80) SDA_OUT=1;    // MSB fist   
        else            SDA_OUT=0;
        SCL=1;
//        j++;// delay
        __delay_us(1);
        SCL=0;
    }
}

unsigned char i2c_read(unsigned char ACK)
{
    unsigned char DATA;
    SCL_TRIS=0;
    SCL=0;
    SDA_TRIS=1;        
    for (unsigned char i=0;i<8;i++)
    {
        SCL = 1;
        if(SDA_IN == 1) DATA = (unsigned char)(DATA << 1) | 1;
        else            DATA = (unsigned char)(DATA << 1);
        SCL=0;
        __delay_us(10);
    }
    SDA_TRIS=0;       
    if (ACK == 1) SDA_OUT = 0;    
    else SDA_OUT = 1;    
    SCL=1;
    SCL=0;
    return DATA;
}

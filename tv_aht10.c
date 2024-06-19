

#include "aht10_header.h"
void Cmd_Aht10() {
    i2c_start();
    i2c_write(0x70);
    i2c_write(0xac);
//    i2c_write(0x33);
//    i2c_write(0);
    i2c_stop();
}

void READ_T_H_AHT10(float *p) {//p0: nhietdo, p1: do am
    unsigned long temp = 0, hum = 0;
    unsigned long dt1, dt2, dt3, dt4, dt5;
    i2c_start();
    i2c_write(0x71);
    i2c_read(1);
    dt1 = i2c_read(1);
    dt2 = i2c_read(1);
    dt3 = i2c_read(1);
    dt4 = i2c_read(1);
    dt5 = i2c_read(0);
    i2c_stop();
//    hum = (dt1 << 12) | (dt2 << 4) | (dt3 >> 4);
//    p[1] = ((100 * (float)hum) / 1048576);
//    if (p[1]>99) p[1]=99;
    temp_glo = ((dt3 & 0x0f) << 16) | (dt4 << 8) | dt5;
//    p[0] = (200 * (float) temp_glo) / 1048576 - 50;
//    if (p[0]>99) p[0]=99;
}

unsigned char lamtron(float data) {
    if ((data - (unsigned char) data) >= 0.5) {
        return ((unsigned char) data) + 1;
    } else return (unsigned char) data;
}
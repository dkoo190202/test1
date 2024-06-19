/* 
 * File:   aht10_header.h
 * Author: Admin
 *
 * Created on October 28, 2023, 1:46 PM
 */

#ifndef AHT10_HEADER_H
#define	AHT10_HEADER_H
#include "i2c_header.h"
void Cmd_Aht10(void);
void READ_T_H_AHT10(float *p);
unsigned char lamtron(float data);
unsigned long temp_glo;

#endif	/* AHT10_HEADER_H */


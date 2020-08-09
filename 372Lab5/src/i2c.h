// Author:         Ajay Katoch, Kyle Fortuno, James Rowley, John Merems, Quinton Arnaud
// Net ID:         
// Date:           3/26/19
// Assignment:     Lab 5
//
// Description: 
//
// Requirements:
//----------------------------------------------------------------------//

#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

void initAccelerometer();
void beginTransmission(int address);
int endTransmission();
int write(unsigned char parameter);
int requestFrom(unsigned char address, unsigned char * buffer, unsigned char quantity);
int writeTo(unsigned char address, unsigned char value);
int availible();
unsigned char read(int nack, unsigned char * buffer);

#endif

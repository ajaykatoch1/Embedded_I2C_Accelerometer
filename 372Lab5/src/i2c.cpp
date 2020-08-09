// Author:         Ajay Katoch, Kyle Fortuno, James Rowley, John Merems, Quinton Arnaud
// Net ID:         
// Date:           3/26/19
// Assignment:     Lab 5
//
// Description: 
//
// Requirements:
//----------------------------------------------------------------------//

#include "i2c.h"
#include "timer.h"
#include <Wire.h>

//TODO
//this library is using the Arduino Wire library until the accelerometer is working
//We need to remove Wire.h and implement I2C communcation without it before 
//the project is complete

//initilizes the accelerometer
void initAccelerometer(){
    DDRD |= (1 << DDD0) | (1 << DDD1);
    TWSR = 0;
    TWBR = 18;
    TWCR = (1 << TWEN) | (1 << TWINT);
}

void beginTransmission(int read){
    //for this application the address will always be 1D
    //concatenated with read (1) or write (0)

    // Send start bit
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));

    // Send address with R/W bit
    TWDR = (0x1D << 1) | read;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

int endTransmission(){
    // Send stop bit
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
    return 1;
}

int write(unsigned char parameter){
    if (TWSR == 0x18 || TWSR == 0x28)
    {
        // If SLA+W or data transmitted and ACK recieved, transmit data.
        TWDR = parameter;
        TWCR = (1 << TWINT) | (1 << TWEN);
        while (!(TWCR & (1 << TWINT)));
        return 1;
    }
    else
    {
        // Not in proper state to transmit.
        return 0;
    }
}

int requestFrom(unsigned char address, unsigned char * buffer, unsigned char quantity){
    beginTransmission(0);
    write(address);
    endTransmission();

    beginTransmission(1);
    for (int i = 0; i < quantity; i++)
    {
        read(i == (quantity - 1), buffer + i);
    }
    endTransmission();

    return 1;
}

int writeTo(unsigned char address, unsigned char value){
    beginTransmission(0);
    write(address);
    write(value);
    endTransmission();

    return 1;
}

unsigned char read(int nack, unsigned char * buffer){
    if (TWSR == 0x40 || TWSR == 0x50)
    {
        // If SLA+R transmitted or data received and ACK recieved, receive data.
        if (nack)
        {
            TWCR = (1 << TWINT) | (1 << TWEN);
        }
        else
        {
            TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
        }
        while (!(TWCR & (1 << TWINT)));
        *buffer = TWDR;
        return 1;
    }
    else
    {
        // Not in proper state to receive.
        return 0;
    }
}
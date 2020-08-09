// Author:         Ajay Katoch, Kyle Fortuno, James Rowley, John Merems, Quinton Arnaud
// Net ID:         
// Date:           3/26/19
// Assignment:     Lab 5
//
// Description: 
//
// Requirements:
//----------------------------------------------------------------------//

#include <Arduino.h> 
#include <avr/io.h>
#include "timer.h"
#include "i2c.h"

#define ACC_BYTES 6

int main(){
  //initilize functions
  initTimer1();
  initAccelerometer();
  Serial.begin(9600);

  writeTo(0x2D, 0b00001000);
  writeTo(0x2C, 0b00001010);

  unsigned char buf[ACC_BYTES] = {0};

  while(1){
    requestFrom(0x32, buf, ACC_BYTES);
    short int x = (short int)(((unsigned short int)buf[1] << 8) + buf[0]);
    short int y = (short int)(((unsigned short int)buf[3] << 8) + buf[2]);
    short int z = (short int)(((unsigned short int)buf[5] << 8) + buf[4]);

    Serial.println("----");
    Serial.print("X: ");
    Serial.println(x, DEC);
    Serial.print("Y: ");
    Serial.println(y, DEC);
    Serial.print("Z: ");
    Serial.println(z, DEC);

    delayms(1000);
  }

  return 0;
}

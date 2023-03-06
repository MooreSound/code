#include "PCF8574.h"
#include <Wire.h>

PCF8574 PCF_01(0x20);


const int red = 0;
const int green = 1;
const int blue = 2;

const int led1 = 3;
const int led2 = 4;
const int led3 = 5;
const int led4 = 6;
const int led5 = 7;


void setup() {
   PCF_01.begin();

  
}

void loop() {
  

  
 
   PCF_01.write(red, HIGH);
   PCF_01.write(green,HIGH);
  PCF_01.write(blue, HIGH);

  PCF_01.write(led1, LOW);
   PCF_01.write(led2, LOW);
  PCF_01.write(led3, LOW);
   PCF_01.write(led4, LOW);
  PCF_01.write(led5, LOW);
  delay(2000);
  
   PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, HIGH);

  PCF_01.write(led1, LOW);
   PCF_01.write(led2, LOW);
  PCF_01.write(led3, LOW);
   PCF_01.write(led4, LOW);
  PCF_01.write(led5, LOW);
 delay(2000);
 
  PCF_01.write(red, HIGH);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, LOW);
   PCF_01.write(led2, LOW);
  PCF_01.write(led3, LOW);
   PCF_01.write(led4, LOW);
  PCF_01.write(led5, LOW);
  delay(2000);

PCF_01.write(red, LOW);
   PCF_01.write(green, HIGH);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, LOW);
   PCF_01.write(led2, LOW);
  PCF_01.write(led3, LOW);
   PCF_01.write(led4, LOW);
  PCF_01.write(led5, LOW);
  delay(2000);

 
 for(int i = 0; i < 200; i++){
 PCF_01.write(red, HIGH);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, LOW);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);
 

   PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);


 PCF_01.write(red, HIGH);
   PCF_01.write(green, HIGH);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, LOW);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);


 PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);
 

 PCF_01.write(red, LOW);
   PCF_01.write(green, HIGH);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, LOW);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);


 PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);
 

 PCF_01.write(red, LOW);
   PCF_01.write(green, HIGH);
  PCF_01.write(blue, HIGH);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, LOW);
  PCF_01.write(led5, HIGH);
 

 PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);


PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, HIGH);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, LOW);


 PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);
 }

  for(int i = 0; i < 200; i++){
  PCF_01.write(red, HIGH);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, HIGH);

  PCF_01.write(led1, LOW);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);
 PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);

  PCF_01.write(red, HIGH);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, LOW);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);
PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);
  PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, LOW);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);
 PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);

   PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, HIGH);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, LOW);
  PCF_01.write(led5, HIGH);
 PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);

  PCF_01.write(red, HIGH);
   PCF_01.write(green, HIGH);
  PCF_01.write(blue, HIGH);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, LOW);
 PCF_01.write(red, LOW);
   PCF_01.write(green, LOW);
  PCF_01.write(blue, LOW);

  PCF_01.write(led1, HIGH);
   PCF_01.write(led2, HIGH);
  PCF_01.write(led3, HIGH);
   PCF_01.write(led4, HIGH);
  PCF_01.write(led5, HIGH);

}
}

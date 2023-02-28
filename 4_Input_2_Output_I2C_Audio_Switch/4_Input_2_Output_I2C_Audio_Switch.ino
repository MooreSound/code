#include <PCF8574.h>
#include <Wire.h>

PCF8574 pcf20(0x20);

const int selectA = 0;
const int selectB = 1;
const int enable1 = 2;
const int enable2 = 3;
const int selectA2 = 4;
const int selectB2 = 5;


void setup() {
  Serial.begin(115200);
  pcf20.begin();

  Serial.println("4 input 2 output I2C audio switch");

}

void loop() {
if (Serial.available()) {
    int inByte = Serial.read();
   if(inByte == '0' ){
      setAudioSource(0);
    }else if(inByte == '1' ){
      setAudioSource(1);
    }else if(inByte == '2' ){
      setAudioSource(2);
    }else if(inByte == '3' ){
      setAudioSource(3);
    }else if(inByte == '4' ){
      setAudioSource(4);
    }else if(inByte == '5' ){
      setAudioSource(5);
    }else if(inByte == '6' ){
      setAudioSource(6);
    }else if(inByte == '7' ){
      setAudioSource(7);
    }else if(inByte == '8' ){
      setAudioSource(8);
    }

}
}

void setAudioSource(int s){
  if(s == 0){
     Serial.println("Output 1 & 2 disabled");

    pcf20.write(selectA, HIGH);
    pcf20.write(selectB, HIGH);
    pcf20.write(enable1, HIGH);
    pcf20.write(enable2, HIGH);
    pcf20.write(selectA2, HIGH);
    pcf20.write(selectB2, HIGH);
  } else if(s == 1){
     Serial.println("Input 1 Selected on output 1");
    pcf20.write(selectA, LOW);
    pcf20.write(selectB, LOW);
    pcf20.write(enable1, LOW);
    
  }else if(s == 2){
    Serial.println("Input 2 Selected on output 1");
    pcf20.write(selectA, HIGH);
    pcf20.write(selectB, LOW);
    pcf20.write(enable1, LOW);
  }else if(s == 3){
    Serial.println("Input 3 Selected on output 1");
    pcf20.write(selectA, LOW);
    pcf20.write(selectB, HIGH);
    pcf20.write(enable1, LOW);
  }else if(s == 4){
    Serial.println("Input 4 Selected on output 1");
    pcf20.write(selectA, HIGH);
    pcf20.write(selectB, HIGH);
    pcf20.write(enable1, LOW);
  }else if(s == 5){
     Serial.println("Input 1 Selected on output 2");
    pcf20.write(enable2, LOW);
    pcf20.write(selectA2, LOW);
    pcf20.write(selectB2, LOW);
  }else if(s == 6){
    Serial.println("Input 2 Selected on output 2");
    pcf20.write(enable2, LOW);
    pcf20.write(selectA2, HIGH);
    pcf20.write(selectB2, LOW);
  }else if(s == 7){
   Serial.println("Input 3 Selected on output 2");
    pcf20.write(enable2, LOW);
    pcf20.write(selectA2, LOW);
    pcf20.write(selectB2, HIGH);
  }else if(s == 8){
     Serial.println("Input 4 Selected on output 2");
    pcf20.write(enable2, LOW);
    pcf20.write(selectA2, HIGH);
    pcf20.write(selectB2, HIGH);
  }
}

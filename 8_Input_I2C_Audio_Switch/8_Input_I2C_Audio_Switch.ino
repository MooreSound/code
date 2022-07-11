#include <PCF8574.h>
#include <Wire.h>

PCF8574 pcf20(0x20);

const int selectA = 0;
const int selectB = 1;
const int enable1 = 2;
const int enable2 = 3;

void setup() {
  Serial.begin(115200);
  pcf20.begin();

  Serial.println("8 input I2C audio switch");

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
  Serial.print("Input ");
  Serial.print(s);
  Serial.println(" Selected");
  if(s == 0){
    pcf20.write(selectA, HIGH);
    pcf20.write(selectB, HIGH);
    pcf20.write(enable1, HIGH);
    pcf20.write(enable2, HIGH);
  } else if(s == 1){
    pcf20.write(selectA, LOW);
    pcf20.write(selectB, LOW);
    pcf20.write(enable1, LOW);
    pcf20.write(enable2, HIGH);
  }else if(s == 2){
    pcf20.write(selectA, HIGH);
    pcf20.write(selectB, LOW);
    pcf20.write(enable1, LOW);
    pcf20.write(enable2, HIGH);
  }else if(s == 3){
    pcf20.write(selectA, LOW);
    pcf20.write(selectB, HIGH);
    pcf20.write(enable1, LOW);
    pcf20.write(enable2, HIGH);
  }else if(s == 4){
    pcf20.write(selectA, HIGH);
    pcf20.write(selectB, HIGH);
    pcf20.write(enable1, LOW);
    pcf20.write(enable2, HIGH);
  }else if(s == 5){
    pcf20.write(selectA, LOW);
    pcf20.write(selectB, LOW);
    pcf20.write(enable1, HIGH);
    pcf20.write(enable2, LOW);
  }else if(s == 6){
    pcf20.write(selectA, HIGH);
    pcf20.write(selectB, LOW);
    pcf20.write(enable1, HIGH);
    pcf20.write(enable2, LOW);
  }else if(s == 7){
    pcf20.write(selectA, LOW);
    pcf20.write(selectB, HIGH);
    pcf20.write(enable1, HIGH);
    pcf20.write(enable2, LOW);
  }else if(s == 8){
    pcf20.write(selectA, HIGH);
    pcf20.write(selectB, HIGH);
    pcf20.write(enable1, HIGH);
    pcf20.write(enable2, LOW);
  }
}

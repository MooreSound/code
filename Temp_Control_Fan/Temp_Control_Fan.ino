/* SerialTemp example
 
 Copyright 2017 Isaac100

 This example writes the current temperarure in celsius
 and fahrenheit to the serial monitor.

*/

#include <TMP36.h>

//Create an instance of the TMP36 class and 
//define the pin the sensor is connected to
//If using 3.3v Arduino, change 5 to 3.3
TMP36 myTMP36(A0, 5.0); 

const int fanPin = 3;
int fanSpeed = 30;

void setup() {
  Serial.begin(9600);
  pinMode(fanPin, OUTPUT);
}

void loop() {
  //create a variable and store the current temperature in
  //celsius in it using the getTempC function
  float celsius = myTMP36.getTempC(); 
  
  //create a variable and store the current temperature in
  //fahrenheit in it using the getTempF function
  float fahrenheit = myTMP36.getTempF(); 

  fanSpeed = map(fahrenheit, 65, 120, 30, 255);
 if(fanSpeed > 255){
    fanSpeed = 255;
  }else if(fanSpeed <= 30){
    fanSpeed = 30;
  }
  //Print the data to the Serial monitor
  Serial.print("Celsius: ");
  Serial.print(celsius);
  Serial.print(" Fahrenheit: ");
  Serial.print(fahrenheit);
  Serial.print(" Fan Speed: ");
  Serial.println(fanSpeed);
 
  analogWrite(fanPin, fanSpeed);
  delay(3000);
  
}

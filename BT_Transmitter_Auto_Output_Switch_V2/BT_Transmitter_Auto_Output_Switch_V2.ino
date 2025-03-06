/*
  Software serial multiple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

const int btPower = 10;
const int connectPin = 5;
const int linkPin = 4;
const int selectA = 6;
const int selectB = 7;
const int auxSense = 8;
const int button = 9;
const int blueLED = 13;

long buttonTimer = 0;
long longPressTime = 3000;

boolean buttonActive = false;
boolean btOn = false;
boolean longPressActive = false;

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  
 pinMode(btPower, OUTPUT);
  pinMode(connectPin, OUTPUT);
  pinMode(linkPin, INPUT);
  pinMode(selectA, OUTPUT);
   pinMode(selectB, OUTPUT);
   pinMode(button, INPUT_PULLUP);
   pinMode(auxSense, INPUT_PULLUP);


pinMode(blueLED, OUTPUT);

digitalWrite(blueLED, HIGH);
digitalWrite(btPower, LOW);
delay(1000);
   
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
 
digitalWrite(blueLED, LOW);
}

void loop() { // run over and over
if(digitalRead(auxSense) == LOW){
   digitalWrite(selectA, HIGH);
  digitalWrite(selectB, LOW);

digitalWrite(blueLED, LOW);
    }else if(digitalRead(linkPin) == HIGH){
   digitalWrite(selectA, LOW);
  digitalWrite(selectB, HIGH);
digitalWrite(blueLED, HIGH);
    } else{
      
      digitalWrite(selectA, LOW);
  digitalWrite(selectB, LOW);
  if(btOn == true){
    digitalWrite(blueLED, HIGH);
    delay(300);
    digitalWrite(blueLED, LOW);
    delay(300);
  }
digitalWrite(blueLED, LOW);
    }

 if(digitalRead(button) == LOW){

     if (buttonActive == false) {

      buttonActive = true;
      buttonTimer = millis();

  btOn = true;
  digitalWrite(btPower, HIGH);
  digitalWrite(connectPin, HIGH);
  delay(1000);
  digitalWrite(connectPin, LOW);

    }

    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {

      longPressActive = true;
     
    }
  }

   else {

    if (buttonActive == true) {

      if (longPressActive == true) {

        longPressActive = false;

digitalWrite(blueLED, LOW);
digitalWrite(btPower, LOW);
btOn = false;
      } else {
       
      }

      buttonActive = false;

    } 
   }
}

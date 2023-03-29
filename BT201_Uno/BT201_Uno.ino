#include <SoftwareSerial.h>

SoftwareSerial BT201Serial(4, 3); // RX, TX
const int playButton = 9;
const int nextButton = 10;
const int prevButton = 8;
const int volUpButton = 7;
const int volDnButton = 6;
const int ampMute = 5;

const int redLED = 13;
const int greenLED = 12;
const int blueLED = 11;

int btStatus = 0;

unsigned long previousMillis = 0; 


void setup() {
  pinMode(playButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);
  pinMode(prevButton, INPUT_PULLUP);
  pinMode(volUpButton, INPUT_PULLUP);
  pinMode(volDnButton, INPUT_PULLUP);
  pinMode(ampMute, OUTPUT);
  pinMode(redLED, OUTPUT);
   pinMode(greenLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
 Serial.begin(115200);
 BT201Serial.begin(115200);

 digitalWrite(redLED, HIGH);
 digitalWrite(greenLED, HIGH);
 digitalWrite(blueLED, HIGH);
  resetBT201();
    btStatus = getBTStatus();
    delay(300);
 digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
}

void loop() {
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
     previousMillis = currentMillis;
    btStatus = getBTStatus();
    delay(50);
  }

    switch(btStatus){
        case 3:
    digitalWrite(ampMute, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, HIGH);
    break;
    case 2:
   digitalWrite(ampMute, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED,HIGH);
    digitalWrite(blueLED, HIGH);
    break;
    case 4:
   digitalWrite(ampMute, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, LOW);
   break;
    case 1:
   digitalWrite(ampMute, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    break;
    }
    delay(50);
 
  
  if(digitalRead(playButton) == LOW){
    digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
   playPause();
   delay(100);
  }else if(digitalRead(nextButton) == LOW){
    digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
   nextTrack();
   delay(100);
  }else if(digitalRead(prevButton) == LOW){
    digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
    prevTrack();
    delay(100);
  }else if(digitalRead(volUpButton) == LOW){
    digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
   volUp();
   delay(100);
  }else if(digitalRead(volDnButton) == LOW){
    digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
   volDown();
   delay(100);
  }

}

#include <SPI.h>


const int asInhibit = 9;
const int asSelectA = 8;
const int asSelectB = 7;
const int redLED = A0;
const int greenLED = A1;
const int blueLED = A2;

const int modeButton = 5;
const int volUpButton = 6;
const int volDnButton = 4;

const byte csPin           = 10;       // MCP42100 chip select pin
const int  maxPositions    = 256;     // wiper can move from 0 to 255 = 256 positions
const long rAB             = 100000;  // 100k pot resistance between terminals A and B
const byte rWiper          = 125;     // 125 ohms pot wiper resistance
const byte pot0            = 0x11;    // pot0 addr
const byte pot1            = 0x12;    // pot1 addr
const byte potBoth         = 0x13;    // pot0 and pot1 simultaneous addr
const byte pot0Shutdown    = 0x21;    // pot0 shutdown
const byte pot1Shutdown    = 0x22;    // pot1 shutdown
const byte potBothShutdown = 0x23;    // pot0 and pot1 simultaneous shutdown


int volume = 15;
int currentInput = 0;

void setup() {
 pinMode(modeButton, INPUT_PULLUP);
  pinMode(volUpButton, INPUT_PULLUP);
  pinMode(volDnButton, INPUT_PULLUP);
  
  pinMode(asInhibit, OUTPUT);
   pinMode(asSelectA, OUTPUT);
    pinMode(asSelectB, OUTPUT);
    pinMode(redLED, OUTPUT);
   pinMode(greenLED, OUTPUT);
    pinMode(blueLED, OUTPUT);
   digitalWrite(csPin, HIGH);        // chip select default to de-selected
  pinMode(csPin, OUTPUT);  
   SPI.begin();
  Serial.begin(115200);

  digitalWrite(redLED, HIGH);
 digitalWrite(greenLED, HIGH);
 digitalWrite(blueLED, HIGH);
 delay(1000);
 digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
}

void loop() {
 
 switch(currentInput){
  case 1:
   unmute();
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, LOW);
      digitalWrite(asSelectB, LOW);
       digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, HIGH);
     break;
  case 2:
   unmute();
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, LOW);
     digitalWrite(redLED, LOW);
 digitalWrite(greenLED, HIGH);
 digitalWrite(blueLED, LOW);
     break;
  case 3:
  unmute();
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, LOW);
      digitalWrite(asSelectB, HIGH);
     digitalWrite(redLED, HIGH);
 digitalWrite(greenLED, HIGH);
 digitalWrite(blueLED, LOW);
   break;
  case 4:
  unmute();
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, HIGH);
     digitalWrite(redLED, HIGH);
 digitalWrite(greenLED, HIGH);
 digitalWrite(blueLED, HIGH);
       break;
  case 0:
  mute();
   digitalWrite(asInhibit, HIGH);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, HIGH);
     digitalWrite(redLED, HIGH);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
       break;
  }

 if(digitalRead(modeButton) == LOW){
    digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
  if(currentInput >= 4){
    currentInput = 0;
  }else {
    currentInput++;
  }
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
  }else{
    
  }

 delay(100);
  
}

void volUp(){
int volumeScaled = map(volume, 0, 30, 0, 255);

  volume++;
  if(volume >= 30){
    volume = 30;
  }
  setPotWiper(potBoth, volumeScaled);
}
void volDown(){
int volumeScaled = map(volume, 0, 30, 0, 255);
 
  
  volume--;
  if(volume <= 0){
    volume = 0;
     }
   setPotWiper(potBoth, volumeScaled);
  }

  void mute(){
    setPotWiper(potBothShutdown, 0);
  }

  void unmute(){
 int volumeScaled = map(volume, 0, 30, 0, 255);
 
   setPotWiper(potBoth, volumeScaled);
  }

void setPotWiper(int addr, int pos) {

  pos = constrain(pos, 0, 255);            // limit wiper setting to range of 0 to 255

  digitalWrite(csPin, LOW);                // select chip
  SPI.transfer(addr);                      // configure target pot with wiper position
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);               // de-select chip
}

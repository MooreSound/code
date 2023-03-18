#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <IRremote.h>

const int RECV_PIN = 3;

const int playButton = 9;
const int nextButton = 10;
const int prevButton = 8;
const int volUpButton = 7;
const int volDnButton = 6;
const int ampOn = 13;
const int ampMute = 12;

IRrecv irrecv(RECV_PIN);

decode_results results;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  pinMode(playButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);
  pinMode(prevButton, INPUT_PULLUP);
  pinMode(volUpButton, INPUT_PULLUP);
  pinMode(volDnButton, INPUT_PULLUP);
  pinMode(ampOn, OUTPUT);
  pinMode(ampMute, OUTPUT);
 Serial.begin(115200);
  Serial1.begin(115200);

 irrecv.enableIRIn(); // Start the receiver

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)// Check your I2C address and enter it here, in Our case address is 0x3C
     display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
}

void loop() {
  display.clearDisplay();
    if(getStatus() == 3){
      digitalWrite(ampOn, HIGH);
      digitalWrite(ampMute, LOW);
       display.setCursor(20, 10);
     display.print("BT Active");
    }else if(getStatus() == 2){
       digitalWrite(ampOn, LOW);
       digitalWrite(ampMute, HIGH);
       display.setCursor(20, 10);
    display.print("Paused"); 
    }else if(getStatus() == 4){
       digitalWrite(ampOn, HIGH);
      digitalWrite(ampMute, LOW);
       display.setCursor(20, 10);
    display.print("Incoming call");
    }/*else if(getStatus() == 1){
       digitalWrite(ampOn, LOW);
      digitalWrite(ampMute, HIGH);
       display.setCursor(20, 10);
    display.print("Disconnected");
    }*/
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    switch(results.value){
      case 0xFFC23D:
      playPause();
      break;
      
      case 0xFF02FD:
      nextTrack();
      break;
      
      case 0xFF22DD:
      prevTrack();
      break;

      case 0xFFE01F:
      volDown();
      break;

      case 0xFFA857:
      volUp();
      break;

      default:
      break;

    }
    irrecv.resume(); // Receive the next value
    }
    
    
  
  if(digitalRead(playButton) == LOW){
   playPause();
  }else if(digitalRead(nextButton) == LOW){
   nextTrack();
  }else if(digitalRead(prevButton) == LOW){
    prevTrack();
  }else if(digitalRead(volUpButton) == LOW){
   volUp();
  }else if(digitalRead(volDnButton) == LOW){
   volDown();
  } 
display.display(); 
}

void playPause(){

   Serial1.println("AT+CB");
    delay(50);
 

}

void nextTrack(){
   Serial1.println("AT+CC");
    delay(50);
}

void prevTrack(){
   Serial1.println("AT+CD");
    delay(50);
}
void volUp(){
Serial1.println("AT+CE");
    delay(50);
}
void volDown(){
 
Serial1.println("AT+CF");
    delay(50);
}

int getStatus(){
  Serial1.println("AT+TS");
  delay(50);
   while (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
    if(inByte == '2' || inByte == '4'){
      return 3;
    }else if(inByte == '1'){
     return 2;
     }else if(inByte == '3'){
     return 4;
    }else if(inByte == '0'){
      return 1;
    }
}
}

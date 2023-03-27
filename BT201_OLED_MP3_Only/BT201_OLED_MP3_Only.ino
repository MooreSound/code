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
const int modeButton = 5;
const int ampOn = 13;
const int ampMute = 12;

unsigned long previousMillis = 0; 
unsigned long previousMillis2 = 0;  

int mode = 10;
int btStatus = 0;
int mp3Status = 0;

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
   pinMode(modeButton, INPUT_PULLUP);
  pinMode(ampOn, OUTPUT);
  pinMode(ampMute, OUTPUT);
 Serial.begin(115200);
  Serial1.begin(115200);

 irrecv.enableIRIn(); // Start the receiver

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)// Check your I2C address and enter it here, in Our case address is 0x3C
     display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  resetBT201();
   mode = getMode();
    btStatus = getBTStatus();
    mp3Status = getMP3Status();
    delay(300);
}

void loop() {
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 3000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    mode = getMode();
    delay(50);
     display.clearDisplay(); 
  }

 if (currentMillis - previousMillis2 >= 1000) {
   // save the last time you blinked the LED
    previousMillis2 = currentMillis;
  switch(mode){
 /*   case 2:
       display.setCursor(20, 00);
     display.print("Bluetooth     ");
      display.display();
    btStatus = getBTStatus();
     break;*/
     case 3:
      display.setCursor(20, 00);
     display.print("USB Play     ");
     display.display();
     mp3Status = getMP3Status();
     break;
     case 4:
      display.setCursor(20, 00);
     display.print("SD Card Play");
     display.display();
     mp3Status = getMP3Status();
     break;
     case 10:
       digitalWrite(ampOn, LOW);
      digitalWrite(ampMute, HIGH);
      display.setCursor(20, 00);
     display.print("Power Off    ");
     display.display(); 
     break;
  }
  delay(50);
 }
 /* if(mode == 2){
   switch(btStatus){
        case 3:
      digitalWrite(ampOn, HIGH);
      digitalWrite(ampMute, LOW);
       display.setCursor(20, 20);
     display.print("BT Active    ");
     display.display(); 
    break;
    case 2:
       digitalWrite(ampOn, LOW);
       digitalWrite(ampMute, HIGH);
       display.setCursor(20, 20);
    display.print("Paused      ");
    display.display();  
    break;
    case 4:
       digitalWrite(ampOn, HIGH);
      digitalWrite(ampMute, LOW);
       display.setCursor(20, 20);
    display.print("Incoming call:");
    display.setCursor(20, 28);
    display.print(getPhoneNumber());
    display.display(); 
   break;
    case 1:
       digitalWrite(ampOn, LOW);
      digitalWrite(ampMute, HIGH);
       display.setCursor(20, 20);
    display.print("Disconnected   ");
    display.display(); 
    break;
    }
    delay(50);
 }*/
if(mode == 3 || mode == 4){
    /* switch(mp3Status){
    case 3:*/
      digitalWrite(ampOn, HIGH);
      digitalWrite(ampMute, LOW);
       display.setCursor(0, 10);
     display.print("Playing ");
     displayMP3Info();
     display.display(); 
 //   break;
   /* case 2:
       digitalWrite(ampOn, LOW);
       digitalWrite(ampMute, HIGH);
       display.setCursor(0, 10);
    display.print("Paused ");
    display.display();  
    break;
  /*  case 1:
       digitalWrite(ampOn, LOW);
       digitalWrite(ampMute, HIGH);
       display.setCursor(0, 10);
    display.print("Stopped ");
    display.display();  
    break;*/
 // }
  delay(50);
  }
   
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    switch(results.value){

       case 0xFFE21D:
        if(mode == 10){
        resetBT201();
      }else{
      setMode(0);
      mode = getMode();
    delay(200);
     display.clearDisplay();
      } 
      break;

       case 0xFFA25D:
        if(mode == 10){
        resetBT201();
      }else{
      setMode(8);
      }
      break;
      
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
      displayVol();
      break;

      case 0xFFA857:
      volUp();
      displayVol();
      break;

      default:
      break;

    }
    irrecv.resume(); // Receive the next value
    }
    
    
  
  if(digitalRead(playButton) == LOW){
    if(mode == 10){
        resetBT201();
      }else {
   playPause();
   delay(200);
      }
  }else if(digitalRead(nextButton) == LOW){
   nextTrack();
   delay(200);
  }else if(digitalRead(prevButton) == LOW){
    prevTrack();
    delay(200);
  }else if(digitalRead(volUpButton) == LOW){
   volUp();
   displayVol();
   delay(200);
  }else if(digitalRead(volDnButton) == LOW){
   volDown();
   displayVol();
   delay(200);
  } else if(digitalRead(modeButton) == LOW){
    if(mode == 10){
        resetBT201();
      }else{
    setMode(0);
    mode = getMode();
    delay(200);
     display.clearDisplay(); 
      }
  } 

}

void displayMP3Info(){ 
  
char buffer [16];
char buffer2 [16];
int currentFile, totalFiles;
long currentPlayTime, totalPlayTime;

display.setCursor(0,20);
display.print(getMP3FileName());
delay(50);
currentFile = getCurrentFile();
delay(50);
totalFiles = getTotalFiles();
delay(50);
currentPlayTime = getCurrentPlayTime();
delay(50);
totalPlayTime = getTotalPlayTime();
delay(50);

sprintf (buffer, "%06d/%06d", currentFile, totalFiles);
delay(50);

int progress = map(currentPlayTime, 0, totalPlayTime, 0, 128);
display.fillRect(0, 58, progress, 64, WHITE);

display.setCursor(48,10);
display.print(buffer);


  display.display(); 
}


void displayVol(){
  int volLevel = map(getVolume(), 0, 30, 0, 128);
   display.setCursor(20, 50);
     display.print("Volume: ");
     display.print(getVolume());
     display.print(" ");
     display.fillRect(0, 58, volLevel, 64, WHITE);
     display.display(); 

}

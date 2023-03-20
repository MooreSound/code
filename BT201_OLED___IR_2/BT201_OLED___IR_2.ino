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

unsigned long previousMillis = 0;  

int mode;
int btStatus;

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
   mode = getMode();
    btStatus = getBTStatus();
}

void loop() {
   unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 2000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    mode = getMode();
    delay(200);
    btStatus = getBTStatus();
     display.clearDisplay(); 
  }

  switch(mode){
    case 2:
       display.setCursor(20, 00);
     display.print("Bluetooth     ");
     display.display(); 
     break;
     case 3:
      digitalWrite(ampOn, HIGH);
      digitalWrite(ampMute, LOW);
      display.setCursor(20, 00);
     display.print("USB Play     ");
     display.display(); 
     break;
     case 4:
      digitalWrite(ampOn, HIGH);
      digitalWrite(ampMute, LOW);
      display.setCursor(20, 00);
     display.print("SD Card Play");
     display.display(); 
     break;
     case 10:
       digitalWrite(ampOn, LOW);
      digitalWrite(ampMute, HIGH);
      display.setCursor(20, 00);
     display.print("Power Off    ");
     display.display(); 
  }

  if(mode == 2){
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
  }
   
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    switch(results.value){

       case 0xFFE21D:
       mode++;
      setMode(0);
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

}

void playPause(){

   Serial1.println("AT+CB");
    delay(100);

}

void nextTrack(){
   Serial1.println("AT+CC");
    delay(100);
}

void prevTrack(){
   Serial1.println("AT+CD");
    delay(100);
}
void volUp(){
Serial1.println("AT+CE");
    delay(100);
    display.setCursor(20, 50);
     display.print("Volume: ");
     display.print(getVolume());
     display.print("    ");
     display.display(); 
     delay(100);
}
void volDown(){
 
Serial1.println("AT+CF");
    delay(100);
     display.setCursor(20, 50);
     display.print("Volume: ");
     display.print(getVolume());
     display.print("    ");
     display.display(); 
     delay(100);
}

void setMode(int mode){
  switch(mode){
    case 0:
  Serial1.println("AT+CM00");
  break;
    case 1:
  Serial1.println("AT+CM01");
  break;
    case 2:
  Serial1.println("AT+CM02");
  break;
    case 3:
  Serial1.println("AT+CM03");
  break;
    case 4:
  Serial1.println("AT+CM04");
  break;
    case 5:
  Serial1.println("AT+CM05");
  break;
    case 7:
  Serial1.println("AT+CM07");
  break;
    case 8:
  Serial1.println("AT+CM08");
  break;
  default:
  break;
}
delay(100);
}

int getBTStatus(){
String readStatus;
  Serial1.println("AT+TS");
  delay(100);
   while (Serial1.available() > 0) {
    char cs = Serial1.read();
    if (cs == '+') {
      if (readStatus.length() >0) {
        Serial.println(readStatus); //prints string to serial port out

        int ns = readStatus.toInt();  //convert readString into a number
        if(ns == 2 || ns == 4){
      return 3;
    }else if(ns == 1){
     return 2;
     }else if(ns == 3){
     return 4;
    }else if(ns == 0){
      return 1;
    }

        readStatus=""; //clears variable for new input
      }
    }  
    else {     
      readStatus += cs; //makes the string readString
    }
   
}
}

int getMode(){
String readMode;
  Serial1.println("AT+QM");
  delay(100);
   while (Serial1.available() > 0) {
    char cm = Serial1.read();
    if (cm == '+') {
      if (readMode.length() >0) {
        Serial.println(readMode); //prints string to serial port out

        int nm = readMode.toInt();  //convert readString into a number
        if(nm == 0){
      return 1;
    }else if(nm == 1){
     return 2;
     }else if(nm == 2){
     return 3;
    }else if(nm == 3){
      return 4;
    }else if(nm == 4){
      return 5;
    }else if(nm == 5){
      return 6;
    }else if(nm == 6){
      return 7;
    }else if(nm == 7){
      return 8;
    }else if(nm == 8){
      return 9;
    }else if(nm == 9){
      return 10;
    }

        readMode=""; //clears variable for new input
      }
    }  
    else {     
      readMode += cm; //makes the string readString
    }
   
}
}

int getVolume(){
String readVol;
  Serial1.println("AT+QA");
  delay(100);
   while (Serial1.available() > 0) {
    char cv = Serial1.read();
    if (cv == '+') {
      if (readVol.length() >0) {
        Serial.println(readVol); //prints string to serial port out

        int nv = readVol.toInt();  //convert readString into a number
    return nv;

        readVol=""; //clears variable for new input
      }
    }  
    else {     
      readVol += cv; //makes the string readString
    }
   
}
delay(50);
}

long getPhoneNumber(){
String readNumber;
  Serial1.println("AT+TT");
  delay(100);
   while (Serial1.available() > 0) {
    char cn = Serial1.read();
    if (cn == '+') {
      if (readNumber.length() >0) {
        Serial.println(readNumber); //prints string to serial port out

        long phn = readNumber.toFloat();  //convert readString into a number
    return phn;

        readNumber=""; //clears variable for new input
      }
    }  
    else {     
      readNumber += cn; //makes the string readString
    }
   
}
delay(50);
}

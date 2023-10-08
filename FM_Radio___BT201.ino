/*
   MCP42100 Dual 100K Digital Pot Demo
   Based on examples at https://wiki.dfrobot.com/Dual_Digital_Pot__100K__SKU__DFR0520
   Slowly adjusts pot wipers between min and max (0-255)
   to allow measuring the resistance from the wiper to
   one of the end terminals and to observe the operation of the device.
   Wiper setting is displayed on the serial monitor for confirmation.
   Arduino Uno SPI connections:
   Uno            MCP42100
   -------------------------
   D2            CS  (pin 1)
   D11 (MOSI)    SI  (pin 3)
   D13 (SCK)     SCK (pin 2)
   Gadget Reboot
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
#include <Si4703_Breakout.h>

const int adc0 = A0;
const int adc1 = A1;
const int adc2 = A2;
const int powerLED = 10;
const int snoozeLED = 9;
const int asInhibit = 46;
const int asSelectA = 47;
const int asSelectB = 5;
const int ampEnable = 4;

const byte csPin           = 53;       // MCP42100 chip select pin
const int  maxPositions    = 256;     // wiper can move from 0 to 255 = 256 positions
const long rAB             = 100000;  // 100k pot resistance between terminals A and B
const byte rWiper          = 125;     // 125 ohms pot wiper resistance
const byte pot0            = 0x11;    // pot0 addr
const byte pot1            = 0x12;    // pot1 addr
const byte potBoth         = 0x13;    // pot0 and pot1 simultaneous addr
const byte pot0Shutdown    = 0x21;    // pot0 shutdown
const byte pot1Shutdown    = 0x22;    // pot1 shutdown
const byte potBothShutdown = 0x23;    // pot0 and pot1 simultaneous shutdown

const int resetPin = 48;
const int SDIO = 20;
const int SCLK = 21;


int channel = 893;
char rdsBuffer[10];

int volume = 10;
int adc0Value = 1023;
int adc1Value = 1023;
int adc2Value = 1023;
int brightness = 255;
int audioMode = 0;
int prevAudioMode = 0;

#define volDownButton 44             
#define volUpButton 45
#define channelDown 42
#define channelUp 43

float tempF = 0;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Si4703_Breakout radio(resetPin, SDIO, SCLK);
RTC_DS3231 rtc;

void setup() {
pinMode(asInhibit, OUTPUT);
   pinMode(asSelectA, OUTPUT);
    pinMode(asSelectB, OUTPUT);
    digitalWrite(asInhibit, HIGH);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, HIGH);
pinMode(ampEnable, OUTPUT);
 digitalWrite(ampEnable, LOW);
   
 pinMode(adc0, INPUT_PULLUP);
 pinMode(adc1, INPUT_PULLUP);
 pinMode(adc2, INPUT_PULLUP);
 pinMode(powerLED, OUTPUT);
 pinMode(snoozeLED, OUTPUT);
 digitalWrite(snoozeLED, HIGH);

Serial.begin(115200);
  Serial1.begin(115200);
   pinMode(volDownButton, INPUT_PULLUP);        
  pinMode(volUpButton, INPUT_PULLUP);
  pinMode(channelUp, INPUT_PULLUP);
  pinMode(channelDown, INPUT_PULLUP);  
  
  digitalWrite(csPin, HIGH);        // chip select default to de-selected
  pinMode(csPin, OUTPUT);           // configure chip select as output
  SPI.begin();

int volumeScaled = map(volume, 0, 30, 0, 255);

setPotWiper(potBoth, volumeScaled);
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)// Check your I2C address and enter it here, in Our case address is 0x3C
     display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);


   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
         display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  draw_text(0, 0, "RTC Error", 1);
  draw_text(0, 12, "Check Connections", 1);
  display.display(); // this command will display all the data which is in buffer
  
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");

  display.clearDisplay();
  draw_text(0, 0, "Check CMOS Battery", 1);
  display.display(); // this command will display 
   
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  radio.powerOn();
  radio.setVolume(0);

         display.clearDisplay();
  display.display(); // this command will display 
delay(500);

}

void loop() {
  display.clearDisplay();
   adc0Value = analogRead(adc0);
 adc1Value = analogRead(adc1);
 adc2Value = analogRead(adc2);
int volumeScaled = map(volume, 0, 30, 0, 255);

 DateTime now = rtc.now();
  /*============Display Date=================*/
display.setTextSize(1);
display.setCursor(0,0);
display.print(daysOfTheWeek[now.dayOfTheWeek()]);

char currentDate [16];
uint8_t thisDay, thisMonth ;
thisDay = now.day();
thisMonth = now.month();
sprintf (currentDate, "%02d/%02d/", thisMonth, thisDay); //add leading zeros to the day and month

display.setTextSize(1);
display.setCursor(62,0);
display.print(currentDate);

display.setTextSize(1);
display.setCursor(102,0);
display.print(now.year(), DEC);


/*================Display Time================*/ 
char buffer [16];
uint8_t thisSec, thisMin, thisHour;
thisSec = now.second();
thisMin = now.minute();
if(now.hour() >= 13){
thisHour = now.hour() - 12;
}else if(now.hour() == 0){
thisHour = 12;
}else {
  thisHour = now.hour();
}
sprintf (buffer, "%02d:%02d", thisHour, thisMin);

display.setTextSize(2);
display.setCursor(12,9);
display.print(buffer);
if(now.hour() >= 12){
display.print(" PM");
}else {
display.print(" AM");
}




if (audioMode == 1){
  digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, LOW);
      digitalWrite(ampEnable, HIGH);
      display.setCursor(20, 35);
       display.setTextSize(1); // Draw 2X-scale text
    display.print("BT Active               ");
} else if (audioMode == 3){
   display.setCursor(20, 35);
    display.setTextSize(1); // Draw 2X-scale text
    display.print("AUX Active");
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, LOW);
       digitalWrite(ampEnable, HIGH);
}else if (audioMode == 2){
 displayInfo();
}

 if(adc0Value <= 20){
  if (audioMode == 0){
    audioMode = prevAudioMode;
    analogWrite(powerLED, brightness);
    digitalWrite(ampEnable, HIGH);
    display.setCursor(20, 35);
    display.print("                            ");
    display.display(); 
    setPotWiper(potBoth, volumeScaled);
    radio.setVolume(15);
  }else{
    prevAudioMode = audioMode;
    audioMode = 0;
    analogWrite(powerLED, 0);
  display.setCursor(20, 35);
    display.print("Audio Off              ");
    display.display(); 
 digitalWrite(asInhibit, HIGH);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, HIGH);
      digitalWrite(ampEnable, LOW);
      setPotWiper(potBothShutdown, 0);
      radio.setVolume(0);
        Serial1.println("AT+CM10");
    delay(300);
  }
  Serial.println("Power");
    delay(100);
  } else if(digitalRead(volUpButton) == LOW){
   volUp();
    Serial.println("Volume Up");
    delay(100);
  }else if(digitalRead(volDownButton) == LOW){
     
   volDown();
    Serial.println("Volume Down");
    delay(100);
  }else if(adc0Value > 190 && adc0Value < 219){
    Serial.println("Bedtime");
    delay(100);
  }else if(adc0Value > 300 && adc0Value < 325){
    Serial.println("Time Set");
    delay(100);
  }
  if(adc1Value <= 20){
    analogWrite(powerLED, brightness);
    audioMode++;
    setPotWiper(potBoth, volumeScaled);
    if (audioMode == 1){
  digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, LOW);
      digitalWrite(ampEnable, HIGH);
      radio.setVolume(0);
      Serial1.println("AT+CM01");
    delay(300);
     display.setTextSize(1); // Draw 2X-scale text
      display.setCursor(20, 35);
    display.print("BT Active               ");
}else if (audioMode == 2){
   display.setCursor(20, 45);
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, LOW);
      digitalWrite(asSelectB, HIGH);
       digitalWrite(ampEnable, HIGH);
            Serial1.println("AT+CM10");
    delay(300);
  radio.powerOn();
  radio.setVolume(15);
   radio.setChannel(channel);
    displayInfo();
}  
else if (audioMode == 3){
   display.setCursor(20, 35);
    display.setTextSize(1); // Draw 2X-scale text
    display.print("AUX Active");
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, LOW);
       digitalWrite(ampEnable, HIGH);
       radio.setVolume(0);
          Serial1.println("AT+CM10");
    delay(300);
}else if (audioMode == 4){
  audioMode = 1;
}
    Serial.println("Mode/EQ");
    delay(100);
  } else if(digitalRead(channelUp) == LOW){
     if (audioMode == 1){
  nextTrack();
}else if (audioMode == 2){
    channel = radio.seekUp();
    displayInfo();
    Serial.println("Tune Up");
    delay(100);
  }
  }else if(adc1Value > 129 && adc1Value < 145){
    Serial.println("Wakeup");
    delay(100);
  }else if(adc1Value > 198 && adc1Value < 215){
    brightness = brightness - 20;
    if(brightness < 0){
      brightness = 255;
    }
    analogWrite(snoozeLED, brightness);
    Serial.println("Snooze/Dimmer");
    delay(100);
  }
if(adc2Value <= 20){
    Serial.println("Alarm 1");
    delay(100);
  } else if(adc2Value > 68 && adc2Value < 76){
    Serial.println("Alarm 2");
    delay(100);
  }else if(digitalRead(channelDown) == LOW){
   if (audioMode == 1){
  prevTrack();
}else if (audioMode == 2){
    channel = radio.seekDown();
    displayInfo();
    
    Serial.println("Tune Down");
    delay(100);
  }
  }else if(adc2Value > 196 && adc2Value < 215){
  audioMode = 1;
  setPotWiper(potBoth, volumeScaled);
    playPause();
    Serial.println("Play/Pause");
    delay(100);
  }else{
    
  }

display.display(); 
delay(200);
}

void setAudioSource(int s){
  if(s = 0){
    digitalWrite(asInhibit, HIGH);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, HIGH);

  } else if(s = 1){
    digitalWrite(asInhibit, HIGH);
     digitalWrite(asSelectA, LOW);
      digitalWrite(asSelectB, HIGH);
  } else if(s = 2){
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, LOW);
      digitalWrite(asSelectB, HIGH);
  }  else if(s = 3){
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, HIGH);

  }else if(s = 4){
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelectA, HIGH);
      digitalWrite(asSelectB, HIGH);

  }

 delay(100);
}

void setPotWiper(int addr, int pos) {

  pos = constrain(pos, 0, 255);            // limit wiper setting to range of 0 to 255

  digitalWrite(csPin, LOW);                // select chip
  SPI.transfer(addr);                      // configure target pot with wiper position
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);               // de-select chip
}

void draw_text(byte x_pos, byte y_pos, char *text, byte text_size) {
  display.setCursor(x_pos, y_pos);
  display.setTextSize(text_size);
  display.print(text);
}

void playPause(){
   Serial1.println("AT+CB");
    delay(300);
}

void nextTrack(){
   Serial1.println("AT+CC");
    delay(300);
}

void prevTrack(){
   Serial1.println("AT+CD");
    delay(300);
}
void volUp(){
int volumeScaled = map(volume, 0, 30, 0, 255);
display.setCursor(20, 55);
    display.print("Volume: ");
    if(volume < 10){
      display.print("0");
    }
    display.print(volume);
    display.display(); 
  
  volume++;
  if(volume >= 30){
    volume = 30;
  }
  setPotWiper(potBoth, volumeScaled);
}
void volDown(){
int volumeScaled = map(volume, 0, 30, 0, 255);
 display.setCursor(20, 55);
    display.print("Volume: ");
    if(volume < 10){
      display.print("0");
    }
    display.print(volume);
    display.display(); 
  
  volume--;
  if(volume <= 0){
    volume = 0;
    setPotWiper(potBothShutdown, 0);
  }
  setPotWiper(potBoth, volumeScaled);
}

void displayInfo()
{
  display.setCursor(20, 35);
  display.setTextSize(1); // Draw 2X-scale text
   display.print("Channel:");
display.println((float)channel/10, 1); 
   display.setCursor(24, 55);
    radio.readRDS(rdsBuffer, 1000);
      display.println(rdsBuffer);    
   display.display();      // Show initial text
 
}

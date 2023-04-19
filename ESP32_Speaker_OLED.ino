/*
  Streaming data from Bluetooth to internal DAC of ESP32
  
  Copyright (C) 2020 Phil Schatzmann
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// ==> Example to use built in DAC of ESP32

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#include "BluetoothA2DPSink.h"
#include <TTS.h>

// Media pins
#define PWM 25

BluetoothA2DPSink a2dp_sink;
TTS text2speech(PWM); 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const byte csPin           = 5;       // MCP42100 chip select pin
const int  maxPositions    = 256;     // wiper can move from 0 to 255 = 256 positions
const long rAB             = 100000;  // 100k pot resistance between terminals A and B
const byte rWiper          = 125;     // 125 ohms pot wiper resistance
const byte pot0            = 0x11;    // pot0 addr
const byte pot1            = 0x12;    // pot1 addr
const byte potBoth         = 0x13;    // pot0 and pot1 simultaneous addr
const byte pot0Shutdown    = 0x21;    // pot0 shutdown
const byte pot1Shutdown    = 0x22;    // pot1 shutdown
const byte potBothShutdown = 0x23;    // pot0 and pot1 simultaneous shutdown

const int INPUT_PIN = 34;

const int LED = 2;
const int dacMute = 13;

const int asInhibit = 4;
const int asSelect = 15;

int volume = 20;

bool is_active = false;
bool Connected = false;

unsigned long previousMillis = 0; 

String songTitle;
String artistName;
String albumName;




 void avrc_metadata_callback(uint8_t id, const uint8_t *text) {
    switch (id) {
        case ESP_AVRC_MD_ATTR_TITLE:
           songTitle = (char*) text;
            break;
        case ESP_AVRC_MD_ATTR_ARTIST:
            artistName = (char*) text;
            break;
    } 
    Serial.println( songTitle);
    Serial.println(artistName);
}



void setup() {
  pinMode(asInhibit, OUTPUT);
   pinMode(asSelect, OUTPUT);
  
   pinMode(INPUT_PIN, INPUT_PULLUP);
    digitalWrite(csPin, HIGH);        // chip select default to de-selected
  pinMode(csPin, OUTPUT);  
  pinMode(dacMute, OUTPUT); 
  SPI.begin();
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
 display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("ESP32 BT Audio");
  display.println("Initializing...");
  display.display();
  
  pinMode(LED, OUTPUT);
  int volumeScaled = map(volume, 0, 30, 0, 255);
 
   setPotWiper(potBoth, volumeScaled);
  setAudioSource(2);
  text2speech.setPitch(4);
  text2speech.sayText("Power On"); 


  i2s_pin_config_t my_pin_config = {
        .bck_io_num = 32,
        .ws_io_num = 12,
        .data_out_num = 27,
        .data_in_num = I2S_PIN_NO_CHANGE
    };
    a2dp_sink.set_pin_config(my_pin_config);
  
  const i2s_config_t i2s_config = {
      .mode = (i2s_mode_t) (I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = 44100, // corrected by info from bluetooth
      .bits_per_sample = (i2s_bits_per_sample_t) 32, /* the DAC module will only take the 8bits from MSB */
      .channel_format =  I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = (i2s_comm_format_t)I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0, // default interrupt priority
      .dma_buf_count = 8,
      .dma_buf_len = 64,
      .use_apll = false
  };

  a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
  a2dp_sink.set_avrc_metadata_attribute_mask(ESP_AVRC_MD_ATTR_TITLE | ESP_AVRC_MD_ATTR_ARTIST | ESP_AVRC_MD_ATTR_ALBUM);
  a2dp_sink.set_i2s_config(i2s_config);  
  a2dp_sink.start("ESP32 Audio");
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("ESP32 BT Audio");
  display.println("Ready to connect");
  display.display();
  announce("Ready to connect"); 
  delay(100);  

}


void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 3000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    displayData();
    }
  if (a2dp_sink.is_connected() == true ){
    if(Connected == false){
    Connected = true;
    Serial.println("Bluetooth Connected");
    display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("ESP32 BT Audio");
  display.println("Connected.");
  display.display();
    digitalWrite(LED, HIGH);
    announce("Bluetooth is connected"); 
     a2dp_sink.set_volume(0x7F);
    delay(2000);
    digitalWrite(LED, LOW);
    }
  }else{
    if(Connected == true){
    Connected = false;
     announce("Bluetooth is disconnected"); 
     delay(50);
    }
     mute();
    Serial.println("Bluetooth Disconnected");
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  }
  if( a2dp_sink.get_audio_state()==ESP_A2D_AUDIO_STATE_STARTED){
    //Serial.println("Bluetooth Active");
    digitalWrite(LED, HIGH);
    
    if(volume == 0){
   mute();
  }else{
    unmute();
  }
    is_active = true;
  }else{
    digitalWrite(LED, LOW);
     mute();
    is_active = false;
  }

  
  
if(readAnalogButton() == 2){
  digitalWrite(LED, LOW);
    Serial.println("changing state...");
    if (is_active == false){
      Serial.println("play");
       setAudioSource(1);
       unmute();
      a2dp_sink.play();
    } else {
      
      Serial.println("pause");
      mute();
      a2dp_sink.pause();
    }
    delay(50);
}
else if(readAnalogButton() == 1){
  digitalWrite(LED, LOW);
  a2dp_sink.next();
  delay(50);
}
else if(readAnalogButton() == 3){
  digitalWrite(LED, LOW);
  a2dp_sink.previous();
  delay(50);
}
else if(readAnalogButton() == 4){
  volUp();
  displayVol();
  digitalWrite(LED, LOW);
  Serial.print("Volume: ");
  Serial.println(volume);
  if (is_active == false){
    digitalWrite(LED, HIGH);
       setAudioSource(2);
      announce("Volume:");
       sayNumber(volume);
    }
  delay(50);
}
else if(readAnalogButton() == 5){
  volDown();
  displayVol();
  digitalWrite(LED, LOW);
  Serial.print("Volume: ");
  Serial.println(volume);
   if (is_active == false){
    digitalWrite(LED, HIGH);
       announce("Volume:");
       sayNumber(volume);
    }
  delay(50);
}
/*else if(readAnalogButton() == 6){
 announce("Now Playing:");
 announce(artistName);
}*/

  

delay(50);
}

void announce(char* text){
  setAudioSource(2);
  text2speech.sayText(text);
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
   mute();
  }
   setPotWiper(potBoth, volumeScaled);
  }

  void mute(){
    setPotWiper(potBothShutdown, 0);
    digitalWrite(dacMute, LOW);
    setAudioSource(0);
  }

  void unmute(){
 int volumeScaled = map(volume, 0, 30, 0, 255);
 
   setPotWiper(potBoth, volumeScaled);
   digitalWrite(dacMute, HIGH);
  }

void setPotWiper(int addr, int pos) {

  pos = constrain(pos, 0, 255);            // limit wiper setting to range of 0 to 255

  digitalWrite(csPin, LOW);                // select chip
  SPI.transfer(addr);                      // configure target pot with wiper position
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);               // de-select chip
}
void displayVol(){
   display.setCursor(0,48);             // Start at top-left corner
  display.print("Volume: ");
  display.println(volume);
 int volumeScaled = map(volume, 0, 30, 0, 128);
 display.fillRect(0, 58, volumeScaled, 64, SSD1306_WHITE);
  display.display();
}

void displayData(){
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println("ESP32 BT Audio");
   display.setCursor(0,24);             // Start at top-left corner
  display.print("Song: ");
  display.println(songTitle);
   display.print("Artist: ");
  display.println(artistName);
  display.display();
}

int readAnalogButton() {
  int button = analogRead(INPUT_PIN);
  if (button > 4000) return 0;
  if (button < 100) return 1;
  if (button < 1900) return 2;
  if (button < 2600) return 3;
  if (button < 2900) return 4;
  if (button < 3200) return 5;
  if (button < 3400) return 6;
}

void setAudioSource(int s){
  if(s == 0){
    digitalWrite(asInhibit, HIGH);
     digitalWrite(asSelect, LOW);
  } else if(s == 1){
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelect, LOW);

}else if(s == 2){
    digitalWrite(asInhibit, LOW);
     digitalWrite(asSelect, HIGH); 
}
}
void sayNumber(long n) {
  if (n<0) {
text2speech.sayText("Negative");
    sayNumber(-n);
  } else if (n==0) {
    text2speech.sayText("0");
  } else {
    if (n>=1000) {
      int thousands = n / 1000;
      sayNumber(thousands);
     text2speech.sayText("Thousand");
      n %= 1000;
      if ((n > 0) && (n<100));
    }
    if (n>=100) {
      int hundreds = n / 100;
      sayNumber(hundreds);
      text2speech.sayText("Hundred");
      n %= 100;
      if (n > 0);
    }
    if (n>19) {
      int tens = n / 10;
      switch (tens) {
        case 2: text2speech.sayText("Twenty"); break;
        case 3: text2speech.sayText("Thirty"); break;
        case 4: text2speech.sayText("Forty");  break;
        case 5: text2speech.sayText("Fifty"); break;
        case 6: text2speech.sayText("Sixty"); break;
        case 7: text2speech.sayText("Seventy"); break;
        case 8: text2speech.sayText("Eighty"); break;
        case 9: text2speech.sayText("Ninety"); break;
      }
      n %= 10;
    }
    switch(n) {
      case 1: text2speech.sayText("1"); break;
      case 2: text2speech.sayText("2"); break;
      case 3: text2speech.sayText("3"); break;
      case 4: text2speech.sayText("4"); break;
      case 5: text2speech.sayText("5"); break;
      case 6: text2speech.sayText("6"); break;
      case 7: text2speech.sayText("7"); break;
      case 8: text2speech.sayText("8"); break;
      case 9: text2speech.sayText("9"); break;
      case 10: text2speech.sayText("Ten"); break;
      case 11: text2speech.sayText("Eleven"); break;
      case 12: text2speech.sayText("Twelve"); break;
      case 13: text2speech.sayText("Thirteen"); break;
      case 14: text2speech.sayText("Fourteen");break;
      case 15: text2speech.sayText("Fifteen"); break;
      case 16: text2speech.sayText("Sixteen"); break;
      case 17: text2speech.sayText("Seventeen"); break;
      case 18: text2speech.sayText("Eighteen"); break;
      case 19: text2speech.sayText("Nineteen"); break;
    }
  }
}

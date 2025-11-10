#include <AudioLogger.h>
#include <AudioTools.h>
#include <AudioToolsConfig.h>

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
//#include "audiodata.h"
#include "BluetoothA2DPSink.h"
#include "driver/i2s.h"

// Media pins

/*const unsigned int bluetoothConn_raw_len = 43600;    //CONN
const unsigned int bluetoothDisconn_raw_len = 55730; //DISCONN
const i2s_port_t I2S_PORT = I2S_NUM_0;
const unsigned char *ConnRawFile=bluetoothConn_raw;       //CONN
const unsigned char *DisconnRawFile=bluetoothDisconn_raw; //DISCONN*/
I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);
esp_a2d_connection_state_t last_state;
//unsigned const char* AudioData;
//bool playmsg;

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
const int INPUT_PIN2 = 35;

const int LED1 = 2;
const int LED2 = 12;
const int dacMute = 13;
const int UARTready = 4;


int volume = 20;

bool is_active = false;
bool Connected = false;

String songTitle;
String artistName;

#define RXD2 16
#define TXD2 17





 void avrc_metadata_callback(uint8_t id, const uint8_t *text) {
    switch (id) {
        case ESP_AVRC_MD_ATTR_TITLE:
           songTitle = (char*) text;
            break;
        case ESP_AVRC_MD_ATTR_ARTIST:
            artistName = (char*) text;
            break;
    }  digitalWrite(UARTready, LOW);
    Serial.println( songTitle);
    Serial2.println( songTitle);
    Serial.println(artistName);
    digitalWrite(UARTready, HIGH);
}



void setup() {
   pinMode(INPUT_PIN, INPUT_PULLUP);
   pinMode(INPUT_PIN2, INPUT_PULLUP);
    digitalWrite(csPin, HIGH);        // chip select default to de-selected
  pinMode(csPin, OUTPUT);  
  pinMode(dacMute, OUTPUT); 
  pinMode(UARTready, OUTPUT); 
  SPI.begin();
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(UARTready, HIGH);
  int volumeScaled = map(volume, 0, 30, 0, 255);
 
   setPotWiper(potBoth, volumeScaled);
   delay(1000);
  digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);



 

  a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
  a2dp_sink.set_avrc_metadata_attribute_mask(ESP_AVRC_MD_ATTR_TITLE | ESP_AVRC_MD_ATTR_ARTIST); 
  a2dp_sink.set_auto_reconnect(true);
  a2dp_sink.start("ESP32 Audio");
  delay(100);  

}


void loop() {
  if (a2dp_sink.is_connected() == true ){
    if(Connected == false){
    Connected = true;
    digitalWrite(UARTready, LOW);
    Serial.println("Bluetooth Connected");
    Serial2.println("Bluetooth Connected");
    delay(50);
    digitalWrite(LED1, HIGH);
    digitalWrite(UARTready, HIGH);
    //playAudio(1);
     a2dp_sink.set_volume(0x7F);
    delay(2000);
    }
  }else{
    if(Connected == true){
    Connected = false; 
    //  playAudio(0);
     delay(50);
    }
     digitalWrite(UARTready, LOW);
     mute();
    Serial.println("Bluetooth Disconnected");
    Serial2.println("Bluetooth Disconnected");
    digitalWrite(UARTready, HIGH);
    digitalWrite(LED1, HIGH);
    delay(100);
    digitalWrite(LED1, LOW);
    delay(100);
  }
  if( a2dp_sink.get_audio_state()==ESP_A2D_AUDIO_STATE_STARTED){
    //Serial.println("Bluetooth Active");
    digitalWrite(LED2, HIGH);
    if(volume == 0){
   mute();
  }else{
    unmute();
  }
    is_active = true;
  }else{
    digitalWrite(LED2, LOW);
     mute();
    is_active = false;
  }

  if(Serial2.available()){
    digitalWrite(UARTready, LOW);
    int inByte = Serial2.read();
   
    digitalWrite(LED1, LOW);
    if(inByte == 'p'){
      unmute();
      a2dp_sink.play();
    } else if(inByte == 's'){
      mute();
      a2dp_sink.pause();
    }else if(inByte == 'n'){
      a2dp_sink.next();
    }else if(inByte == 'r'){
      a2dp_sink.previous();
    }else if(inByte == 'u'){
     volUp();
  digitalWrite(LED1, LOW);
  Serial.print("Volume: ");
  Serial.println(volume);
    }else if(inByte == 'd'){
      volDown();
  digitalWrite(LED1, LOW);
  Serial.print("Volume: ");
  Serial.println(volume);
    }
    delay(50);
    digitalWrite(LED1, HIGH);
     digitalWrite(UARTready, HIGH);
  }
  
if(readAnalogButton() == 2){
  digitalWrite(LED1, LOW);
    Serial.println("changing state...");
    if (is_active == false){
      Serial.println("play");
     
       unmute();
      a2dp_sink.play();
    } else {
      
      Serial.println("pause");
      mute();
      a2dp_sink.pause();
    }
     digitalWrite(LED1, HIGH);
    delay(50);
}
else if(readAnalogButton() == 1){
  digitalWrite(LED1, LOW);
  a2dp_sink.next();
  delay(50);
   digitalWrite(LED1, HIGH);
}
else if(readAnalogButton() == 3){
  digitalWrite(LED1, LOW);
  a2dp_sink.previous();
  delay(50);
   digitalWrite(LED1, HIGH);
}
else if(readAnalogButton2() == 1){
  volUp();
  digitalWrite(LED1, LOW);
  Serial.print("Volume: ");
  Serial.println(volume);
    delay(50);
    digitalWrite(LED1, HIGH);
  
}
else if(readAnalogButton2() == 2){
  volDown();
  digitalWrite(LED1, LOW);
  Serial.print("Volume: ");
  Serial.println(volume);
     delay(50);
     digitalWrite(LED1, HIGH);
 
}
  else if(readAnalogButton2() == 3){
    digitalWrite(LED1, LOW);
    delay(50);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  delay(50);
}

delay(50);
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

int readAnalogButton() {
  int button = analogRead(INPUT_PIN);
  if (button > 3900) return 0;
  if (button < 100) return 1;
  if (button < 2000) return 2;
  if (button < 2700) return 3;
  
}
int readAnalogButton2() {
  int button = analogRead(INPUT_PIN2);
  if (button > 3900) return 0;
  if (button < 100) return 1;
  if (button < 2000) return 2;
  if (button < 2700) return 3;
  
}

/*void playAudio(bool type) {
  AudioData = ConnRawFile;
  int len = bluetoothConn_raw_len;
  if (type == 0) {
    AudioData = DisconnRawFile;
    len = bluetoothDisconn_raw_len;
  }
  i2s_set_sample_rates(I2S_PORT, 11025);
  uint32_t index = 0; 
  size_t BytesWritten;
  const unsigned char *Data;
  int rest;
  int byteSize = 4;
 unmute();
   digitalWrite(LED2, HIGH);
  playmsg = 1;
  while (index < len) {
    rest = len - index;
    if (rest < 4){byteSize = rest;}
    Data=AudioData+index;
    i2s_write(I2S_PORT,Data,byteSize,&BytesWritten,portMAX_DELAY); 
    index+=4;
  }
  playmsg = 0;
  i2s_set_sample_rates(I2S_PORT, 44100);
}*/

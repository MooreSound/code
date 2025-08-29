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
#include "audiodata.h"
#include "BluetoothA2DPSink.h"
#include "driver/i2s.h"

// Media pins

const unsigned int bluetoothConn_raw_len = 43600;    //CONN
const unsigned int bluetoothDisconn_raw_len = 55730; //DISCONN
const i2s_port_t I2S_PORT = I2S_NUM_0;
const unsigned char *ConnRawFile=bluetoothConn_raw;       //CONN
const unsigned char *DisconnRawFile=bluetoothDisconn_raw; //DISCONN
BluetoothA2DPSink a2dp_sink;
esp_a2d_connection_state_t last_state;
unsigned const char* AudioData;
bool playmsg;

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
const int LED2 = 14;
const int dacMute = 13;


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
    } 
    Serial.println( songTitle);
    Serial.println(artistName);
}



void setup() {
   pinMode(INPUT_PIN, INPUT_PULLUP);
   pinMode(INPUT_PIN2, INPUT_PULLUP);
    digitalWrite(csPin, HIGH);        // chip select default to de-selected
  pinMode(csPin, OUTPUT);  
  pinMode(dacMute, OUTPUT); 
  SPI.begin();
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  int volumeScaled = map(volume, 0, 30, 0, 255);
 
   setPotWiper(potBoth, volumeScaled);
   delay(1000);
  digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);



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
  a2dp_sink.set_avrc_metadata_attribute_mask(ESP_AVRC_MD_ATTR_TITLE | ESP_AVRC_MD_ATTR_ARTIST);
  a2dp_sink.set_i2s_config(i2s_config);  
  a2dp_sink.start("ESP32 Audio");
  delay(100);  

}


void loop() {
  if (a2dp_sink.is_connected() == true ){
    if(Connected == false){
    Connected = true;
    Serial.println("Bluetooth Connected");
    digitalWrite(LED1, HIGH);
    playAudio(1);
     a2dp_sink.set_volume(0x7F);
    delay(2000);
    }
  }else{
    if(Connected == true){
    Connected = false; 
      playAudio(0);
     delay(50);
    }
     mute();
    Serial.println("Bluetooth Disconnected");
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

void playAudio(bool type) {
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
}

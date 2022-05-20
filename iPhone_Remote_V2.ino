

#include <SPI.h>
#include <IRremote.h>

const int RECV_PIN = 8;

IRrecv irrecv(RECV_PIN);

decode_results results;

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

const int sensePin = A0;
const int LEDPin = 2;
const int pulsePin = 3;

int volume = 15;
// the setup routine runs once when you press reset:
void setup() {
  pinMode(sensePin, INPUT);
  pinMode(LEDPin, OUTPUT);
  pinMode(pulsePin, OUTPUT);
   digitalWrite(csPin, HIGH);        // chip select default to de-selected
  pinMode(csPin, OUTPUT);           // configure chip select as output
  SPI.begin();
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(sensePin);
  Serial.println(sensorValue);

if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    digitalWrite(LEDPin, LOW);
    delay(30);

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

      case 0xFF906F:
      mute();
      break;

      case 0xFF629D:
      voiceCmd();
      break;
      
      default:
      break;

    }
    
    irrecv.resume(); // Receive the next value
}
if(sensorValue >= 350){
  digitalWrite(LEDPin, HIGH);
}
else{
   digitalWrite(LEDPin, LOW);
}
 

}

void setPotWiper(int addr, int pos) {

  pos = constrain(pos, 0, 255);            // limit wiper setting to range of 0 to 255

  digitalWrite(csPin, LOW);                // select chip
  SPI.transfer(addr);                      // configure target pot with wiper position
  SPI.transfer(pos);
  digitalWrite(csPin, HIGH);               // de-select chip
}
void playPause(){
 digitalWrite(pulsePin, HIGH);
 delay(100);
 digitalWrite(pulsePin, LOW);
}

void nextTrack(){
  digitalWrite(pulsePin, HIGH);
 delay(100);
 digitalWrite(pulsePin, LOW);
 delay(100);
 digitalWrite(pulsePin, HIGH);
 delay(100);
 digitalWrite(pulsePin, LOW);
}

void prevTrack(){
   digitalWrite(pulsePin, HIGH);
 delay(100);
 digitalWrite(pulsePin, LOW);
 delay(100); 
 digitalWrite(pulsePin, HIGH);
 delay(100);
 digitalWrite(pulsePin, LOW);
 delay(100);
 digitalWrite(pulsePin, HIGH);
 delay(100);
 digitalWrite(pulsePin, LOW);
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
    setPotWiper(potBothShutdown, 0);
  }
   setPotWiper(potBoth, volumeScaled);
  }

  void mute(){
    setPotWiper(potBothShutdown, 0);
  }

  void voiceCmd(){
    digitalWrite(pulsePin, HIGH);
 delay(1200);
 digitalWrite(pulsePin, LOW);
  }

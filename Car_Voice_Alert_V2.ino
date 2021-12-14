#include <DFRobotDFPlayerMini.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

uint8_t battery[8]  = {B01110, B11111, B11111, B11111, B11111, B11111, B11111, B11111};
uint8_t temp[8]  = {B00100, B00100, B00100, B00100, B00100, B01110, B11111, B01110};
uint8_t frost[8] = {B10101, B01010, B00100, B11111, B00100, B01010, B10101, B00000};
uint8_t battlow[8] = {B01110, B11111, B10001, B10001, B10001, B11001, B11101, B11111};
uint8_t warning[8]  = {B00100, B01010, B10101, B10101, B10001, B10101, B10001, B11111};
uint8_t battfault[8] = {B01110, B11111, B10001, B10101, B10101, B10001, B10101, B11111};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {  0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};


// Media pins
const int voiceActivity = 22;
const int switchPin = 3;  
const int dimmerPin = 13;                         
const int readyPin = 2;
const int LFdoorPin = 26;
const int RFdoorPin = 27;
const int LRdoorPin = 28;
const int RRdoorPin = 29;
const int mwPin = 7;
const int bmsPin = 6;
const int parkPin = 8;
const int brakePin = 5;
const int auderrPin = 9;
const int motionPin = 10;
const int seatbeltPin = 11;
const int lightPin = 12;
const int temperature1Pin = A1;
const int temperature2Pin = A2;
const int temperature3Pin = A3;

int LFdoorState = 0; 
int RFdoorState = 0; 
int LRdoorState = 0; 
int RRdoorState = 0; 
int mwState = 0; 
int bmsState = 0; 
int parkState = 0; 
int brakeState = 0; 
int auderrState = 0; 
int motionState = 0;
int seatbeltState = 0;
int lightState = 0;

boolean ready = false;
boolean lowTemp = false;
boolean mwActive = false;
boolean ampHot = false;
boolean parkActive = false;
boolean battLow = false;
boolean brakeFault = false;
boolean audioFault = false;
boolean bmsFault = false;
boolean demoMode = false;

DFRobotDFPlayerMini myDFPlayer;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() { 
   pinMode(switchPin, OUTPUT);
    pinMode(dimmerPin, OUTPUT);
  pinMode(readyPin, INPUT_PULLUP);
  pinMode(LFdoorPin, INPUT_PULLUP);
   pinMode(RFdoorPin, INPUT_PULLUP);
    pinMode(LRdoorPin, INPUT_PULLUP);
     pinMode(RRdoorPin, INPUT_PULLUP);
  pinMode(mwPin, INPUT_PULLUP);
  pinMode(bmsPin, INPUT_PULLUP);
  pinMode(parkPin, INPUT_PULLUP);
  pinMode(brakePin, INPUT_PULLUP);
  pinMode(auderrPin, INPUT_PULLUP);
  pinMode(motionPin, INPUT_PULLUP);
  pinMode(seatbeltPin, INPUT_PULLUP);
  pinMode(lightPin, INPUT_PULLUP);
   pinMode(24, INPUT_PULLUP);
    pinMode(25, INPUT_PULLUP);
  
    Serial1.begin(9600); 
    Serial.begin(115200);
     lcd.begin();
  lcd.backlight();
     if(lightState == LOW)
  {
  analogWrite(13, 120);  
  } else {
    analogWrite(13, 255);  
  }

  lcd.createChar(0, battery);
  lcd.createChar(1, temp);
  lcd.createChar(2, frost);
  lcd.createChar(3, battlow);
  lcd.createChar(4, warning);
  lcd.createChar(5, battfault);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  lcd.home();

   lcd.print("Initializing...");
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
   lcd.clear();
     lcd.print("Voice Alert");
     lcd.setCursor(0, 1);
    lcd.print("System Fault");
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(20);
  
}

void loop() {
  LFdoorState = digitalRead(LFdoorPin);
  LRdoorState = digitalRead(LRdoorPin);
  RFdoorState = digitalRead(RFdoorPin);
  RRdoorState = digitalRead(RRdoorPin);
  mwState = digitalRead(mwPin);
  bmsState = digitalRead(bmsPin);
  parkState = digitalRead(parkPin);
  brakeState = digitalRead(brakePin);
  auderrState = digitalRead(auderrPin);
  motionState = digitalRead(motionPin);
  seatbeltState = digitalRead(seatbeltPin);
  lightState = digitalRead(lightPin);
  
  // read the input on analog pin 0:
   if(digitalRead(25) == LOW){
    myDFPlayer.volume(20);
  } else {
    myDFPlayer.volume(30);
  }
  int sensorValue = analogRead(A0);
  int batteryLevel = map(sensorValue, 0, 1023, 0, 100);
  // print out the value you read:
  Serial.print("Battery: ");
  Serial.print(batteryLevel);
  Serial.println("%");

   float voltage2, degreesC1, degreesF1;

  voltage2 = getVoltage2(temperature1Pin);

  degreesC1 = (voltage2 - 0.5) * 100.0;


  degreesF1 = degreesC1 * (9.0/5.0) + 32.0;

  Serial.print("Motor Temp: ");
  Serial.print(degreesF1);
  Serial.println("F");
  
   float voltage3, degreesC2, degreesF2;

  voltage3 = getVoltage3(temperature2Pin);

  degreesC2 = (voltage3 - 0.5) * 100.0;


  degreesF2 = degreesC2 * (9.0/5.0) + 32.0;

  Serial.print("Amplifier Temp: ");
  Serial.print(degreesF2);
  Serial.println("F");

    float voltage4, degreesC3, degreesF3;

  voltage4 = getVoltage4(temperature3Pin);

  degreesC3 = (voltage4 - 0.5) * 100.0;


  degreesF3 = degreesC3 * (9.0/5.0) + 32.0;

  Serial.print("Ambient Temp: ");
  Serial.print(degreesF3);
  Serial.println("F");

if(digitalRead(readyPin) == LOW)
  {if(ready == false)
  {ready = true;
  demoMode = false;
   if(lightState == LOW)
  {
  analogWrite(13, 120);  
  } else {
    analogWrite(13, 255);  
  }
  lcd.clear();
  lcd.print("Initializing...");
 if(digitalRead(24) == LOW){
   playMessage(19);
    playMessage(20);
 } else {
   playMessage(31);
    playMessage(31);
     playMessage(31);
    playMessage(31);
     playMessage(31);
    playMessage(31);
 }
  lcd.clear();
     lcd.print("Ready To Drive.");
    playMessage(18);
  }
  }if(ready == true)
  { if(lightState == LOW)
  {
  analogWrite(13, 120);  
  } else {
    analogWrite(13, 255);  
  }
  lcd.clear();
  lcd.write(0);
  lcd.print(batteryLevel);
  lcd.print("%");
  lcd.setCursor(7, 0);
  lcd.write(1);
  lcd.print(degreesF1);
  lcd.print("F");
   lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(degreesF3);
  lcd.print("F");
  
  if(degreesF1 >= 210) 
  { 
    lcd.clear();
    lcd.print("Motor Temp.");
    lcd.setCursor(0, 1);
    lcd.print("Too Hot");
    
    playMessage(31);
    playMessage(1);
  }if(degreesF2 >= 210) 
  {
  if(ampHot == false) 
    {
    ampHot = true;
    lcd.clear();
    lcd.print("Amplifier Temp.");
    lcd.setCursor(0, 1);
    lcd.print("Too Hot");
    
   playMessage(31);
    playMessage(2);
  } 
  }
  if(degreesF3 <= 35) 
  {
    lcd.setCursor(13, 1);
    lcd.write(2);
    if(lowTemp == false) 
    {
    lowTemp = true;
    lcd.clear();
    lcd.print("Ambient Temp.");
    lcd.setCursor(0, 1);
    lcd.print("Low");
    playMessage(31);
    playMessage(4);
    }
  }if(batteryLevel <= 20) 
  {
    lcd.setCursor(0, 0);
    lcd.write(3);
    if(battLow == false) 
    {
    battLow = true;
    digitalWrite(switchPin, HIGH);
    lcd.clear();
    lcd.print("Battery Low");
    lcd.setCursor(0, 1);
    lcd.print("");
     playMessage(31);
    playMessage(3);
  }
  }if(seatbeltState == HIGH && motionState == LOW)
  {
    digitalWrite(switchPin, HIGH);
    lcd.clear();
    lcd.print("Please Fasten");
    lcd.setCursor(0, 1);
    lcd.print("Seatbelt");
    
     playMessage(31);
    playMessage(10);
  }if(LFdoorState == LOW && motionState == LOW)
  {
    lcd.clear();
    lcd.print("Left Front");
    lcd.setCursor(0, 1);
    lcd.print("Door Open");
    playMessage(31);
    playMessage(11);
   
  }if(RFdoorState == LOW && motionState == LOW)
  {
    lcd.clear();
    lcd.print("Right Front");
    lcd.setCursor(0, 1);
    lcd.print("Door Open");
    playMessage(31);
    playMessage(12);
   
  }if(LRdoorState == LOW && motionState == LOW)
  {
    lcd.clear();
    lcd.print("Left Rear");
    lcd.setCursor(0, 1);
    lcd.print("Door Open");
    playMessage(31);
    playMessage(13);
   
  }if(RRdoorState == LOW && motionState == LOW)
  {
    lcd.clear();
    lcd.print("Right Rear");
    lcd.setCursor(0, 1);
    lcd.print("Door Open");
    playMessage(31);
    playMessage(14);
   
  }
  
  if(mwState == LOW)
  {
    lcd.setCursor(14, 1);
    lcd.write(4);
    if(mwActive == false) 
    {
    mwActive = true;
    lcd.clear();
    lcd.print("Master Warning");
    lcd.setCursor(0, 1);
    lcd.print("");
    playMessage(31);
    playMessage(6);
  }
  }if(bmsState == LOW)
  {
    lcd.setCursor(0, 0);
    lcd.write(5);
     if(bmsFault == false) 
    {
    bmsFault = true;
    lcd.clear();
    lcd.print("BMS Fault");
    lcd.setCursor(0, 1);
    lcd.print("");
    playMessage(31);
    playMessage(7);
  }
  }if(parkState == LOW && motionState == LOW)
  {
     if(parkActive == false) 
    {
    parkActive = true;
    lcd.clear();
    lcd.print("Parking Brake");
    lcd.setCursor(0, 1);
    lcd.print("Engaged");
     playMessage(31);
    playMessage(5);
  }
  }if(brakeState == LOW)
  {
    if(brakeFault == false)
  {brakeFault = true;
    lcd.clear();
    lcd.print("Brake System");
    lcd.setCursor(0, 1);
    lcd.print("Fault");
    playMessage(31);
    playMessage(8);;
  }
  }if(auderrState == LOW)
  {
    if(audioFault == false)
  {audioFault = true;
    lcd.clear();
    lcd.print("Audio System");
    lcd.setCursor(0, 1);
    lcd.print("Fault");
    playMessage(31);
    playMessage(9);
  }
  }
  if(motionState == HIGH)
  {
    parkActive = false;
  }
  }if(digitalRead(readyPin) == HIGH)
{ if(ready == true){
  ready = false;
  ampHot = false;
  lowTemp = false;
  mwActive = false;
  battLow = false;
  brakeFault = false;
  audioFault = false;
  bmsFault = false;
  lcd.clear();
}if(lightState == LOW)
  {
    analogWrite(13, 120); 
  lcd.clear();
  lcd.backlight();
  lcd.print("Headlights On");
    playMessage(31);
    playMessage(15);
  }
  
  if(LFdoorState == LOW)
  {
    
   lcd.clear();
    analogWrite(13, 255); 
  lcd.write(0);
  lcd.print(batteryLevel);
  lcd.print("%");
  lcd.setCursor(7, 0);
  lcd.write(1);
  lcd.print(degreesF1);
  lcd.print("F");
   lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(degreesF3);
  lcd.print("F");
  if(batteryLevel <= 20) 
  {
    lcd.setCursor(0, 0);
    lcd.write(3);
  }
  }else 
  {
    lcd.clear();
    analogWrite(13, 0); 
  }
}
  delay(1000);
  
  if(parkState == LOW && LFdoorState == LOW && lightState == LOW && ready == false)
  {
    if (demoMode == false)
    { demoMode = true;
    
    lcd.clear();
    lcd.print("Motor Temp.");
    lcd.setCursor(0, 1);
    lcd.print("Too Hot");
    
      playMessage(31);
    playMessage(1);
    lcd.clear();
    lcd.print("Amplifier Temp.");
    lcd.setCursor(0, 1);
    lcd.print("Too Hot");
      playMessage(31);
    playMessage(2);
    lcd.clear();
    lcd.print("Ambient Temp.");
    lcd.setCursor(0, 1);
    lcd.print("Low");
      playMessage(31);
    playMessage(4);
    lcd.clear();
    lcd.print("Battery Low");
    lcd.setCursor(0, 1);
    lcd.print("");
    
      playMessage(31);
    playMessage(3);
    lcd.clear();
    lcd.print("Please Fasten");
    lcd.setCursor(0, 1);
    lcd.print("Seatbelt");
     playMessage(31);
    playMessage(10);
   lcd.clear();
    lcd.print("Left Front");
    lcd.setCursor(0, 1);
    lcd.print("Door Open");
    playMessage(31);
    playMessage(11);
    lcd.clear();
    lcd.print("Right Front");
    lcd.setCursor(0, 1);
    lcd.print("Door Open");
    playMessage(31);
    playMessage(12);
   
    lcd.clear();
    lcd.print("Left Rear");
    lcd.setCursor(0, 1);
    lcd.print("Door Open");
    playMessage(31);
    playMessage(13);
   
    lcd.clear();
    lcd.print("Right Rear");
    lcd.setCursor(0, 1);
    lcd.print("Door Open");
    playMessage(31);
    playMessage(14);
    lcd.clear();
    lcd.print("Master Warning");
    lcd.setCursor(0, 1);
    lcd.print("");
     playMessage(31);
    playMessage(6);
    lcd.clear();
    lcd.print("BMS Fault");
    lcd.setCursor(0, 1);
    lcd.print("");
     playMessage(31);
    playMessage(7);
    lcd.clear();
    lcd.print("Parking Brake");
    lcd.setCursor(0, 1);
    lcd.print("Engaged");
     playMessage(31);
    playMessage(5);
    lcd.clear();
    lcd.print("Brake System");
    lcd.setCursor(0, 1);
    lcd.print("Fault");
    playMessage(31);
    playMessage(8);
    lcd.clear();
    lcd.print("Audio System");
    lcd.setCursor(0, 1);
    lcd.print("Fault");
    playMessage(31);
    playMessage(9);
  lcd.clear();
  lcd.backlight();
  lcd.print("Headlights On");
    playMessage(31);
    playMessage(15);
     lcd.clear();
     lcd.print("Ready To Drive.");
    playMessage(18);
}
}
}
  

float getVoltage2(int A1)
{

  return (analogRead(A1) * 0.004882814);

  
}

float getVoltage3(int A2)
{

  return (analogRead(A2) * 0.004882814);

  
}

float getVoltage4(int A3)
{

  return (analogRead(A3) * 0.004882814);

  
}

void playMessage(int f) {
  digitalWrite(switchPin, HIGH);
   myDFPlayer.playFolder(1, f);
delay(1000);
   while(digitalRead(voiceActivity)== LOW){
  delay(10);
}
digitalWrite(switchPin, LOW);
}

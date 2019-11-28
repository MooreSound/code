/*
 ###  simplest ever Arduino UNO digital clock  ###

 This clock needs only a 1602 LCD 2X16 and 2 push buttons 

 No Potentiometer for contrast, no resistors for pull-up or backlight !!!!

 * The simplest clock ever made with a Arduino UNO *    

 Button Functions:
 
 - short stroke on one of the buttons put Backlight on for 30 s
 
 Time settings
 - Press on H increments the Hours
 - Press on M increments the Minutes and resets the seconds
*/

#include <english.h>
#include <sound.h>
#include <TTS.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

uint8_t Time[8]  = {B01110, B10001, B10101, B10101, B11101, B10001, B10001, B01110};
uint8_t temp[8]  = {B00100, B00100, B00100, B00100, B00100, B01110, B11111, B01110};
uint8_t light[8] = {B10101, B00000, B01110, B11111, B01110, B00000, B01110, B01110};
uint8_t battlow[8] = {B01110, B11111, B10001, B10001, B10001, B11001, B11101, B11111};
uint8_t warning[8]  = {B00100, B01010, B10101, B10101, B10001, B10101, B10001, B11111};
uint8_t battfault[8] = {B01110, B11111, B10001, B10101, B10101, B10001, B10101, B11111};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {  0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

LiquidCrystal_I2C lcd(0x3F,16,2);
TTS text2speech(9);

const int temperaturePin = A0;
int brightness = 0;

// initial Time display is 12:59:45 PM
int h=8;
int m=0;
int s=0;
int flag=1; //PM

// Time Set Buttons
int button1;
int button2;
int button3;

// Pins definition for Time Set Buttons
int hs=2;// pin 0 for Hours Setting
int ms=3;// pin 1 for Minutes Setting
int Say=4;
// Backlight Time Out 

// For accurate Time reading, use Arduino Real Time Clock and not just delay()
static uint32_t last_time, now = 0; // RTC


void setup()
{
  lcd.begin();
  lcd.backlight();
  text2speech.setPitch(1);
  pinMode(hs,INPUT_PULLUP);// avoid external Pullup resistors for Button 1
  pinMode(ms,INPUT_PULLUP);// and Button 2
  pinMode(Say,INPUT_PULLUP);
  pinMode(8, OUTPUT);

    lcd.createChar(0, Time);
  lcd.createChar(1, temp);
  lcd.createChar(2, light);
  lcd.createChar(3, battlow);
  lcd.createChar(4, warning);
  lcd.createChar(5, battfault);
  lcd.createChar(6, cross);
  lcd.createChar(7, retarrow);
  lcd.home();
  now=millis(); // read RTC initial value  
}


void loop()
{
// Update LCD Display
// Print TIME in Hour, Min, Sec + AM/PM
 lcd.clear();
 lcd.write(0);
 lcd.print(" ");
 if(h<10)lcd.print("0");// always 2 digits
 lcd.print(h);
 lcd.print(":");
 if(m<10)lcd.print("0");
 lcd.print(m);
 lcd.print(":");
 if(s<10)lcd.print("0");
 lcd.print(s);

 if(flag==0) lcd.print(" AM");
 if(flag==1) lcd.print(" PM");
 
 lcd.setCursor(0,1);// for Line 2

   brightness = analogRead(A1);

 float voltage, degreesC, degreesF;

  voltage = getVoltage(temperaturePin);

  degreesC = (voltage - 0.5) * 100.0;


  degreesF = degreesC * (9.0/5.0) + 32.0;

  lcd.write(1);
  lcd.print(" ");
  lcd.print(degreesF);
  lcd.print("F ");
  lcd.write(2);
  lcd.print(" ");
  lcd.print(brightness);
  

// improved replacement of delay(1000) 
// Much better accuracy, no more dependant of loop execution time

for ( int i=0 ;i<5 ;i++)// make 5 time 200ms loop, for faster Button response
{

  while ((now-last_time)<200) //delay200ms
  { 
    now=millis();
  }
 // inner 200ms loop
 last_time=now; // prepare for next loop 

 // read Setting Buttons
 button1=digitalRead(hs);// Read Buttons
 button2=digitalRead(ms);
 button3=digitalRead(Say);
 
 {
  if(button1==0){
   h=h+1;
  }

 if(button2==0){
  s=0;
  m=m+1;
  }
 if(button3==0){
  digitalWrite(8,HIGH);
  sayTime();
  delay(50);
    text2speech.sayText("The temperature is:");
  sayNumber(degreesF);
   text2speech.sayText("Degrees");
   delay(50);
    text2speech.sayText("The brightness is:");
  sayNumber(brightness);
    digitalWrite(8,LOW);
  }

/* ---- manage seconds, minutes, hours am/pm overflow ----*/
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
  sayTime();
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 }


 if((button1==0)|(button2==0))// Update display if time set button pressed
 {
  // Update LCD Display
  // Print TIME in Hour, Min, Sec + AM/PM
  lcd.clear();
  lcd.write(0);
  lcd.print(" ");
  if(h<10)lcd.print("0");// always 2 digits
  lcd.print(h);
  lcd.print(":");
  if(m<10)lcd.print("0");
  lcd.print(m);
  lcd.print(":");
  if(s<10)lcd.print("0");
  lcd.print(s);

  if(flag==0) lcd.print(" AM");
  if(flag==1) lcd.print(" PM");
 
  lcd.setCursor(0,1);// for Line 2
 }


 } // end if else
}// end for



// outer 1000ms loop

 s=s+1; //increment sec. counting
    
    
// ---- manage seconds, minutes, hours am/pm overflow ----
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 } 
 

 
// Loop end
}

void sayTime() 
{
  text2speech.sayText("The time is:");
  sayNumber(h);
  if(m==0){
    text2speech.sayText("O clock");
  }
  else if(m<10){
    sayNumber(0);
    sayNumber(m);
  }else {
  sayNumber(m);
  }
  if(flag==1){
  text2speech.sayText("P M");
  } else {
  text2speech.sayText("A M");
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

float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}

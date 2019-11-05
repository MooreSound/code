#include <english.h>
#include <sound.h>
#include <TTS.h>
#include <LiquidCrystal_I2C.h>

#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

TTS text2speech(9);

const int temperaturePin = A1;
int brightness = 0;
int buttonState = 0;
int val = 0; 

void setup() {
  pinMode(2, INPUT_PULLUP);
   pinMode(3, OUTPUT);
    text2speech.setPitch(1);

     Serial.begin(9600);
     lcd.begin();
  lcd.backlight();
}

void loop() {
  buttonState = digitalRead(2);
  brightness = analogRead(A0);

   val = brightness;            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 255); 
  analogWrite(3, val);

 float voltage, degreesC, degreesF;

  voltage = getVoltage(temperaturePin);

  degreesC = (voltage - 0.5) * 100.0;


  degreesF = degreesC * (9.0/5.0) + 32.0;

  Serial.print("deg C: ");
  Serial.print(degreesC);
  Serial.print("  deg F: ");
  Serial.print(degreesF);
  Serial.print(" Brightness: ");
  Serial.println(brightness);

  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(degreesF);
  lcd.print("F");
  lcd.setCursor(0,1);
  lcd.print("Light: ");
  lcd.print(brightness);
  
  if(buttonState == LOW){
    analogWrite(3, 255);
    text2speech.sayText("The temperature is:");
  sayNumber(degreesF);
   text2speech.sayText("Degrees");
   delay(100);
  text2speech.sayText("The brightness is:");
  sayNumber(brightness);
  }

  
delay(300);
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

const int buttonLEDpin = 13;

void setup() {
 pinMode(buttonLEDpin, INPUT_PULLUP);
 Serial.begin(115200);

}

void loop() {
  
 Serial.println(digitalRead(buttonLEDpin));
 if(digitalRead(buttonLEDpin) == LOW){
  pinMode(buttonLEDpin, OUTPUT);
  digitalWrite(buttonLEDpin, HIGH);
  delay(1000);
  pinMode(buttonLEDpin, INPUT_PULLUP);
 }
 delay(100);

 
}

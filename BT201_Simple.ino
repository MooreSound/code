const int playButton = 9;
const int nextButton = 10;
const int prevButton = 8;
const int volUpButton = 7;
const int volDnButton = 6;
const int LED = 13;


void setup() {
  pinMode(playButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);
  pinMode(prevButton, INPUT_PULLUP);
  pinMode(volUpButton, INPUT_PULLUP);
  pinMode(volDnButton, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
 Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {

   if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
    if(inByte == '2' || inByte == '4'){
      digitalWrite(LED, HIGH);
    }else if(inByte == '1'){
       digitalWrite(LED, LOW);
    }
   }
  
  if(digitalRead(playButton) == LOW){
    Serial1.println("AT+CB");
    delay(300);
  }else if(digitalRead(nextButton) == LOW){
    Serial1.println("AT+CC");
    delay(300);
  }else if(digitalRead(prevButton) == LOW){
    Serial1.println("AT+CD");
    delay(300);
  }else if(digitalRead(volUpButton) == LOW){
    Serial1.println("AT+CE");
    delay(300);
  }else if(digitalRead(volDnButton) == LOW){
    Serial1.println("AT+CF");
    delay(300);
  }
}

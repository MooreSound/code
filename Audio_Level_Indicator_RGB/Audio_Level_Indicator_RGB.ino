const int audioIn = A0;
const int redLED = 13;
const int greenLED = 12;
const int blueLED = 11;

void setup() {
  Serial.begin(115200);
  pinMode(audioIn, INPUT);
 pinMode(redLED, OUTPUT);
 pinMode(greenLED, OUTPUT);
 pinMode(blueLED, OUTPUT);
 digitalWrite(redLED, HIGH);
 digitalWrite(greenLED, HIGH);
 digitalWrite(blueLED, HIGH);
 delay(500);
 digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
}

void loop() {
int audioLevel = analogRead(audioIn);
Serial.print("Audio Level: ");
Serial.println(audioLevel);

if(audioLevel >= 600){
  digitalWrite(redLED, HIGH);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
 delay(100);
}else if(audioLevel >= 460){
  digitalWrite(redLED, HIGH);
 digitalWrite(greenLED, HIGH);
 digitalWrite(blueLED, LOW);
 delay(100);
}else if(audioLevel >= 100){
  digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, HIGH);
}else{
 digitalWrite(redLED, LOW);
 digitalWrite(greenLED, LOW);
 digitalWrite(blueLED, LOW);
}
delay(10);


}

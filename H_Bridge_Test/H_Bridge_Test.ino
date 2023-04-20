const int pinA = 10;
const int pinB = 9;

const int redLED = 13;
const int greenLED = 12;
const int blueLED = 11;

void setup() {
pinMode(redLED, OUTPUT);
pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);
digitalWrite(redLED, HIGH);
digitalWrite(greenLED, HIGH);
digitalWrite(blueLED, HIGH);
  
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  delay(500);
}

void loop() {
  digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, HIGH);
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, LOW);
  delay(2000);

  digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  delay(2000);

  digitalWrite(redLED, HIGH);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, HIGH);
  delay(2000);

  digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  delay(2000);

}

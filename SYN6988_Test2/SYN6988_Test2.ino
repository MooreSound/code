const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

void speak(char* msg) {
  Serial1.write(0xFD);
  Serial1.write((byte)0x0);
  Serial1.write(2 + strlen(msg));
  Serial1.write(0x01);
  Serial1.write((byte)0x0);
  Serial1.write(msg);
}

void waitForSpeech(unsigned long timeout = 500000) {
  unsigned long start = millis();
  bool done = false;
  while ( ! done && (millis() - start) < timeout ) {
    while ( Serial1.available() ) {
      if ( Serial1.read() == 0x4F ) {
        done = true;
        break;
      }
    }
  }
}

void busy() {
  state = !state;
  digitalWrite(ledPin, state);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), busy, CHANGE);
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  speak("[t3][s5][v10]Thank you for watching! Please like, share, subscribe, & support me by purchasing from my stores. Links in the description.");
waitForSpeech();
delay(2000);
}

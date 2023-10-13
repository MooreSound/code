const byte ledPin = 13;
const byte interruptPin = 2;
volatile byte state = LOW;

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

void speak(char* msg) {
  Serial1.write(0xFD);
  Serial1.write((byte)0x0);
  Serial1.write(2 + strlen(msg));
  Serial1.write(0x01);
  Serial1.write((byte)0x0);
  Serial1.write(msg);
  waitForSpeech();
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
speak("[x1][v10]sound101");
delay(500);
speak("[x1]sound102");
delay(500);
speak("[x1]sound103");
delay(500);
speak("[x1]sound104");
delay(500);
speak("[x1]sound105");
delay(500);
speak("[x1]sound106");
delay(500);
speak("[x1]sound107");
delay(500);
speak("[x1]sound108");
delay(500);
speak("[x1]sound109");
delay(500);
speak("[x1]sound110");
delay(500);
speak("[x1]sound111");
delay(500);
speak("[x1]sound112");
delay(500);
speak("[x1]sound113");
delay(500);
speak("[x1]sound114");
delay(500);
speak("[x1]sound115");
delay(500);
speak("[x1]sound116");
delay(500);
speak("[x1]sound117");
delay(500);
speak("[x1]sound118");
delay(500);
speak("[x1]sound119");
delay(500);
speak("[x1]sound120");
delay(500);
speak("[x1]sound121");
delay(500);
speak("[x1]sound122");
delay(500);
speak("[x1]sound123");
delay(500);
speak("[x1]sound124");
delay(2000);

speak("[x1]sound201");
delay(500);
speak("[x1]sound202");
delay(500);
speak("[x1]sound203");
delay(500);
speak("[x1]sound204");
delay(500);
speak("[x1]sound205");
delay(500);
speak("[x1]sound206");
delay(500);
speak("[x1]sound207");
delay(500);
speak("[x1]sound208");
delay(500);
speak("[x1]sound209");
delay(2000);

speak("[x1]sound301");
delay(500);
speak("[x1]sound302");
delay(500);
speak("[x1]sound303");
delay(500);
speak("[x1]sound304");
delay(500);
speak("[x1]sound305");
delay(500);
speak("[x1]sound306");
delay(500);
speak("[x1]sound307");
delay(500);
speak("[x1]sound308");
delay(500);
speak("[x1]sound309");
delay(500);
speak("[x1]sound310");
delay(500);
speak("[x1]sound311");
delay(500);
speak("[x1]sound312");
delay(500);
speak("[x1]sound313");
delay(500);
speak("[x1]sound314");
delay(500);
speak("[x1]sound315");
delay(500);
speak("[x1]sound316");
delay(500);
speak("[x1]sound317");
delay(500);
speak("[x1]sound318");
delay(2000);

speak("[x1]sound401");
delay(500);
speak("[x1]sound402");
delay(500);
speak("[x1]sound403");
delay(500);
speak("[x1]sound404");
delay(500);
speak("[x1]sound405");
delay(500);
speak("[x1]sound406");
delay(500);
speak("[x1]sound407");
delay(500);
speak("[x1]sound408");
delay(5000);
}

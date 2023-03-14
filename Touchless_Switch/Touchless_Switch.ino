

const int irLED = 12;
const int irSense = A0;
const int LED = 13;

int irValue = 1023;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(irLED, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(irSense, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  digitalWrite(irLED, HIGH);
  delay(10);
irValue = analogRead(irSense);
   if(irValue <= 100){
       delay(100);
       digitalWrite(LED, HIGH);
    Serial.print("Sensor triggered! ");
    Serial.println(irValue);
     delay(1000);
     digitalWrite(irLED, LOW);   
  }else if(irValue <= 600){
    Serial.println(irValue); 
    digitalWrite(LED, LOW);
    digitalWrite(irLED, LOW);
  delay(200);   
  }else{
  Serial.println(irValue);
  digitalWrite(LED, LOW);
  digitalWrite(irLED, LOW);
  delay(500);  
  }

}

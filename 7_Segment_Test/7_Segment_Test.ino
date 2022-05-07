const int segmentA = 13;
const int segmentB = 12;
const int segmentC = 11;
const int segmentD = 10;
const int segmentE = 9;
const int segmentF = 8;
const int segmentG = 7;
const int segmentDP = 6;

void setup() {
 pinMode(segmentA, OUTPUT);
 pinMode(segmentB, OUTPUT);
 pinMode(segmentC, OUTPUT);
pinMode(segmentD, OUTPUT);
pinMode(segmentE, OUTPUT);
pinMode(segmentF, OUTPUT);
pinMode(segmentG, OUTPUT);
pinMode(segmentDP, OUTPUT);

digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, HIGH);
delay(500);

digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);

}

void loop() {
 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

digitalWrite(segmentA, LOW);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, HIGH);
delay(1000);

}

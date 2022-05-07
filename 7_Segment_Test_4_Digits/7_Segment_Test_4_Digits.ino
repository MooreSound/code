const int segmentA = 13;
const int segmentB = 12;
const int segmentC = 11;
const int segmentD = 10;
const int segmentE = 9;
const int segmentF = 8;
const int segmentG = 7;
const int segmentDP = 6;
const int digit1 = 5;
const int digit2 = 4;
const int digit3 = 3;
const int digit4 = 2;

const int button = A0;

  int mode = 0;

void setup() {
pinMode(button, INPUT_PULLUP);

 pinMode(segmentA, OUTPUT);
 pinMode(segmentB, OUTPUT);
 pinMode(segmentC, OUTPUT);
pinMode(segmentD, OUTPUT);
pinMode(segmentE, OUTPUT);
pinMode(segmentF, OUTPUT);
pinMode(segmentG, OUTPUT);
pinMode(segmentDP, OUTPUT);
pinMode(digit1, OUTPUT);
pinMode(digit2, OUTPUT);
pinMode(digit3, OUTPUT);
pinMode(digit4, OUTPUT);


digitalWrite(segmentA, HIGH);
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, HIGH);
digitalWrite(digit1, HIGH);
digitalWrite(digit2, HIGH);
digitalWrite(digit3, HIGH);
digitalWrite(digit4, HIGH);
delay(500);

digitalWrite(segmentA, LOW);
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

}

void loop() {
if(digitalRead(button) == LOW){
  mode++;
  if(mode == 5){
    mode = 0;
  }
  delay(100);
}

if (mode == 0){ 
digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, HIGH);
  
 /*digitalWrite(segmentA, HIGH);//0
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(10);*/

 digitalWrite(segmentA, LOW);//1
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(5);

digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, HIGH);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//2
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);
digitalWrite(digit1, LOW);
digitalWrite(digit2, HIGH);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//3
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);

digitalWrite(digit1, HIGH);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, LOW);//4
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);}

if (mode == 1){

digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, HIGH);
  
digitalWrite(segmentA, HIGH);//0
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(5);
digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, HIGH);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, LOW);//1
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(5);
digitalWrite(digit1, LOW);
digitalWrite(digit2, HIGH);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//2
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);


digitalWrite(digit1, HIGH);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//3
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);

  
}

if (mode == 4){

digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, HIGH);
  
digitalWrite(segmentA, HIGH);//0
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, HIGH);
delay(200);
digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, HIGH);
digitalWrite(digit4, LOW);

digitalWrite(segmentA, HIGH);//0
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, HIGH);
delay(200);
digitalWrite(digit1, LOW);
digitalWrite(digit2, HIGH);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//0
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, HIGH);
delay(200);


digitalWrite(digit1, HIGH);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//0
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, HIGH);
delay(200);
  
}

if (mode == 2){

digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, HIGH);
  
 digitalWrite(segmentA, HIGH);//G
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);

delay(5);

digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, HIGH);
digitalWrite(digit4, LOW);

  digitalWrite(segmentA, HIGH);//A
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);

digitalWrite(digit1, LOW);
digitalWrite(digit2, HIGH);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, LOW);//r
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);


digitalWrite(digit1, HIGH);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//E
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);

  
}

if (mode == 3){

digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, HIGH);
  
 digitalWrite(segmentA, HIGH);//2
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);

delay(5);

digitalWrite(digit1, LOW);
digitalWrite(digit2, LOW);
digitalWrite(digit3, HIGH);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//0
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(5);

digitalWrite(digit1, LOW);
digitalWrite(digit2, HIGH);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

  digitalWrite(segmentA, HIGH);//2
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);


digitalWrite(digit1, HIGH);
digitalWrite(digit2, LOW);
digitalWrite(digit3, LOW);
digitalWrite(digit4, LOW);

 digitalWrite(segmentA, HIGH);//2
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(5);

  
}

/*

 digitalWrite(segmentA, HIGH);//5
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//6
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//7
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//8
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//9
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//A
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//b
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//C
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//d
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//E
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//F
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//G
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//H
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

digitalWrite(segmentA, LOW);//i
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

digitalWrite(segmentA, LOW);//J
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//K
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//L
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//N
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//o
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//P
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//q
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//r
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//S
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//t
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//U
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, HIGH);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//y
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, HIGH);
digitalWrite(segmentD, HIGH);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//dash
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, HIGH);//degree sign
digitalWrite(segmentB, HIGH);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, HIGH);
digitalWrite(segmentG, HIGH);
digitalWrite(segmentDP, LOW);
delay(1000);

 digitalWrite(segmentA, LOW);//decimal point
digitalWrite(segmentB, LOW);
digitalWrite(segmentC, LOW);
digitalWrite(segmentD, LOW);
digitalWrite(segmentE, LOW);
digitalWrite(segmentF, LOW);
digitalWrite(segmentG, LOW);
digitalWrite(segmentDP, HIGH);
delay(1000);

*/

}

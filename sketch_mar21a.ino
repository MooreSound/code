const int sensorPin1 = A0;
const int sensorPin2 = A1;
const int display1CA = 13;
const int display2CA = 12;
const int segment1 = 11;
const int segment2 = 10;
const int segment3 = 9;
const int segment4 = 8;
const int segment5 = 7;
const int segment6 = 6;
const int segment7 = 5;
const int segment8 = 4;
const int segment9 = 3;
const int segment10 = 2;

void setup() {
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(display1CA, OUTPUT);
  pinMode(display2CA, OUTPUT);
  pinMode(segment1, OUTPUT);
  pinMode(segment2, OUTPUT);
  pinMode(segment3, OUTPUT);
  pinMode(segment4, OUTPUT);
  pinMode(segment5, OUTPUT);
  pinMode(segment6, OUTPUT);
  pinMode(segment7, OUTPUT);
  pinMode(segment8, OUTPUT);
  pinMode(segment9, OUTPUT);
  pinMode(segment10, OUTPUT);
  digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, LOW);
  digitalWrite(segment9, LOW);
  digitalWrite(segment10, LOW);
  delay(1000);
  
  digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, HIGH);
  digitalWrite(segment2, HIGH);
  digitalWrite(segment3, HIGH);
  digitalWrite(segment4, HIGH);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);
}

void loop() {
 int sensorValue1 = analogRead(sensorPin1);
 int sensorValue2 = analogRead(sensorPin2);

 int ledLevel1 = map(sensorValue1, 0, 1010, 0, 10);
 int ledLevel2 = map(sensorValue2, 0, 1010, 0, 10);

 if(ledLevel2 <= 1){
   digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, HIGH);
  digitalWrite(segment3, HIGH);
  digitalWrite(segment4, HIGH);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);
 }else if(ledLevel2 == 2){
   digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, HIGH);
  digitalWrite(segment4, HIGH);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel2 == 3){
   digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, HIGH);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel2 == 4){
   digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel2 == 5){
  digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel2 == 6){
  digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);;
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel2 == 7){
   digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel2 == 8){
  digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, LOW);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel2 == 9){
  digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, LOW);
  digitalWrite(segment9, LOW);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel2 >= 10){
  digitalWrite(display1CA, HIGH);
  digitalWrite(display2CA, LOW);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, LOW);
  digitalWrite(segment9, LOW);
  digitalWrite(segment10, LOW);  
 }
 delay(10);

  if(ledLevel1 <= 1){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, HIGH);
  digitalWrite(segment3, HIGH);
  digitalWrite(segment4, HIGH);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);
 }else if(ledLevel1 == 2){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, HIGH);
  digitalWrite(segment4, HIGH);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel1 == 3){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, HIGH);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel1 == 4){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, HIGH);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel1 == 5){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, HIGH);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel1 == 6){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, HIGH);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel1 == 7){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, HIGH);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel1 == 8){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, LOW);
  digitalWrite(segment9, HIGH);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel1 == 9){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, LOW);
  digitalWrite(segment9, LOW);
  digitalWrite(segment10, HIGH);  
 }else if(ledLevel1 >= 10){
   digitalWrite(display1CA, LOW);
  digitalWrite(display2CA, HIGH);
  digitalWrite(segment1, LOW);
  digitalWrite(segment2, LOW);
  digitalWrite(segment3, LOW);
  digitalWrite(segment4, LOW);
  digitalWrite(segment5, LOW);
  digitalWrite(segment6, LOW);
  digitalWrite(segment7, LOW);
  digitalWrite(segment8, LOW);
  digitalWrite(segment9, LOW);
  digitalWrite(segment10, LOW);  
 }
 delay(10);

}

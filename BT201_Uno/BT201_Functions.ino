void playPause(){

   BT201Serial.println("AT+CB");
    delay(100);

}

void nextTrack(){
   BT201Serial.println("AT+CC");
    delay(100);
}

void prevTrack(){
   BT201Serial.println("AT+CD");
    delay(100);
}
void volUp(){
BT201Serial.println("AT+CE");
    delay(100);
}
void volDown(){
 
BT201Serial.println("AT+CF");
    delay(100);
    
}

void setMode(int mode){
  switch(mode){
    case 0:
  BT201Serial.println("AT+CM00");
  break;
    case 1:
 BT201Serial.println("AT+CM01");
  break;
    case 2:
 BT201Serial.println("AT+CM02");
  break;
    case 3:
 BT201Serial.println("AT+CM03");
  break;
    case 4:
 BT201Serial.println("AT+CM04");
  break;
    case 5:
BT201Serial.println("AT+CM05");
  break;
    case 7:
BT201Serial.println("AT+CM07");
  break;
    case 8:
 BT201Serial.println("AT+CM08");
  break;
  default:
  break;
}
delay(100);
}

void resetBT201(){
  BT201Serial.println("AT+CZ");
   delay(100);
}

int getBTStatus(){
String readStatus;
 BT201Serial.println("AT+TS");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cs = BT201Serial.read();
    if (cs == '+') {
      if (readStatus.length() >0) {
        Serial.println(readStatus); //prints string to serial port out

        int ns = readStatus.toInt();  //convert readString into a number
        if(ns == 2 || ns == 4){
      return 3;
    }else if(ns == 1){
     return 2;
     }else if(ns == 3){
     return 4;
    }else if(ns == 0){
      return 1;
    }

        readStatus=""; //clears variable for new input
      }
    }  
    else {     
      readStatus += cs; //makes the string readString
    }
   
}
}

int getMP3Status(){
String readStatus;
  BT201Serial.println("AT+MP");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cs = BT201Serial.read();
    if (cs == '+') {
      if (readStatus.length() >0) {
        Serial.println(readStatus); //prints string to serial port out

        int ns = readStatus.toInt();  //convert readString into a number
        if(ns == 2){
      return 3;
    }else if(ns == 1){
     return 2;
    }else if(ns == 0){
      return 1;
    }

        readStatus=""; //clears variable for new input
      }
    }  
    else {     
      readStatus += cs; //makes the string readString
    }
   
}
}

String getMP3FileName(){
String readStatus;
 BT201Serial.println("AT+MF");
  delay(50);
   while (BT201Serial.available() > 0) {
    readStatus = BT201Serial.readStringUntil('.');
    
      if (readStatus.length() >0) {
        Serial.println(readStatus); //prints string to serial port out

        return readStatus;

        readStatus=""; //clears variable for new input
      }
  
}
}

int getMode(){
String readMode;
  BT201Serial.println("AT+QM");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cm = BT201Serial.read();
    if (cm == '+') {
      if (readMode.length() >0) {
        Serial.println(readMode); //prints string to serial port out

        int nm = readMode.toInt();  //convert readString into a number
        if(nm == 0){
      return 1;
    }else if(nm == 1){
     return 2;
     }else if(nm == 2){
     return 3;
    }else if(nm == 3){
      return 4;
    }else if(nm == 4){
      return 5;
    }else if(nm == 5){
      return 6;
    }else if(nm == 6){
      return 7;
    }else if(nm == 7){
      return 8;
    }else if(nm == 8){
      return 9;
    }else if(nm == 9){
      return 10;
    }

        readMode=""; //clears variable for new input
      }
    }  
    else {     
      readMode += cm; //makes the string readString
    }
   
}
}

int getVolume(){
String readVol;
  BT201Serial.println("AT+QA");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cv = BT201Serial.read();
    if (cv == '+') {
      if (readVol.length() >0) {
        Serial.println(readVol); //prints string to serial port out

        int nv = readVol.toInt();  //convert readString into a number
    return nv;

        readVol=""; //clears variable for new input
      }
    }  
    else {     
      readVol += cv; //makes the string readString
    }
   
}
delay(50);
}

long getPhoneNumber(){
String readNumber;
 BT201Serial.println("AT+TT");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cn = BT201Serial.read();
    if (cn == '+') {
      if (readNumber.length() >0) {
        Serial.println(readNumber); //prints string to serial port out

        long phn = readNumber.toFloat();  //convert readString into a number
    return phn;

        readNumber=""; //clears variable for new input
      }
    }  
    else {     
      readNumber += cn; //makes the string readString
    }
   
}
delay(50);
}

int getCurrentFile(){
String readNumber;
  BT201Serial.println("AT+M1");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cn = BT201Serial.read();
    if (cn == '+') {
      if (readNumber.length() >0) {
        Serial.println(readNumber); //prints string to serial port out

        int phn = readNumber.toInt();  //convert readString into a number
    return phn;

        readNumber=""; //clears variable for new input
      }
    }  
    else {     
      readNumber += cn; //makes the string readString
    }
   
}
delay(50);
}

int getTotalFiles(){
String readNumber;
 BT201Serial.println("AT+M2");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cn = BT201Serial.read();
    if (cn == '+') {
      if (readNumber.length() >0) {
        Serial.println(readNumber); //prints string to serial port out

        int phn = readNumber.toInt();  //convert readString into a number
    return phn;

        readNumber=""; //clears variable for new input
      }
    }  
    else {     
      readNumber += cn; //makes the string readString
    }
   
}
delay(50);
}
long getCurrentPlayTime(){
String readNumber;
  BT201Serial.println("AT+MK");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cn = BT201Serial.read();
    if (cn == '+') {
      if (readNumber.length() >0) {
        Serial.println(readNumber); //prints string to serial port out

        int phn = readNumber.toFloat();  //convert readString into a number
    return phn;

        readNumber=""; //clears variable for new input
      }
    }  
    else {     
      readNumber += cn; //makes the string readString
    }
   
}
delay(50);
}

long getTotalPlayTime(){
String readNumber;
  BT201Serial.println("AT+MT");
  delay(50);
   while (BT201Serial.available() > 0) {
    char cn = BT201Serial.read();
    if (cn == '+') {
      if (readNumber.length() >0) {
        Serial.println(readNumber); //prints string to serial port out

        int phn = readNumber.toFloat();  //convert readString into a number
    return phn;

        readNumber=""; //clears variable for new input
      }
    }  
    else {     
      readNumber += cn; //makes the string readString
    }
   
}
delay(50);
}

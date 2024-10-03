/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/* This sketch demonstrate the BLEAncs service. After uploading, go to
 * iOS setting and connect to Bluefruit, and then press PAIR. Bluefruit
 * will print out any notification meesages to Serial Monitor
 */

#include <bluefruit.h>

const int redLED = A0;
const int greenLED = A1;
const int blueLED = A2;
const int button = A3;


// BLE Client Service
BLEClientDis  bleClientDis;
BLEAncs       bleancs;

#define BUFSIZE   1000
char buffer[BUFSIZE];

// Check BLEAncs.h for AncsNotification_t
const char* EVENT_STR[] = { "Added", "Modified", "Removed" };
const char* CAT_STR  [] =
{
  "Other"             , "Incoming Call"       , "Missed Call", "Voice Mail"   ,
  "Social"            , "Schedule"            , "Email"      , "News"         ,
  "Health and Fitness", "Business and Finance", "Location"   , "Entertainment"
};

void setup()
{
   pinMode(button, INPUT_PULLUP);
  pinMode(redLED, OUTPUT);
pinMode(greenLED, OUTPUT);
pinMode(blueLED, OUTPUT);
digitalWrite(redLED, HIGH);
digitalWrite(greenLED, HIGH);
digitalWrite(blueLED, HIGH);
  Serial.begin(115200);
  Serial1.begin(115200);
//  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("Bluefruit52 BLE ANCS Example");
  Serial.println("----------------------------\n");

  Serial.println("Go to iOS's Bluetooth settings and connect to Bluefruit52");
  Serial.println("It may appear up as 'Accessory' depending on your OS version.");

  // Config the peripheral connection with maximum bandwidth
  // more SRAM required by SoftDevice
  // Note: All config***() function must be called before begin()
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  // Set connection secured callback, invoked when connection is encrypted
  Bluefruit.Security.setSecuredCallback(connection_secured_callback);

  // Configure DIS client
  bleClientDis.begin();

  // Configure ANCS client
  bleancs.begin();
  bleancs.setNotificationCallback(ancs_notification_callback);

  speak("[t3][v10] Power On");
  digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);

  // Set up and start advertising
  startAdv();
   speak("[t3][v10] Ready for connection");
     digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, HIGH);
}

void startAdv(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  // Include ANCS 128-bit uuid
  Bluefruit.Advertising.addService(bleancs);

  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
 
}

void loop()
{
  // Not connected, wait for a connection
  if ( !Bluefruit.connected() ) return;

  // If service is not yet discovered
  if ( !bleancs.discovered() ) return;

if(digitalRead(button)==LOW){
 digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);
}

}

void connect_callback(uint16_t conn_handle)
{
  BLEConnection* conn = Bluefruit.Connection(conn_handle);

  Serial.println("Connected");
  
  Serial.print("Discovering DIS ... ");
  if ( bleClientDis.discover(conn_handle) )
  {
    Serial.println("Discovered");
    
    // Read and print Manufacturer string
    memset(buffer, 0, BUFSIZE);
    if ( bleClientDis.getManufacturer(buffer, BUFSIZE) )
    {
      Serial.print("Manufacturer: ");
      Serial.println(buffer);
    }

    // Read and print Model Number string
    memset(buffer, 0, BUFSIZE);
    if ( bleClientDis.getModel(buffer, BUFSIZE) )
    {
      Serial.print("Model: ");
      Serial.println(buffer);
    }

    Serial.println();
  }

  Serial.print("Discovering ANCS ... ");
  if ( bleancs.discover(conn_handle) )
  {
    Serial.println("Discovered");

    // ANCS requires pairing to work, it makes sense to request security here as well
    Serial.print("Attempting to PAIR with the iOS device, please press PAIR on your phone ... ");
    conn->requestPairing();
    speak("[x1] sound403 ");
     speak("[x0][t3][v10] Please accept pairing request.");
  }
}

void connection_secured_callback(uint16_t conn_handle)
{
  BLEConnection* conn = Bluefruit.Connection(conn_handle);

  if ( !conn->secured() )
  {
    // It is possible that connection is still not secured by this time.
    // This happens (central only) when we try to encrypt connection using stored bond keys
    // but peer reject it (probably it remove its stored key).
    // Therefore we will request an pairing again --> callback again when encrypted
    conn->requestPairing();
  }
  else
  {
    Serial.println("Secured");

    if ( bleancs.discovered() )
    {
      Serial.println("Enabling notifications");
      Serial.println();
      bleancs.enableNotification();
        digitalWrite(redLED, LOW);
digitalWrite(greenLED, HIGH);
digitalWrite(blueLED, LOW);
      speak("[x1] sound403 ");
  speak("[x0][t3][v10] Ready to use. ");
    digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);
    }
  }
}

void ancs_notification_callback(AncsNotification_t* notif)
{
  
  uint32_t const uid = notif->uid;
if (notif->eventID == ANCS_EVT_NOTIFICATION_ADDED){
  if ( notif->categoryID == ANCS_CAT_INCOMING_CALL){
     memset(buffer, 0, BUFSIZE);
  if ( bleancs.getTitle(uid, buffer, BUFSIZE) )
  {
    char u202D[3] = { 0xE2, 0x80, 0xAD }; // U+202D in UTF-8
    char u202C[3] = { 0xE2, 0x80, 0xAC }; // U+202C in UTF-8

    int len = strlen(buffer);

    if ( 0 == memcmp(&buffer[len-3], u202C, 3) )
    {
      len -= 3;
      buffer[len] = 0; // chop ending U+202C
    }

    if ( 0 == memcmp(buffer, u202D, 3) )
    {
      memmove(buffer, buffer+3, len-2); // move null-terminator as well
    }
  }
  
  Serial.printf("%-15s %s\n", buffer, EVENT_STR[notif->eventID]);
    digitalWrite(redLED, HIGH);
digitalWrite(greenLED, HIGH);
digitalWrite(blueLED, HIGH);
   speak("[x1] sound204 ");
  speak("[x0][t3][v10]");
  speak(buffer);
  speak(" is calling");
  }else if( notif->categoryID == ANCS_CAT_SOCIAL){
  // Get notification Title
  // iDevice often include Unicode "Bidirection Text Control" in the Title.
  // Mostly are U+202D as beginning and U+202C as ending. Let's remove them
  memset(buffer, 0, BUFSIZE);
  if ( bleancs.getTitle(uid, buffer, BUFSIZE) )
  {
    char u202D[3] = { 0xE2, 0x80, 0xAD }; // U+202D in UTF-8
    char u202C[3] = { 0xE2, 0x80, 0xAC }; // U+202C in UTF-8

    int len = strlen(buffer);

    if ( 0 == memcmp(&buffer[len-3], u202C, 3) )
    {
      len -= 3;
      buffer[len] = 0; // chop ending U+202C
    }

    if ( 0 == memcmp(buffer, u202D, 3) )
    {
      memmove(buffer, buffer+3, len-2); // move null-terminator as well
    }
  }
  
  Serial.printf("%-15s %s\n", buffer, EVENT_STR[notif->eventID]);
    digitalWrite(redLED, LOW);
digitalWrite(greenLED, HIGH);
digitalWrite(blueLED, LOW);
  speak("[x1] sound123 ");
  speak("[x0][t3][v10] New message from: ");
  speak(buffer);

  // Get notification Message
  memset(buffer, 0, BUFSIZE);
  bleancs.getMessage(uid, buffer, BUFSIZE);
  Serial.printf("  %s\n", buffer);
  speak("It says:");
  speak(buffer);
  

  Serial.println();
}
 else if( notif->categoryID == ANCS_CAT_EMAIL){
  // Get notification Title
  // iDevice often include Unicode "Bidirection Text Control" in the Title.
  // Mostly are U+202D as beginning and U+202C as ending. Let's remove them
  memset(buffer, 0, BUFSIZE);
  if ( bleancs.getTitle(uid, buffer, BUFSIZE) )
  {
    char u202D[3] = { 0xE2, 0x80, 0xAD }; // U+202D in UTF-8
    char u202C[3] = { 0xE2, 0x80, 0xAC }; // U+202C in UTF-8

    int len = strlen(buffer);

    if ( 0 == memcmp(&buffer[len-3], u202C, 3) )
    {
      len -= 3;
      buffer[len] = 0; // chop ending U+202C
    }

    if ( 0 == memcmp(buffer, u202D, 3) )
    {
      memmove(buffer, buffer+3, len-2); // move null-terminator as well
    }
  }
  
  Serial.printf("%-15s %s\n", buffer, EVENT_STR[notif->eventID]);
    digitalWrite(redLED, LOW);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, HIGH);
  speak("[x1] sound110 ");
  speak("[x0][t3][v10] New e-mail from: ");
  speak(buffer);

  // Get notification Message
  memset(buffer, 0, BUFSIZE);
  bleancs.getMessage(uid, buffer, BUFSIZE);
  Serial.printf("  %s\n", buffer);
  speak("It says:");
  speak(buffer);
  

  Serial.println();
} else{
  // Application ID & Name
  char appID[128] = { 0 };
  bleancs.getAppID(uid, appID, sizeof(appID));

  memset(buffer, 0, BUFSIZE);
  bleancs.getAppAttribute(appID, ANCS_APP_ATTR_DISPLAY_NAME, buffer, BUFSIZE);

  Serial.printf("%-15s (%s)\n", buffer, appID);
    digitalWrite(redLED, HIGH);
digitalWrite(greenLED, HIGH);
digitalWrite(blueLED, LOW);
  speak("[x1] sound120 ");
  speak("[x0][t3][v10] New notification from: ");
  speak(buffer);

  // Get notification Title
  // iDevice often include Unicode "Bidirection Text Control" in the Title.
  // Mostly are U+202D as beginning and U+202C as ending. Let's remove them
  memset(buffer, 0, BUFSIZE);
  if ( bleancs.getTitle(uid, buffer, BUFSIZE) )
  {
    char u202D[3] = { 0xE2, 0x80, 0xAD }; // U+202D in UTF-8
    char u202C[3] = { 0xE2, 0x80, 0xAC }; // U+202C in UTF-8

    int len = strlen(buffer);

    if ( 0 == memcmp(&buffer[len-3], u202C, 3) )
    {
      len -= 3;
      buffer[len] = 0; // chop ending U+202C
    }

    if ( 0 == memcmp(buffer, u202D, 3) )
    {
      memmove(buffer, buffer+3, len-2); // move null-terminator as well
    }
  }
  
  Serial.printf("%-15s %s\n", buffer, EVENT_STR[notif->eventID]);
  speak(buffer);

  // Get notification Message
  memset(buffer, 0, BUFSIZE);
  bleancs.getMessage(uid, buffer, BUFSIZE);
  Serial.printf("  %s\n", buffer);
  speak("It says:");
  speak(buffer);
  

  Serial.println();
}
  // Automatically accept incoming calls using 'performAction'
  /*if ( notif->categoryID == ANCS_CAT_INCOMING_CALL && notif->eventID == ANCS_EVT_NOTIFICATION_ADDED)
  {
    Serial.println("Incoming call accepted");
    bleancs.performAction(notif->uid, ANCS_ACTION_POSITIVE);
  }*/
}

}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) reason;

  Serial.println();
  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
    digitalWrite(redLED, HIGH);
digitalWrite(greenLED, LOW);
digitalWrite(blueLED, LOW);
  speak("[x1] sound401 ");
  speak("[x0][t3][v10] Disconnected ");
}

void waitForSpeech(unsigned long timeout = 80000) {
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
  Serial.println(msg);
  short meslength= strlen(msg)+2;
    Serial1.write(0xFD);
    Serial1.write((meslength >> 8) & 0xFF);
    Serial1.write(meslength & 0xFF);
    Serial1.write(0x01);
    Serial1.write((byte)0x0);
    Serial1.write(msg);
    waitForSpeech();
     
}

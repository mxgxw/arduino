#define BUFFSIZE 1024
#include <SoftwareSerial.h>
#include <string.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  
  pinMode(3,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  attachInterrupt(0, pin3OnFalling, FALLING);
  attachInterrupt(4, pin7OnFalling, FALLING);
}
volatile long lastInt = 0;
volatile boolean sendMessage = false;
void pin7OnFalling() {
  if((millis()-lastInt)>500) {
    sendMessage = true;
    lastInt = millis();
  }
}

volatile boolean startShutDown = false;
void pin3OnFalling() {
  if((millis()-lastInt)>500) {
    startShutDown = true;
    lastInt = millis();
  }
}

char buffer[BUFFSIZE];
int buffSize = 0;

void clearBuffer() {
  for(int i=0;i<BUFFSIZE;i++) {
    buffer[i] = 0;
  }
  buffSize = 0;
}

volatile byte chr;

void appendToBuffer(char c) {
  if(buffSize<BUFFSIZE) {
    buffer[buffSize++] = c;
  } else {
    Serial.print(buffer);
    clearBuffer();
    buffer[buffSize++] = c;
  }
}

boolean gsmIsReady = false;

void pushSlow(char* command) {
  for(int i=0; i<strlen(command); i++) {
    mySerial.write(command[i]);
    if(command[i]=='\n') {
      delay(1000);
    } else {
      delay(100);
    }
  }
}

void sendSMS() {
  pushSlow("AT+CMGF=1\r\n");
  pushSlow("AT+CMGS=\"+50312345678\"\r\n");
  pushSlow("HELLO WORLD\x1A");
}

void shutDown() {
  pushSlow("AT+CPOWD=1\r\n");
}

void loop() // run over and over
{
  if(sendMessage) {
    Serial.print("SMS Interrupt received\r\n");
    sendSMS();
    sendMessage = false;
  }
  if(startShutDown) {
    Serial.print("Shutdown interrupt received\r\n");
    shutDown();
    startShutDown = false;
  }
  if (mySerial.available()) {
    chr = mySerial.read();
    Serial.write(chr);
    if(!((char)chr=='\r' || (char)chr=='\n')) {
      appendToBuffer((char)chr);
    } else { // PROCESS BUFFER
      if(strstr(buffer,"Call Ready")!=NULL) {
        gsmIsReady = true;
        Serial.print("ARDUINO> GSM is Ready - Waiting for interrupt\r\n");
      }
    clearBuffer();
    }
  }
  if (Serial.available())
    mySerial.write(Serial.read());
}

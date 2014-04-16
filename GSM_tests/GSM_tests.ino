#include <SerialGSM.h>
#include <SoftwareSerial.h>

SerialGSM cell(2,3); // RX, TX

int time=0;

void setup() {
  Serial.begin(9600);
  cell.begin(4800);
  
  cell.Verbose(true);
  cell.Boot();
  cell.checkSignalQuality();
  cell.FwdSMS2Serial();
  cell.Rcpt("+12035391858");
  cell.Message("Program begins now!");
  cell.SendSMS();
  
  delay(30000); // Wait 30s for things to clear
}

void loop() { 
  char __msg[50];
  
  sprintf(__msg, "The program has been running for %i minutes.", time);  
  
  cell.Message(__msg);
  cell.SendSMS();
  //Serial.println(__msg);
  
  time++;
  delay(60000); // Wait 60 s  
}

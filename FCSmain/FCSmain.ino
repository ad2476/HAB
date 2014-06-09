#include <SerialGSM.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

// HAB/Definitions/ is symlinked to sketchbook/libraries/Definitions/
#include <definitions.h>

TinyGps gps;
SoftwareSerial GPS(GPSRX, GPSTX);
SerialGSM cell(GSMRX, GSMTX);

unsigned long int time=0; // Running time in seconds

void setup()
{
  /* Begin hw/sw serial communications */
  Serial.begin(SERIALBAUD);
  GPS.begin(GPSBAUD);
  cell.begin(GSMBAUD);
  
  Serial.println(F("HAB FCS v.1.0"));
  
  /* Initialise the cell module */
  cell.listen();
  cell.Verbose(true);
  cell.Boot();
  cell.checkSignalQuality();
  cell.FwdSMS2Serial();
  cell.Rcpt(RCPT);
  cell.Message("Starting FCS...");
  cell.SendSMS();
  
  delay(30000); // Wait 30s for things to clear
}

void loop()
{
  char GPSbuf[80];
        
  // For 15 seconds we parse GPS data and report some key values
  GPS.listen(); // Listen on the GPS serial
  for (unsigned long start = millis(); millis() - start < 15000;)
  {
    while (GPS.available())
    {
      char c = GPS.read();
      //Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) { // Process new GPS data here
        packGPSdata(GPSbuf);
      }
    }
  }
  Serial.println(GPSbuf);
  
  
  time+=15;
  // Send a text every 60 seconds
  if (time%60==0) {
    cell.listen();
    cell.Message(GPSbuf);
    cell.SendSMS();
  }
   
}


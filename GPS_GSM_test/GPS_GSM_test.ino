#include <SerialGSM.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

// HAB/Definitions is symlinked to sketchbook/libraries/Definitions
#include <definitions.h>

// Status LED
#define LEDpin 13

TinyGPS gps;
SoftwareSerial GPS(GPSRX, GPSTX);
SerialGSM cell(GSMRX,GSMTX); // RX, TX

int time=0; // Time in seconds
int state=LOW; // Remember the state of the LED pin

// Packs all relevant GPS data into a logging string for OpenLog and SMS
void packGPSdata(char* strbuf) {
  long lat, lon; // float fcourse;;
  int year;
  unsigned long alt, kspeed;
  unsigned long fix_age;
  byte hour, minute, second, IDC;
  
  gps.get_position(&lat, &lon, &fix_age); // Lat/long in millionths of degrees
  alt = gps.altitude(); // Altitude in cm
  kspeed = gps.speed(); // Speed in 100ths of knots
  //fcourse = gps.f_course(); // Course in degrees
  gps.crack_datetime(&year, &IDC, &IDC, &hour, &minute, &second, &IDC, &fix_age);
    
  // Pack it all into one output
  sprintf(strbuf, "%2d:%2d:%2d | %ld %ld | %ld | %ld", hour, minute, second, lat, lon, alt, kspeed);
}

void toggleLED() {
  digitalWrite(LEDpin, state);
  state=!state;
}

void setup()
{
  Serial.begin(SERIALBAUD);
  GPS.begin(GPSBAUD);
  cell.begin(GSMBAUD);
  
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, HIGH);
  
  Serial.println(F("GPS - GSM communication test"));
  
  cell.listen();
  cell.Verbose(true);
  cell.Boot();
  cell.checkSignalQuality();
  cell.FwdSMS2Serial();
  cell.Rcpt(RCPT);
  cell.Message("Program begins in 30s!");
  cell.SendSMS();
  
  delay(30000); // Wait 30s for things to clear
}

void loop()
{
  char GPSbuf[80];
  
  toggleLED();
        
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

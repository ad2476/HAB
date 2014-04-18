#include <SerialGSM.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   9600-baud serial GPS device hooked up on pins 4(rx) and 5(tx).
*/

#define GPSBAUD 9600
#define SERIALBAUD 9600
#define GSMBAUD 4800

#define GPSRX 4
#define GPSTX 5

#define GSMRX 2
#define GSMTX 3

TinyGPS gps;
SoftwareSerial GPS(GPSRX, GPSTX);
SerialGSM cell(GSMRX,GSMTX); // RX, TX

void setup()
{
  Serial.begin(SERIALBAUD);
  GPS.begin(GPSBAUD);
  cell.begin(GSMBAUD);
  
  Serial.println("GPS - GSM communication test");
}

void loop()
{
  float lat, lon, alt, fcourse, fspeed;
  unsigned long fix_age;
  int year; // byte month, day;
  byte* EMPTY=NULL;
  byte hour, minute, second; //hundredths;
        
  // For two seconds we parse GPS data and report some key values
  GPS.listen(); // Listen on the GPS serial
  for (unsigned long start = millis(); millis() - start < 15000;)
  {
    while (GPS.available())
    {
      char c = GPS.read();
      //Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) { // Process new GPS data here        
        gps.f_get_position(&lat, &lon, &fix_age); // Lat/long in degrees
        alt = gps.f_altitude(); // Altitude in m
        fcourse = gps.f_course(); // Course in degrees
        fspeed = gps.f_speed_kmph(); // Speed in km/h
        gps.crack_datetime(&year, EMPTY, EMPTY, &hour, &minute, &second, EMPTY, &fix_age);
      }
    }
  }
  
  char output[20];
  sprintf(output, "Time: %2d:%2d:%2d", hour, minute, second);
  Serial.println(output);
  Serial.print("Lat/lon:"); Serial.print(lat,6); Serial.print(", "); Serial.println(lon,6);
  Serial.print("Alt: "); Serial.print(alt); Serial.print(" Speed: "); Serial.print(fspeed); Serial.print(" Course: "); Serial.println(fcourse);
  
}

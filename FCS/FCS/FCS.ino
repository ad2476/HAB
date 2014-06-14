#include "SoftwareSerial.h"
#include "Wire.h"
#include "Adafruit_MCP23008.h"
#include "math.h"

// HAB/Definitions/ is symlinked to sketchbook/libraries/Definitions/
#include "SerialGSM.h"
#include "TinyGPS.h"
#include "definitions.h"

unsigned long int time=0; // Running time in seconds
int state=LOW; // Remember the state of the LED pin

void toggleLED() {
  digitalWrite(13, state);
  state=!state;
}

void setup()
{
  /* Begin hw/sw/i2c/spi serial communications */
  Serial.begin(SERIALBAUD);
  GPS.begin(GPSBAUD);
  cell.begin(GSMBAUD);

  /* Set up I/O port expander */
  mcp.begin();
  for(int pin=S0; pin<_0GD; pin++)
    mcp.pinMode(pin, OUTPUT); // Set GP0-GP3 as outputs: for analog mux
  mcp.pinMode(_0GD, INPUT); // Accelerometer 0g detect

  Serial.println(F("HAB FCS v.1.0"));
  
  /* Read BMP180 EEPROM coefficients */
  ac1 = read_n_bytes(0xAA, 2);
  ac2 = read_n_bytes(0xAC, 2);
  ac3 = read_n_bytes(0xAE, 2);
  ac4 = read_n_bytes(0xB0, 2);
  ac5 = read_n_bytes(0xB2, 2);
  ac6 = read_n_bytes(0xB4, 2);
  b1 = read_n_bytes(0xB6, 2);
  b2 = read_n_bytes(0xB8, 2);
  mb = read_n_bytes(0xBA, 2);
  mc = read_n_bytes(0xBC, 2);
  md = read_n_bytes(0XBE, 2);

  /* Initialise the cell module 
  cell.listen();
  cell.Verbose(true);
  cell.Boot();
  cell.checkSignalQuality();
  cell.FwdSMS2Serial();
  cell.Rcpt(RCPT);
  cell.Message("Starting FCS...");
  cell.SendSMS(); */
  
  //delay(30000); // Wait 30s for things to clear
}

void loop()
{
  char GPSbuf[80];
  char databuf[50];
  /*float zrot, x, y, z;
  int freefall; */
  int alt, t, interior_temp; int32_t b5; // Altitude in m (max error 7m below actual) - from BMP180
        
  // For 15 seconds we parse GPS data and report some key values, and log sensor data every 500ms
  GPS.listen(); // Listen on the GPS software serial
  for (unsigned long start = millis(); millis() - start < 15000;) // The total time of all non-GSM operations must equal 15s
  {    
    if(((millis()-start) % 500) == 0) {
      toggleLED();
      /* Exterior pressure, temperature data */
      b5 = bmpTemp();
      pressure = calcPressure(b5);
      alt = calcAltitude();
      
      /* Interior temperature */
      interior_temp = thermistor(analogRead(THERM));
      
      Serial.print("\t Sensors:> "); Serial.print(pressure); Serial.print(" "); Serial.print(alt); Serial.print(" | ");
      Serial.print(exterior_temp); Serial.print(" "); Serial.println(interior_temp);
    }
    
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


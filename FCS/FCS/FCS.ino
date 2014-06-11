#include "SoftwareSerial.h"
#include "Wire.h"
#include "Adafruit_MCP23008.h"

// HAB/Definitions/ is symlinked to sketchbook/libraries/Definitions/
#include "SerialGSM.h"
#include "TinyGPS.h"
#include "definitions.h"

unsigned long int time=0; // Running time in seconds

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
  
  // Altitude in m (max error 7m below actual) - from BMP180
  int alt; int32_t b5;

  /* Exterior pressure, temperature data */
  b5 = bmpTemp();
  pressure = calcPressure(b5);
  alt = calcAltitude();

  // Interior temperature data:
  interior_temp = tmpTemp(muxRead(TMP));

  // Rotation data:
  float zrot = gyroRot(muxRead(ZX1));

  // Acceleration data:
  float x = gAccel(muxRead(GX));
  float y = gAccel(muxRead(GY));
  float z = gAccel(muxRead(GZ));
        
  // For 15 seconds we parse GPS data and report some key values
  GPS.listen(); // Listen on the GPS serial
  for (unsigned long start = millis(); millis() - start < 15000;) // TODO: The listen time must equal 15-[time for all other non-GSM tasks to complete]
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


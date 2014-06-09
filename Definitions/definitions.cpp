/* Define all FCS functions here, to prevent a mess of functions in FCSmain.ino
   These should be relatively stable functions - any unstable functions should
   remain in FCSmain.ino                                                     */

#include <definitions.h>

/* Packs all relevant GPS data into a logging string for OpenLog and SMS */
void packGPSdata(char* strbuf) {
  long lat, lon;
  int year;
  unsigned long alt, kspeed;
  unsigned long fix_age;
  byte hour, minute, second, IDC;

  gps.get_position(&lat, &lon, &fix_age); // Lat/long in millionths of degrees
  alt = gps.altitude(); // Altitude in cm
  kspeed = gps.speed(); // Speed in 100ths of knots

  gps.crack_datetime(&year, &IDC, &IDC, &hour, &minute, &second, &IDC, &fix_age);

  // Pack it all into one output
  sprintf(strbuf, "%2d:%2d:%2d | %ld %ld | %ld | %ld", hour, minute, second, lat, lon, alt, kspeed);
}

int tmpTemp(int analog) {
  int mV = map(analog, 0, 1023, 0, 3300); // map to mV
  return (mV/10 - 50);
}

float gyroRot(int analog) {
  int mV = map(analog, 0, 1023, 0, 3300); // map to mV
  return ((float)mV/8.3 - 120.0 - 32.0); // 32.0 is a linear correction I applied...
}

float gAccel(int analog) {
  int mV = map(analog, 0, 1023, 0, 3300);
  return ((float)mV/850.0-1.7);
}

// Read from a mux pin
int muxRead(int pin) {
  int s0, s1, s2, s3;
  if(pin>0xFF || pin<0x0) return -1;

  s0 = (pin & 0x1) >> S0;
  s1 = (pin & 0x2) >> S1;
  s2 = (pin & 0x4) >> S2;
  s3 = (pin & 0x8) >> S3;

  mcp.digitalWrite(S0, s0);
  mcp.digitalWrite(S1, s1);
  mcp.digitalWrite(S2, s2);
  mcp.digitalWrite(S3, s3);
  delay(10);
  return analogRead(SIG);
}

/* ---- Bunch of functions for BMP180 ---- */

// Read uncompensated temperature
int32_t bmpTemp()
{
  int32_t x1, x2, b5, UT;

  Wire.beginTransmission(BMPADDR); // Start transmission to device
  Wire.write(0xf4); // Sends register address
  Wire.write(0x2e); // Write data
  Wire.endTransmission(); // End transmission
  delay(5); // Datasheet suggests 4.5 ms
  
  UT = read_n_bytes(0xf6, 2); // Read uncompensated TEMPERATURE value

  // Calculate true temperature
  x1 = (UT - (int32_t)ac6) * (int32_t)ac5 >> 15;
  x2 = ((int32_t)mc << 11) / (x1 + (int32_t)md);
  b5 = x1 + x2;
  exterior_temp = (int)((b5 + 8) >> 4)*10.0; // temperature in hundredths of deg-C
  return b5;
}

// Read uncompensated pressure
int32_t uncompPressure()
{
  int32_t value;
  Wire.beginTransmission(BMPADDR); // Start transmission to device
  Wire.write(0xf4); // Sends register address to read from
  Wire.write(0x34 + (OSS << 6)); // Write data
  Wire.endTransmission(); // SEd transmission
  delay(OSD); // Oversampling setting delay
  Wire.beginTransmission(BMPADDR);
  Wire.write(0xf6); // Register to read
  Wire.endTransmission();
  Wire.requestFrom(BMPADDR, 3); // Request three bytes
  if(Wire.available() >= 3)
  {
    value = (((int32_t)Wire.read() << 16) | ((int32_t)Wire.read() << 8) | ((int32_t)Wire.read())) >> (8 - OSS);
  }
  return value; // Return value
}

/* Returns truncated pressure as int (to save space) */
int calcPressure(int32_t b5) {
  int32_t x1, x2, x3, b3, b6, p, UP;
  uint32_t b4, b7;

  UP = uncompPressure(); // Read raw pressure

  b6 = b5 - 4000;
  x1 = (b2 * (b6 * b6 >> 12)) >> 11;
  x2 = ac2 * b6 >> 11;
  x3 = x1 + x2;
  b3 = (((ac1 * 4 + x3) << OSS) + 2) >> 2;
  x1 = ac3 * b6 >> 13;
  x2 = (b1 * (b6 * b6 >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (uint32_t)(x3 + 32768)) >> 15;
  b7 = ((uint32_t)UP - b3) * (50000 >> OSS);
  if(b7 < 0x80000000) { p = (b7 << 1) / b4; } else { p = (b7 / b4) << 1; } // or p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  
  return (int)((p + ((x1 + x2 + 3791) >> 4)) / 100.0f); // Return pressure in mbar
}

int calcAltitude() {
  float p0 = 1013.25; // Sea level std. atmos. pressure
  return 44330*(1-pow((float)pressure/p0, 0.1903));
}

uint16_t read_n_bytes(uint8_t reg, int n) {
  uint16_t value=0;
  Wire.beginTransmission(BMPADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(BMPADDR, n);
  if(Wire.available()>=n) {
    if(n==1) value=Wire.read();
    else if(n==2) value=(Wire.read() << 8) | Wire.read();
  }
    
  return value;
  
}


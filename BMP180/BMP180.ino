#include <Wire.h>

#define BMPADDR 0x77

// Store sensor PROM values
int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
uint16_t ac4, ac5, ac6;

/* Ultra low power (3 uA): OSS=0, OSD=5ms
   Standard (5 uA): OSS=1, OSD=8ms
   High (7 uA): OSS=2, OSD=14ms
   Ultra high (12 uA): OSS=3, OSD=26ms
   Advanced (32 uA): OSS=3, OSD=77ms */
#define OSS 1
#define OSD 8

float exterior_temp, pressure;

void setup() {
  Wire.begin();
  
  Serial.begin(9600);
  
  /* Read sensor coefficients */
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

  Serial.println("Temp (C) | Alt (m) | Press (mbar)");
  delay(100);
}

void loop() {
  int32_t b5 = bmpTemp();
  
  Serial.print(exterior_temp);
  
  pressure = calcPressure(b5);
  int alt = calcAltitude();
  
  Serial.print(" "); Serial.print(alt);
  
  Serial.print(" "); Serial.println(pressure);

  delay(500);
}

// Read uncompensated temperature
int32_t bmpTemp()
{
  int32_t x1, x2, b5, UT;

  Wire.beginTransmission(BMPADDR); // Start transmission to device 
  Wire.write(0xf4);                       // Sends register address
  Wire.write(0x2e);                       // Write data
  Wire.endTransmission();                 // End transmission
  delay(5);                               // Datasheet suggests 4.5 ms
  
  UT = read_n_bytes(0xf6, 2);                // Read uncompensated TEMPERATURE value

  // Calculate true temperature
  x1 = (UT - (int32_t)ac6) * (int32_t)ac5 >> 15;
  x2 = ((int32_t)mc << 11) / (x1 + (int32_t)md);
  b5 = x1 + x2;
  exterior_temp  = (b5 + 8) >> 4;
  exterior_temp = exterior_temp / 10.0;                           // Temperature in celsius 
  return b5;  
}

//  Read uncompensated pressure
int32_t uncompPressure()
{
  int32_t value; 
  Wire.beginTransmission(BMPADDR);   // Start transmission to device 
  Wire.write(0xf4);                         // Sends register address to read from
  Wire.write(0x34 + (OSS << 6));            // Write data
  Wire.endTransmission();                   // SEd transmission
  delay(OSD);                               // Oversampling setting delay
  Wire.beginTransmission(BMPADDR);
  Wire.write(0xf6);                         // Register to read
  Wire.endTransmission();
  Wire.requestFrom(BMPADDR, 3);      // Request three bytes
  if(Wire.available() >= 3)
  {
    value = (((int32_t)Wire.read() << 16) | ((int32_t)Wire.read() << 8) | ((int32_t)Wire.read())) >> (8 - OSS);
  }
  return value;                             // Return value
}

float calcPressure(int32_t b5) {
  int32_t x1, x2, x3, b3, b6, p, UP;
  uint32_t b4, b7; 

  UP = uncompPressure();                         // Read raw pressure

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
  
  return (p + ((x1 + x2 + 3791) >> 4)) / 100.0f; // Return pressure in mbar
}

int calcAltitude() {
  int p0 = 1013.25; // Sea level std. atmos. pressure
  return 44330*(1-pow(pressure/p0, 0.1903));
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

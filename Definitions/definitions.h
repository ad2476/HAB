#ifndef _definitions_H
#define _definitions_H

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include "Adafruit_MCP23008.h"

/* --- Serial baud rates --- */
#define GPSBAUD 9600
#define SERIALBAUD 9600
#define GSMBAUD 4800
/* ------------------------- */

/* --- GPS/GSM-specific  --- */
/* --- definitions       --- */
#define PREC1 6
#define PREC2 2

#define LAT 0
#define LON 1
#define ALT 2
#define SPE 3
#define COU 4

#define RCPT "+12035391858"

void packGPSdata(char* strbuf);

/* ------------------------- */

/* --- Analog/Digital Pin--- */
/* --- Definitions       --- */
// When driven high, this pin will powerdown
// any non-critical devices
#define SIG A0
// A1-A3 unused
// A4 and A5 are reserved for I2C

/* Extended analog pins: */
#define TMP 0
#define ZX1 1
#define GX 2
#define GY 3
#define GZ 4

/* Digital pins */
#define GSMRX 2
#define GSMTX 3
#define GPSRX 4
#define GPSTX 5
#define POWERDOWN 6
// 7-9 unused
// Pins 10-13 reserved for SPI

// Read from a mux pin
int muxRead(int pin);

/* ------------------------- */

/* --- BMP180 sensor stuff --- */
// Store BMP180 EEPROM calibration values
#define OSS 1
#define OSD 8

int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
uint16_t ac4, ac5, ac6;

int exterior_temp, pressure; // exterior_temp in hundredths-°C, pressure truncated to mbar

int32_t bmpTemp(); // Read uncompensated temperature
int32_t uncompPressure(); // Read uncompensated pressure
int calcPressure(int32_t b5); // Returns truncated pressure as int (to save space)
int calcAltitude();
uint16_t read_n_bytes(uint8_t reg, int n);

/* --- TMP36 sensor stuff: --- */
int interior_temp;
int tmpTemp(int analog);

/* --- Gyro stuff --- */
float zrot; // Rotation around z


#endif

#ifndef _definitions_H
#define _definitions_H

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <SerialGSM.h>
#include <TinyGPS.h>
#include <Wire.h>
#include "Adafruit_MCP23008.h"

/* --- Serial baud rates --- */
#define GPSBAUD 9600
#define SERIALBAUD 9600
#define GSMBAUD 4800
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

/* MCP expanded pins */
#define S0 0
#define S1 1
#define S2 2
#define S3 3
#define _0GD 7

Adafruit_MCP23008 mcp;

// Read from a mux pin
//extern int muxRead(int pin);

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

TinyGPS gps;
SoftwareSerial GPS(GPSRX, GPSTX);
SerialGSM cell(GSMRX, GSMTX);

/* ------------------------- */

/* --- BMP180 sensor stuff --- */
// Store BMP180 EEPROM calibration values
#define OSS 1
#define OSD 8

int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
uint16_t ac4, ac5, ac6;

int exterior_temp, pressure; // exterior_temp in hundredths-°C, pressure truncated to mbar

/* --- TMP36 sensor stuff: --- */
int interior_temp;
//extern int tmpTemp(int analog);

/* --- Gyro stuff --- */

/* --- Accelerometer stuff --- */

/* ------------------------- */
/* --- I2C Addresses --- */
#define BMPADDR 0x77
 
#endif

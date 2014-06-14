#ifndef _definitions_H
#define _definitions_H

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <SerialGSM.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <math.h>

/* --- Serial baud rates --- */
#define GPSBAUD 9600
#define SERIALBAUD 9600
#define GSMBAUD 4800
/* ------------------------- */

/* --- Analog/Digital Pin--- */
/* --- Definitions       --- */
// When driven high, this pin will powerdown
// any non-critical devices
#define THERM A0
// A1-A3 unused
// A4 and A5 are reserved for I2C

/* Digital pins */
#define GSMRX 2
#define GSMTX 3
#define GPSRX 4
#define GPSTX 5
#define POWERDOWN 6
// 7-9 unused
// Pins 10-13 reserved for SPI

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

float exterior_temp, pressure; // exterior_temp in hundredths-°C, pressure truncated to mbar

/* Thermistor constants */
#define B 0.000334448

#define R0 10000.0
#define T0 298.15

/* --- Gyro stuff --- */

/* --- Accelerometer stuff --- */

/* ------------------------- */
/* --- I2C Addresses --- */
#define BMPADDR 0x77
 
#endif

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
/* ------------------------- */

/* --- Analog/Digital Pin--- */
/* --- Definitions       --- */
// When driven high, this pin will powerdown
// any non-critical devices
#define TMP A0
#define SIG A1
// A2-A3 unused
// A4 and A5 are reserved for I2C

#define GSMRX 2
#define GSMTX 3
#define GPSRX 4
#define GPSTX 5
#define POWERDOWN 6
// 7-9 unused
// Pins 10-13 reserved for SPI

/* ------------------------- */

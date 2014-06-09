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


// Only making use of Zx4 data (x4 precision data of rotation around Z axis
// Can alternately use Zx1 (for testing and whatnot)
// HP - high-pass filter reset (not really sure what that does yet...)
// PD - Power down (drive high to power down chip)
// ST - Self test (drive high to initiate self-test)
#include <definitions.h>

#define ZX1 A3

// Low sensitivity: 8.3 mV/(deg/s) - range: +/-120 deg/s
#define LOWSENS 8.3
#define LOWRANGE 120.0
// High sensitivity: 33.3 mV/(deg/s) - range +/30 deg/s
#define HIGHSENS 0.03
#define HIGHRANGE 30.0

float zrot; // Rotation around z

float toDegS(int analog) {
  int mV = map(analog, 0, 1024, 0, 3300); // map to mV
  
  return ((float)mV/LOWSENS - LOWRANGE - 32.0);
}


void setup() {
  Serial.begin(SERIALBAUD);
}

void loop() {
  zrot = toDegS(analogRead(ZX1));
  
  Serial.print("Z-rotation: "); Serial.println(zrot);
  
  delay(500);
}

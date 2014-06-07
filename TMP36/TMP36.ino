#include <definitions.h>

int temp;

int toDegC(int analog) {
  int mV = map(analog, 0, 1023, 0, 3300); // map to mV
  
  return (int)((float)(mV/10) - 50);

}

void setup() {
  Serial.begin(GPSBAUD);
}

void loop() {
  temp=toDegC(analogRead(TMP));
  
  Serial.print("Temperature: ");
  Serial.println(temp);
  
  delay(1000);
}


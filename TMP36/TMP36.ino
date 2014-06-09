#include <definitions.h>

int temp;
int time=0;

int toDegC(int analog) {
  int mV = map(analog, 0, 1023, 0, 3300); // map to mV
  
  return (mV/10 - 50);

}

void setup() {
  Serial.begin(GPSBAUD);
  
  Serial.println("Time (s) | Temp (C)");
}

void loop() {
  temp=toDegC(analogRead(TMP));
  
  Serial.print(time); Serial.print(" ");
  Serial.println(temp);
  
  time++;
  delay(1000);
}


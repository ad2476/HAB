// Just hooked up to analog inputs on the arduino. Not making use of self-test (ST), G-select, or sleep in this example code
// G-select hardwired to 1.5g range (tied to GND), sleep tied to VCC, ST tied to GND

#define _0GD 8
#define XOUT A1
#define YOUT A2
#define ZOUT A3

int zero_g;
float x, y, z;


// Convert analog reading to g
float toG(int analog) {
  int mV = map(analog, 0, 1023, 0, 3300); // map to mV
  
  return ((float)mV/850.0-1.7);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(_0GD, INPUT);
}

void loop() {
  zero_g = digitalRead(_0GD);
  x = toG(analogRead(XOUT)); // map to mV
  y = toG(analogRead(YOUT));
  z= toG(analogRead(ZOUT));
  
  Serial.print("0GD: "); Serial.print(zero_g);
  Serial.print(" Xout: "); Serial.print(x);
  Serial.print(" Yout: "); Serial.print(y);
  Serial.print(" Zout: "); Serial.println(z);
  
  delay(500);  
}

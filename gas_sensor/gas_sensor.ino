#define LED 13

int value;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  delay(100);
  digitalWrite(LED, HIGH);
  value = analogRead(0);
  Serial.println(value, DEC);
  delay(100);
  digitalWrite(LED, LOW);
}

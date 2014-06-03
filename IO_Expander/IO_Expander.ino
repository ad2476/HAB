// IO Expander (MCP23008) test code
#include <Wire.h>
#include "Adafruit_MCP23008.h"

#define LED1 0
#define LED2 1

Adafruit_MCP23008 mcp; 

void setup() {
  mcp.begin();
  
  mcp.pinMode(LED1, OUTPUT);
  mcp.pinMode(LED2, OUTPUT);
}

void loop() {
  delay(500);
  mcp.digitalWrite(LED1, LOW);
  mcp.digitalWrite(LED2, HIGH);
  delay(500);
  mcp.digitalWrite(LED1, HIGH);
  mcp.digitalWrite(LED2, LOW);
}

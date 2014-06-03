// IO Expander (MCP23008) test code
#include <Wire.h>
#include "Adafruit_MCP23008.h"

Adafruit_MCP23008 mcp; 

void setup() {
  mcp.begin();
  
  mcp.pinMode(0, OUTPUT);
}

void loop() {
  delay(500);
  mcp.digitalWrite(0, HIGH);
  delay(500);
  mcp.digitalWrite(0, LOW);
}

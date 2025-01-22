#include <Arduino.h>
#include "mcp23017.h"

// TODO: declare mcp23017 object
Mcp23017 mcp(0x20);

void setup() {
  // TODO: initialize i2c and mcp23017 object
  Wire.begin();
  uint8_t dir[8] = {0, 0, 0, 0, 0, 1, 1, 0};
  mcp.begin(dir);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  // TODO: Write tests here
  Serial.println("Hell");
  delay(1000);

  mcp.set_state(7, 0);

 delay(1000);

  mcp.set_state(7, 1);

  delay(1000);
}
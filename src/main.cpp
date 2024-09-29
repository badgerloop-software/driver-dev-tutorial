#include <Arduino.h>
#include "mcp23017.h"

// TODO: declare mcp23017 object
Mcp23017 mcp(0x20);

void setup() {
  // TODO: initialize i2c and mcp23017 object
  Wire.begin();
  uint8_t dir[8] = {0, 0, 0, 0, 0, 1, 1, 1};
  mcp.begin(dir);
  Serial.begin(9600);
  Serial.println("Hello World");
}

void loop() {
  // TODO: Write tests here
  mcp.set_state(0, 0);
  int a = mcp.get_state(0);
  Serial.println(a);
  mcp.set_state(4, 0);
  a = mcp.get_state(4);
  Serial.println(a);

  delay(1000);

  mcp.set_state(0, 1);
  a = mcp.get_state(0);
  Serial.println(a);
  mcp.set_state(4, 1);
  a = mcp.get_state(4);
  Serial.println(a);
}
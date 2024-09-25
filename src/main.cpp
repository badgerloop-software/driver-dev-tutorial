#include <Arduino.h>
#include "mcp23017.h"

#define address 

// TODO: declare mcp23017 object
Mcp23017 mcp(0x20);

void setup() {
  // TODO: initialize i2c and mcp23017 object
  Wire.begin();

  uint8_t directions[8] = {1, 0, 0, 0, 0, 0, 0, 0};
  mcp.begin(directions);
}

void loop() {
  // TODO: Write tests here
  mcp.set_state(0, 1);
  mcp.set_state(4, 1);
  mcp.get_state(7);

  delay(1000);
}
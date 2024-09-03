#include <Wire.h>

#include "include/mcp23017.h"

Mcp23017 mcp_obj(0x20);

void setup() {
  Wire.begin();
  // TODO: initialize the mcp23017 object
  uint8_t directions[8] = {0,0,0,0,1,1,1,1};
  mcp_obj.begin(directions);  
}

void loop() {
  // TODO: write tests
}
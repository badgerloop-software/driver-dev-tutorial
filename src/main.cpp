#include <Arduino.h>
#include "mcp23017.h"

// TODO: declare mcp23017 object
Mcp23017 mcp(0x20); // i2c address 
void setup() {
  // initialize Serial for printouts
  Serial.begin(115200);
  printf("Test begins\n"); 
  // TODO: initialize I2C and mcp23017 object

  Wire.begin();

  uint8_t directions[8] = {0, 1, 0, 1, 0, 1, 1, 0};

  if (mcp.begin(directions) != 0) 
  {
    Serial.println("initialization failed");
  }
  else 
  {
    Serial.println("initialization success");
  }
}

void loop() {
  // TODO: Write tests here

  // 1) set pin 0 HIGH
  mcp.set_state(0, 1);
  delay(500);
  uint8_t state = mcp.get_state(0);
  if (state == 1)
  {
    Serial.println("test 1 passed");
  }
  else
  {
    Serial.println("test 1 failed");
  }

  // 2) set pin 1 LOW
  mcp.set_state(1, 0);
  delay(500);
  uint8_t state = mcp.get_state(1);
  if (state == 0)
  {
    Serial.println("test 2 passed");
  }
  else
  {
    Serial.println("test 2 failed");
  }

  // 3) change direction of pin 0 to HIGH
  mcp.set_dir(0, 1);
  delay(500);
  uint8_t dir = mcp.get_dir(1);
  if (dir == 1) 
  {
    Serial.println("test 3 passed");
  } else 
  {
    Serial.println("test 3 failed");
  }

  // 3) change direction of pin 1 to LOW
  mcp.set_dir(1, 0);
  delay(500);
  uint8_t dir = mcp.get_dir(1);
  if (dir == 1) 
  {
    Serial.println("test 4 passed");
  } else 
  {
    Serial.println("test 4 failed");
  }

}



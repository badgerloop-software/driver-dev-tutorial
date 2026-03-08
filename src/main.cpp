#include "mcp23017.h"
#include <Arduino.h>

// Ignore the compiler instruction related code (the ones that start with #) if
// you are not attempting the optional section

// Uncomment the statement below this line to work on the optional section
//  #define EXTERNAL_RESET_ENABLED

#ifdef EXTERNAL_RESET_ENABLED
#define RESET_PIN ______ // TODO: Add the pin thats doing the reset
#endif

// TODO: declare mcp23017 object
Mcp23017 mcp(0x20); // this might be wrong idk?
// directions array: 0 for Output, 1 for Input.
// GPA0 (LED1) -> 0, GPA4 (LED2) -> 0, GPA7 (Switch) -> 1
uint8_t pin_dirs[8] = {0, 0, 0, 0, 0, 0, 0, 1};

#define LED1_PIN 0
#define LED2_PIN 4
#define SWITCH_PIN 7

void setup() {
  // initialize Serial for printouts
  Serial.begin(115200);
  printf("Test begins\n");

#ifdef EXTERNAL_RESET_ENABLED
  // TODO: Configure the digital pin acting as a reset an output pin and reset
  // the IOExpander registers to their default values. Make sure to check if it
  // is an Active-High or Active-Low reset
#endif
  // TODO: initialize I2C and mcp23017 object
  Wire.begin();
  int status = mcp.begin(pin_dirs);
  if (status == 0) {
    Serial.println("MCP23017 initialized successfully!");
  } else {
    Serial.println(
        "MCP23017 initialization failed: IODIRA did not match default.");
  }
}

void loop() {
  // TODO: Write tests here

  // Turn LEDs on
  mcp.set_state(LED1_PIN, 1);
  mcp.set_state(LED2_PIN, 1);
  Serial.println("LEDs ON");
  delay(1000);

  // Turn LEDs off
  mcp.set_state(LED1_PIN, 0);
  mcp.set_state(LED2_PIN, 0);
  Serial.println("LEDs OFF");
  delay(1000);

  // Read value of the switch
  uint8_t switch_val = mcp.get_state(SWITCH_PIN);
  Serial.print("Switch state: ");
  Serial.println(switch_val);
  delay(1000);
}
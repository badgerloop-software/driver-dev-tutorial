#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:
#define IODIRA 0x00
#define GPIO 0x09

// Record the device address
Mcp23017::Mcp23017(int addr) { this->addr = addr; }

// This function returns the value of a specific pin's direction
uint8_t Mcp23017::get_dir(int pin) {
  Wire.beginTransmission(addr);
  Wire.write(IODIRA);
  Wire.endTransmission();
  Wire.requestFrom(addr, 1);
  uint8_t val = Wire.read();
  return (val >> pin) & 1;
}

// This function returns the value of a specific state register
uint8_t Mcp23017::get_state(int pin) {
  Wire.beginTransmission(addr);
  Wire.write(GPIO);
  Wire.endTransmission();
  Wire.requestFrom(addr, 1);
  uint8_t val = Wire.read();
  return (val >> pin) & 1;
}

// TODO: Write to directions register
// A bit set to 0 indicates the pin is an output
// A bit set to 1 indicates the pin is an input
int Mcp23017::set_dir(int pin, uint8_t dir) {
  
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) { return 0; }

// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
  int rc;

  // TODO: Add device ID check

  return 0;
}

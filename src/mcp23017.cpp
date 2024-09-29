#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:
#define DIRECTIONS_REGISTER 0x00
#define STATE_REGISTER 0x09

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) {
   Mcp23017::addr = addr;
}

uint8_t Mcp23017::get_dir(int pin) {
   // specify what register to read from
   Wire.beginTransmission(Mcp23017::addr);
   Wire.write(DIRECTIONS_REGISTER);
   Wire.endTransmission();

   Wire.requestFrom(DIRECTIONS_REGISTER, 1);

   // read a byte from the specified register
   uint8_t byte = Wire.read();

   // return part of the byte that corresponds to the specific pin
   return (byte >> pin) & 1;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
   // specify what register to read from
   Wire.beginTransmission(Mcp23017::addr);
   Wire.write(STATE_REGISTER);
   Wire.endTransmission();
   Wire.requestFrom(STATE_REGISTER, 1);

   // read a byte from the specified register
   uint8_t byte = Wire.read();

   // return part of the byte that corresponds to the specific pin
   return (byte >> pin) & 1;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
   Wire.beginTransmission(Mcp23017::addr);
   Wire.write(DIRECTIONS_REGISTER);
   Wire.endTransmission();
   Wire.requestFrom(DIRECTIONS_REGISTER, 1);
   uint8_t prev = Wire.read();
   uint8_t byte = (prev >> (pin + 1)) << (pin + 1);
   byte += (dir << pin);
   byte += (prev << (8 - pin)) >> (8 - pin);

   Wire.beginTransmission(Mcp23017::addr);
   uint8_t writtenData[2] = {DIRECTIONS_REGISTER, byte};
   Wire.write(writtenData, 2);
   Wire.endTransmission();

   return byte;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
   Wire.beginTransmission(Mcp23017::addr);
   Wire.write(STATE_REGISTER);
   Wire.endTransmission();
   Wire.requestFrom(STATE_REGISTER, 1);
   uint8_t prev = Wire.read();
   uint8_t byte = (prev >> (pin + 1)) << (pin + 1);
   byte += (val << pin);
   byte += (prev << (8 - pin)) >> (8 - pin);

   Wire.beginTransmission(Mcp23017::addr);
   uint8_t writtenData[2] = {STATE_REGISTER, byte};
   Wire.write(writtenData, 2);
   Wire.endTransmission();

   return byte;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
   int rc;

   // TODO: Add device ID check
   Wire.beginTransmission(Mcp23017::addr);
   Wire.write(DIRECTIONS_REGISTER);
   Wire.endTransmission();
   Wire.requestFrom(DIRECTIONS_REGISTER, 1);
   uint8_t byte = Wire.read();
   if (!(byte ^ 0xFF)) {
      return 0;
   }


   for (int i = 0; i < 8; i++) {
      set_dir(i, directions[i]);
   }

   return 1;
}

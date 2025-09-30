#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:
#define IODIRA 0x00
#define GPIOA 0x12
int addr;

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) {
    this->addr = addr;
    Wire.begin();
}

uint8_t Mcp23017::get_dir(int pin) {
    Wire.beginTransmission(addr);
    Wire.write(IODIRA);
    Wire.endTransmission();
    Wire.requestFrom(addr, 1);
    uint8_t byte = Wire.read();
    int bit = (byte >> pin) & 1;
    return bit;
}


uint8_t Mcp23017::get_state(int pin) {
    Wire.beginTransmission(addr);
    Wire.write(GPIOA);
    Wire.endTransmission();
    Wire.requestFrom(addr, 1);
    uint8_t byte = Wire.read();
    int bit = (byte >> pin) & 1;
    return bit;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    Wire.beginTransmission(addr);
    Wire.write(IODIRA);
    Wire.endTransmission();
    Wire.requestFrom(addr, 1);
    uint8_t byte = Wire.read();
    byte = (byte & ~(1 << pin)) | (dir << pin);
    Serial.printf("okokok %d \n", byte);
    Wire.beginTransmission(addr);
    Wire.write(IODIRA);
    Wire.write(byte);
    Wire.endTransmission();
    return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    Wire.beginTransmission(addr);
    Wire.write(GPIOA);
    Wire.endTransmission();
    Wire.requestFrom(addr, 1);
    uint8_t byte = Wire.read();
    byte = (byte & ~(1 << pin)) | (val << pin);
    Wire.beginTransmission(addr);
    Wire.write(GPIOA);
    Wire.write(byte);
    Wire.endTransmission();
    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {

    // Read IODIRA and print the byte stored in it

    Wire.beginTransmission(addr);
    Wire.write(IODIRA);
    Wire.endTransmission();
    Wire.requestFrom(addr, 1);
    uint8_t byte = Wire.read();
    Serial.printf("%d \n", byte);


    int state;
    for (int i = 0; i < 8; i++) {
        state = set_dir(i, directions[i]);
        if (state)
            return 1;
    }
    // TODO: Add device ID check
}

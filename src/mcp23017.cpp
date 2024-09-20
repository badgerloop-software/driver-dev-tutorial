#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:


// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) {

}

uint8_t Mcp23017::get_dir(int pin) {
    return 0;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    return 0;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    // TODO: Add device ID check

    return 0;
}

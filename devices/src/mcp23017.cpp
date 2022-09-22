#include "mcp23017.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>

#include <iostream>


// TODO (optional): Define macros for useful register below:

// Calls parent constructor
Mcp23017::Mcp23017(int bus, int addr) : I2c(bus, addr) {}


// TODO: Read from direction register
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
int Mcp23017::begin() {
    int rc;

    // Make sure we can access the i2c bus
    if (!this->is_open()) {
        rc = this->open_i2c();
        if (rc) return rc;
    }

    // TODO: Set pin directions

    return 0;
}

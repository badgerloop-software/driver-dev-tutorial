#include "mcp23017.h"


// TODO (optional): Define macros for useful register below:
#define REGISTER_IODIRA 0x00
#define REGISTER_GPIOA 0x12

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr, I2C* i2cBus) {
    this->addr = addr;
    this->i2cBus = i2cBus;
}

uint8_t Mcp23017::get_dir(int pin) {
    char buf[1] = {REGISTER_IODIRA};
    
    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 1, false);

    return (buf[0] && (1 << pin)) > 0;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    char buf[1] = {REGISTER_GPIOA};
    
    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 1, false);

    return (buf[0] && (1 << pin)) > 0;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    char buf[2] = {REGISTER_IODIRA, dir};

    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 1, false);

    uint8_t data = buf[0];

    if (dir) {
        data |= 1 << pin;
    } else {
        data &= ~(1 << pin);
    }

    buf[0] = REGISTER_IODIRA;
    buf[1] = data;
    this->i2cBus->write(this->addr, buf, 2, false);
    return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    char buf[2] = {REGISTER_GPIOA, val};

    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 1, false);

    uint8_t data = buf[0];

    if (val) {
        data |= 0x1 << pin;
    } else {
        data &= ~(0x1 << pin);
    }

    buf[0] = REGISTER_GPIOA;
    buf[1] = data;
    this->i2cBus->write(this->addr, buf, 2, false);
    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    char buf[1] = {REGISTER_IODIRA};
    
    this->i2cBus->write(this->addr, buf, 1, false);
    this->i2cBus->read(this->addr, buf, 1, false);

    uint8_t data = buf[0];

    // TODO: Add device ID check
    if (data != 0xff) {
        return 1;
    }

    for (int i = 0; i < 8; i++) {
        set_dir(i, directions[i]);
    }

    return 0;
}

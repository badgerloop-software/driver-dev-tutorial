#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:
#define IODIRA 0x00
#define IODIRB 0x01
#define GPIOA 0x12
#define GPIOB 0x13

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) {
    this->addr = addr;
}

uint8_t Mcp23017::get_dir(int pin) {
    Wire.requestFrom(IODIRA, 1);
    int w = 0;
    if(Wire.available()){
        w = Wire.read();
    }
    else{
        return 0;
    }
    int p = 1 & (w >> pin);
    return p;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    Wire.requestFrom(GPIOA, 1);
    int w = 0;
    if(Wire.available()){
        w = Wire.read();
    }
    else{
        return 0;
    }
    int p = 1 & (w >> pin);
    return p;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    Wire.requestFrom(this->addr, 1);
    int w = 0;
        if (Wire.available()){
        w = Wire.read();
    }
    else{
        return 0;
    }
    if (dir == 1){
        w = w | (1 << pin);
    }
    else{
        w = w & ~(1 << pin);
    }
        
    uint8_t data[2];
    data[0] = IODIRA;
    data[1] = w;
    
    Wire.beginTransmission(this->addr);
    Wire.write(data, 2);
    Wire.endTransmission();
    return w;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    Wire.requestFrom(this->addr, 1);
    int w = 0;
        if (Wire.available()){
        w = Wire.read();
    }
    else{
        return 0;
    }
    if (val == 1){
        w = w | (1 << pin);
    }
    else{
        w = w & ~(1 << pin);
    }

    uint8_t data[2];
    data[0] = GPIOA;
    data[1] = w;
    
    Wire.beginTransmission(this->addr);
    Wire.write(data, 2);
    Wire.endTransmission();
    return w;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    // TODO: Add device ID check
    Wire.requestFrom(this->addr, 1);
    if (Wire.available()){
        rc = Wire.read();
    }
    else{
        return 0;
    }

    int c = 0;

    while (c < 8){
        rc = set_dir(c, directions[c]);
        c++;
    }

    return 0;
}

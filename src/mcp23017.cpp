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
    Wire.beginTransmission(this->addr);
    uint8_t dataReg = IODIRA;
    Wire.write(dataReg);
    Wire.endTransmission();

    Wire.requestFrom(this->addr, 1);

    int data = Wire.read();

    int p = 1 & (data >> pin);
    return p;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    Wire.beginTransmission(this->addr);
    uint8_t dataReg = GPIOA;
    Wire.write(dataReg);
    Wire.endTransmission();

    Wire.requestFrom(this->addr, 1);

    int data = Wire.read();

    int p = 1 & (data >> pin);
    return p;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    
    Wire.beginTransmission(this->addr);
    Wire.write(IODIRA);
    Wire.endTransmission();
    Wire.requestFrom(this->addr, 1);
    
    uint8_t byte = Wire.read();

    if (dir == 1){
        byte = byte | (1 << pin);
    }
    else{
        byte = byte & ~(1 << pin);
    }
        
    uint8_t data[2];
    data[0] = IODIRA;
    data[1] = byte;
    
    Wire.beginTransmission(this->addr);
    Wire.write(data, 2);
    Wire.endTransmission();
    return byte;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    Wire.beginTransmission(this->addr);
    Wire.write(GPIOA);
    Wire.endTransmission();
    Wire.requestFrom(this->addr, 1);
    
    uint8_t byte = Wire.read();

    if (val == 1){
        byte = byte | (1 << pin);
    }
    else{
        byte = byte & ~(1 << pin);
    }
        
    uint8_t data[2];
    data[0] = GPIOA;
    data[1] = byte;
    
    Wire.beginTransmission(this->addr);
    Wire.write(data, 2);
    Wire.endTransmission();
    return byte;
}


// Verifies that the device is accessible over I2C and sets pin directions
//Returns 1 if successful, 0 otherwise  
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    // TODO: Add device ID check

    Wire.beginTransmission(this->addr);
    Wire.write(IODIRA);
    Wire.endTransmission();
    Wire.requestFrom(this->addr, 1);

    if (Wire.available()){
        rc = Wire.read();
        if (rc != 0){ // Reset values for all pins is 0
            return 0; 
        }
    }
    else{
        return 0;
    }

    for (int c = 0; c < 8; c++){
        rc = set_dir(c, directions[c]);
    }

    return 1;
}

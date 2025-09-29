#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:
#define IODIRREG 0x00    // I/O Direction Register
#define GPIOREG  0x12   // GPIO Register

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) {

    this->addr = addr;


}

uint8_t Mcp23017::get_dir(int pin) {
    Wire.beginTransmission(addr);
    Wire.write(IODIRREG);          // Point to IODIR register 
    Wire.endTransmission();
    Wire.requestFrom(addr, 1); // Request 1 byte
    uint8_t diReg = Wire.read();
    
    return (diReg >> pin) & 0x01;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
   Wire.beginTransmission(addr);          // Point to GPIO register
   Wire.write(GPIOREG);
   Wire.endTransmission();
    Wire.requestFrom(addr, 1); // Request 1 byte
    uint8_t gpioreg = Wire.read();
    return (gpioreg >> pin) & 0x01;
}


// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    uint8_t diReg = get_dir(pin); // read current direction register
    if(dir ==1) {
        diReg |= (1 << pin); // set pin to input
    } else {
        diReg &= ~(1 << pin); // set pin to output
    }
    Wire.beginTransmission(addr);
    Wire.write(IODIRREG);          // Point to IODIR register
    Wire.write(diReg);             // Write updated direction
    Wire.endTransmission();
    
    return 0;
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
   uint8_t gpioreg =  get_state(pin); // read current state register
    if(val ==1) {
        gpioreg |= (1 << pin); // set pin high
    } else {
        gpioreg &= ~(1 << pin); // set pin low
    
    }
    Wire.beginTransmission(addr);
    Wire.write(GPIOREG);          // Point to GPIO register
    Wire.write(gpioreg);             // Write updated state
    Wire.endTransmission();
    return 0;
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;

    // TODO: Add device ID check
    uint8_t iodira_val = 0;
    for(int i=0; i<8; i++) {
        iodira_val |= (get_dir(i) << i);
        //iodira_val = (iodira_val << 1) | (get_dir(i));
    }

    Serial.printf("IODIRA register value: 0x%02X\n", iodira_val);

    if(iodira_val != 0xFF) {
        return 1; // Device ID mismatch
    }

    uint8_t dirByte = 0;
    for(int i=0; i<8; i++) {
        dirByte |= (directions[i] << i);
    }
    Serial.printf("Direction byte: 0x%02X\n", dirByte);
    Wire.beginTransmission(addr);
    Wire.write(IODIRREG);          // Point to IODIR register
    Wire.write(dirByte);           // Set directions
    Wire.endTransmission();


     iodira_val = 0;
    for(int i=0; i<8; i++) {
        iodira_val |= (get_dir(i) << i);
        //iodira_val = (iodira_val << 1) | (get_dir(i));
    }
    Serial.printf("MCP23017 initialized at address 0x%02X\n", iodira_val);

    return 0;
}

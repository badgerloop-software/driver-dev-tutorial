#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:
#define ioDirAddr 0x00
#define GPIOAddr 0x09

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) : addr(addr) { //member initializxation
    Wire.begin(addr); // Start wire library and join i2c bus
}

uint8_t Mcp23017::get_dir(int pin) {
    // request 1 byte from the register at 0x00 (iodir)
    // and store in the variable byteRead
    Wire.requestFrom(ioDirAddr, 1);
    uint8_t byteRead;
    while (Wire.available()){
       byteRead = Wire.read();
    }
    //moves desired bit to LSB and compares to 1
    uint8_t pinDir = (byteRead >> pin) & 1;
    return pinDir;
}


// TODO: Read from state register
uint8_t Mcp23017::get_state(int pin) {
    // Same functionality as above method
    Wire.requestFrom(GPIOAddr, 1);
    uint8_t byteRead;
    while (Wire.available()){
       byteRead = Wire.read();
    }
    uint8_t pinDir = (byteRead >> pin) & 1;
    return pinDir;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    Wire.requestFrom(ioDirAddr, 1);
    uint8_t byte;
    while (Wire.available()){
       byte = Wire.read();
    }
    if(dir == 1){ //If we want the pin to be on, we use OR logic 
        byte |= (dir << pin); // shift the mask by the pin amount
    }
    else if(dir == 0){ //Use AND NOT logic to get the pin to be off
        byte &= ~(dir << pin);
    }
    Wire.beginTransmission(ioDirAddr); //transmit the byte
    Wire.write(byte);
    Wire.endTransmission();

    return get_dir(pin); //checks if what we did worked
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    Wire.requestFrom(GPIOAddr, 1);
    uint8_t byte;
    while (Wire.available()){
       byte = Wire.read();
    }
    if(val == 1){
        byte |= (val << pin);
    }
    else if(val == 0){
        byte &= ~(val << pin);
    }
    Wire.beginTransmission(GPIOAddr);
    Wire.write(byte);
    Wire.endTransmission();

    return get_state(pin);
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;
    Wire.beginTransmission(ioDirAddr);
    //this method with nothing overloaded will return 0 if successful
    //and a different integer if it fails
    rc = Wire.endTransmission(); 

    if(rc == 0){
        Serial.println("IODIR Address verified at 0x");
        Serial.println(ioDirAddr, HEX);
    }
    else {
        Serial.println("No device found at address 0x");
        Serial.println(ioDirAddr, HEX);
    }

    //set the direction of each of the pins to the desired value
    for(int i = 0; i < 8; i++){
        set_dir(i, directions[i]);
    }

    //returns 1 byte from IODIR to see if the addresses were successfully changed
    Wire.requestFrom(ioDirAddr, 1);
    uint8_t byte;
    while (Wire.available()){
       byte = Wire.read();
    }
    return byte;
}

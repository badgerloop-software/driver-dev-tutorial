#include "mcp23017.h"

// TODO (optional): Define macros for useful register below:
#define IO_DIR_ADDR 0x00
#define GPIO_ADDR 0x09

// TODO: Initialize i2cBus member
Mcp23017::Mcp23017(int addr) : addr(addr) {} //member initialization

uint8_t Mcp23017::get_dir(int pin) {
    // first establish a connection with the i2bus
    Wire.beginTransmission(Mcp23017::addr);
    //Specify the register
    Wire.write(IO_DIR_ADDR);
    Wire.endTransmission();
    
    // request 1 byte from the register at 0x00 (iodir)
    // and store in the variable byteRead
    Wire.requestFrom(IO_DIR_ADDR, 1);
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
    Wire.beginTransmission(Mcp23017::addr);
    //Specify the register
    Wire.write(GPIO_ADDR);
    Wire.endTransmission();
    
    Wire.requestFrom(GPIO_ADDR, 1);
    uint8_t byteRead;
    while (Wire.available()){
       byteRead = Wire.read();
    }
    uint8_t pinDir = (byteRead >> pin) & 1;
    return pinDir;
}

// TODO: Write to directions register
int Mcp23017::set_dir(int pin, uint8_t dir) {
    Wire.beginTransmission(Mcp23017::addr);
    Wire.write(IO_DIR_ADDR);
    Wire.endTransmission();
    
    Wire.requestFrom(IO_DIR_ADDR, 1);
    uint8_t byte;
    while (Wire.available()){
       byte = Wire.read();
    }
    if(dir == 1){ //If we want the pin to be on, we use OR logic 
        byte |= (dir << pin); // shift the mask by the pin amount
    }
    else if(dir == 0){ //Use AND NOT logic to get the pin to be off
        byte &= ~(1 << pin);
    }
    Wire.beginTransmission(Mcp23017::addr);
    Wire.write(IO_DIR_ADDR);
    Wire.write(byte);
    Wire.endTransmission();

    return get_dir(pin); //checks if what we did worked
}

// TODO: Write to state register
int Mcp23017::set_state(int pin, uint8_t val) {
    Wire.beginTransmission(Mcp23017::addr);
    Wire.write(GPIO_ADDR);
    Wire.endTransmission();
    
    Wire.requestFrom(GPIO_ADDR, 1);
    uint8_t byte;
    while (Wire.available()){
       byte = Wire.read();
    }
    if(val == 1){
        byte |= (val << pin);
    }
    else if(val == 0){
        byte &= ~(1 << pin);
    }
    
    Wire.beginTransmission(Mcp23017::addr);
    Wire.write(GPIO_ADDR);
    Wire.write(byte);
    Wire.endTransmission();

    return get_state(pin);
}


// Verifies that the device is accessible over I2C and sets pin directions
int Mcp23017::begin(uint8_t directions[8]) {
    int rc;
    
    Wire.beginTransmission(Mcp23017::addr);
    Wire.write(IO_DIR_ADDR);
    Wire.endTransmission();

    Wire.requestFrom(IO_DIR_ADDR, 1);
    uint8_t rc;
    while (Wire.available()){
       rc = Wire.read();
    }
    if(rc != 0xFF){ //according to manual, all of the bits should be on at first
        return 0; //failed
    }

    //set the direction of each of the pins to the desired value
    for(int i = 0; i < 8; i++){
        set_dir(i, directions[i]);
    }

    return 1; //succeeded
}

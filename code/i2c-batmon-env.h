/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef I2C_BATMON_ENV_H
#define I2C_BATMON_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
#define ADCADDRESS 0b10010111

// global variables
uint8_t msb, lsb;

// func decs
uint16_t batSingleSample();
uint16_t batMultiSample(uint8_t);

uint16_t batSingleSample() {
    //
    uint16_t data = 0;
    
    i2cStart(); // send start bit
    i2cTXByte(ADCADDRESS); // transmit address byte
    msb = i2cRXByte(ACK); // receive first byte
    lsb = i2cRXByte(NACK); // receive second byte
    i2cStop(); // send stop bit
    
    
    // TODO: this doesnt work , idk if ^ does either
    data |= msb; // add ms4b to data
    data = data << 6; // shift data left 6 for ls6b
    data &= 0b111111; // clean ls6b of data
    lsb = lsb >> 2; // shift ls6b
    lsb &= 0b00111111; // clean ls6b
    data |= lsb; // add ls6b to data;
    
    return 2 * data;
}

uint16_t mpc3021MultiSample() {
    return 0;
}
#endif



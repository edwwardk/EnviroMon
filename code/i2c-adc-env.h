/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef I2C_ADCI2C_ENV_H
#define I2C_ADCI2C_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"
#include "i2c-env.h"

// constant defs
#define ADCADDRESS 0b10010110

// global variables


// func decs
uint16_t mcp3021SingleSample(uint8_t);
uint16_t mcp3021MultiSample(uint8_t);

uint16_t mcp3021SingleSample(uint8_t rw) {
    uint16_t word;
    
    i2cStart(); // send start bit
    i2cTXByte(ADCADDRESS + rw); // transmit address byte
    //word = i2cRXByte();
}

uint16_t mpc3021MultiSample() {
    
}
#endif



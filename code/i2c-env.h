/* 
 * i2ccfg.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef I2C_ENV_H
#define I2C_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs

// global variables


// func decs
void i2cInit();

void i2cStart();
void i2cStop();
void i2cRestart();

void i2cTXByte(uint8_t);
uint8_t i2cRXByte();

// initialize i2c module
void i2cInit() {
    _I2C1MD = 0; // enable i2c1 power
    I2C1CONbits.I2CEN = 0; // disable i2c1 module
    
    I2C1BRG = 9; // fscl = ~100kHz
    I2C1CONbits.DISSLW = 1; // TODO: check if needed
    I2C1STATbits.ACKSTAT = 1; // force ackstat high
    
    I2C1CONbits.I2CEN = 1; // enable i2c1 module
}

// send byte
void i2cTXByte(uint8_t buf) {
    I2C1TRN = buf; // write byte to buffer
    while (I2C1STATbits.TBF); // wait for write
    while (I2C1STATbits.TRSTAT); // wait for transmit
}

// receive byte
uint8_t i2cRXByte() {
    I2C1CONbits.RCEN = 1; // enable receive mode
    while (!I2C1STATbits.RBF); // wait for read
    while (I2C1CONbits.ACKEN); // wait for ack
    return I2C1RCV;
}

// send start bit
void i2cStart() {
    I2C1CONbits.SEN = 1; // set start bit
    while (I2C1CONbits.SEN); // wait for start bit clear
}

// send stop bit
void i2cStop() {
    I2C1CONbits.PEN = 1; // set stop bit
    while (I2C1CONbits.PEN); // wait for stop bit clear
}

// send restart bit
void i2cRestart() {
    I2C1CONbits.RSEN = 1; // set restart bit
    while (I2C1CONbits.RSEN); // wait for restart bit clear
}
#endif



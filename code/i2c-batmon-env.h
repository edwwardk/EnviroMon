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


// func decs
float battery_sample();

// sample battery voltage
float battery_sample() {
    uint8_t msb, lsb;
    uint16_t data = 0;
    
    i2c_start(); // send start bit
    i2c_tx_byte(ADCADDRESS); // transmit address byte
    msb = i2c_rx_byte(ACK); // receive first byte
    lsb = i2c_rx_byte(NACK); // receive second byte
    i2c_stop(); // send stop bit
    
    data = msb & 0x0F; // add msb to data
    data = (data << 6) | ((lsb & 0xFC) >> 2); // add msb to lsb
    
    return  ((data * 2.8) / 1024.0) * 2;
}
#endif



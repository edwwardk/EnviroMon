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
#define ADCADDRESS 0x97

// func decs
float battery_voltage();

// sample battery voltage
float battery_voltage() {
    uint8_t msb8, lsb8;
    uint16_t msb16 = 0, lsb16 = 0, adata = 0;
    
    i2c_start(); // send start bit
    i2c_tx_byte(ADCADDRESS); // transmit address byte
    msb8 = i2c_rx_byte(ACK); // receive first byte
    lsb8 = i2c_rx_byte(NACK); // receive second byte
    i2c_stop(); // send stop bit
    
    msb16 = (msb16 | msb8) << 6;
    lsb16 = (lsb16 | (lsb8 & 0xFC)) >> 2; 
    adata = msb16 | lsb16;
    
    return (((float)adata * (2.8/1024.0)) * 2.0) + 0.43;
}

#endif



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

#include <xc.h>

void i2cInit();

void i2cInit() {
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
}

#endif



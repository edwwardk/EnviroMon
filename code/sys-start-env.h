/* 
 * envcfg.h
 * written by edward kneller
 * 
 * configures startup sequence
 * 
 */

// include catch clause
#ifndef SYS_START_ENV_H
#define SYS_START_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// global variables
uint8_t startComplete = 0;

// func decs
void __startup();
void fastMode();
void slowMode();

// perform startup initializations
void __startup() {
    // only run once on startup
    if (startComplete) {
        return;
    }
    
    sysInit(); // init misc sys cfg
    pmdDisableAll(); // disable all peripheral modules
    intInit(); // init external interrupts
    adcInit(); // init adc module
    i2cInit(); // init i2c module
    
    // set start complete
    startComplete = 1;
}

// set fast mode
void fastMode() {
    // disable rtcc interrupt
    fast = 1; // enable fast mode bit
}

// set slow mode
void slowMode() {
    // enable rtcc interrupt
    fast = 0; // disable fast mode bit
}
#endif



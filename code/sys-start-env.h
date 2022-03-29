/* 
 * sys-start-env.h
 * written by edward kneller
 * 
 * determines startup sequence
 * runs once on reset/power on
 * 
 * 
 * ~~~ defines ~~~
 * 
 * 
 * ~~~ global variables ~~~
 * startComplete - tracks if startup has been performed
 * 
 * ~~~ functions ~~~
 * void __startup();
 * - performs startup routine
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

// perform startup initializations
void __startup() {
    // only run once on startup
    if (startComplete) {
        return;
    }
    
    // system inits
    sys_init(); // init misc sys cfg
    pmd_disable_all(); // disable all peripheral modules
    
    // module inits
    intInit(); // init external interrupts
    adcInit(); // init adc module
    i2c_init(); // init i2c module
    spi1Init(); // init spi1 module
    spi2Init(); // init spi2 module
    
    // device inits
    lora_init(); // init lora module
    
    
    startComplete = 1; // set start complete
    __delay_ms(100); // setup time
}

#endif



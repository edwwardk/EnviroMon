/* 
 * sys-run-env.h
 * written by edward kneller
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
    adcInit(); // init adc module
    i2c_init(); // init i2c module
    spi1Init(); // init spi1 module
    
    // device inits
    lora_init(); // init lora module
    
    // setup debug led D8 - RB3
    _TRISB3 = 0;
    _ODC3 = 0;
    
    // setup other debug led D12 - RA3
    _TRISA3 = 0;
    _ODA3 = 0;
    
    // configure external interrupts
    int_init(); // init external interrupts
    
    startComplete = 1; // set start complete
    __delay_ms(200); // setup time
}
#endif



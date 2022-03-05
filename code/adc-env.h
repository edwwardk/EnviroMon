/* 
 * adccfg.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef ADC_ENV_H
#define ADC_ENV_H

#include <xc.h>

void adcInit();

void adcInit() {
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
}


#endif



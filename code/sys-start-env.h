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

// func decs
void __startup();

// perform startup initializations
void __startup() {
    sysInit(); // init misc sys cfg
    pmdDisableAll(); // disable all peripheral modules
    intInit(); // init external interrupts
    adcInit(); // init adc module
}
#endif



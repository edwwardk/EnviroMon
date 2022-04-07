/* 
 * sys-intcfg-env.h
 * written by edward kneller
 * 
 */

// include catch clause
#ifndef SYS_INTCFG_ENV_H
#define SYS_INTCFG_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// func decs
void int_init();

// configure external interrupts
void int_init() {
    // clear states
    _RB7 = 0; // int0
    _RB13 = 0; // int1
    
    // set as inputs
    _TRISB7 = 1; // int0
    _TRISB13 = 1; // int1
    
    _PCFG11 = 1; // set int1 digital
    
    // pps
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    _INT1R = 13; // int1
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
    
    // positive edge triggered
    _INT0EP = 0; // int0
    _INT1EP = 0; // int1
    
    // clear interrupt flags
    _INT0IF = 0; // int0
    _INT1IF = 0; // int1
    
    // interrupt priorities
    _INT0IP = 7; // int0
    _INT1IP = 7; // int1
    
    // enable interrupts
    _INT0IE = 1; // int0
    _INT1IE = 1; // int1
}
#endif



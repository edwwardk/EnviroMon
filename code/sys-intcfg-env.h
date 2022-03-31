/* 
 * sys-intcfg-env.h
 * written by edward kneller
 * 
 * configures external interrupt inputs
 * 
 * INT0 uses pin43/rb7
 * INT1 uses pin11/rb13
 * 
 * 
 * ~~~ defines ~~~
 * 
 * 
 * ~~~ global variables ~~~
 * 
 * 
 * ~~~ functions ~~~
 * void intInit();
 * - initializes external INT0 and INT1
 * 
 */

// include catch clause
#ifndef SYS_INTCFG_ENV_H
#define SYS_INTCFG_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// func decs
void intInit();

// configure external interrupts
void intInit() {
    // pps
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    _INT1R = INT1; // int1
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
    
    // clear states
    _RB7 = 0; // int0
    _RB13 = 0; // int1
    
    // set as inputs
    _TRISB7 = 1; // int0
    _TRISB13 = 1; // int1
    
    _PCFG11 = 1; // set int1 digital
    
    // positive edge triggered
    _INT0EP = 0; // int0
    _INT1EP = 0; // int1
    
    // set both interrupts priority 1
    _INT0IP = 1; // int0
    _INT1IP = 1; // int1
    
    // clear interrupt flags
    _INT0IF = 0; // int0
    _INT1IF = 0; // int1
    
    // enable interrupts
    _INT0IE = 1; // int0
    _INT1IE = 1; // int1
}
#endif



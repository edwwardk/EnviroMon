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
    // clear states
    _RB7 = 0; // int0
    _RB13 = 0; // int1
    
    // set as inputs
    _TRISB7 = 1; // int0
    _TRISB13 = 1; // int1
    
    // positive edge triggered
    _INT0EP = 0; // int0
    _INT1EP = 0; // int1
    
    // clear interrupt flags
    _INT0IF = 0; // int0
    _INT1IF = 0; // int1
    
    // enable interrupts
    _INT0IE = 1; // int0
    _INT1IE = 1; // int1
}
#endif



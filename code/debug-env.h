/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef DEBUG_ENV_H
#define DEBUG_ENV_H

// ensure xc.h inclusion
#include <xc.h>

// other includes


// constant defs
#define DEBUG_EN PORTAbits.RA3

// func decs
void debugInit();
void debugEnable();
void debugDisable();

// initialize debug
void debugInit() {
    // clear states
    DEBUG_EN = 0;
    
    // pin directions
    TRISAbits.TRISA3 = 0; // output
    
    // open drain
    ODCAbits.ODA3 = 0; // non od
}

// enable debug mode
void debugEnable() {
    // set debug enable high
    DEBUG_EN = 1;
}

// disable debug mode
void debugDisable() {
    // set debug enable low
    DEBUG_EN = 0;
}
#endif



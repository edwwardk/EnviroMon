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

// ensure sys inclusions
#include <xc.h>
#include "sys-env.h"

// constant defs


// global variables


// func decs
void debugInit();
void debugEnable();
void debugDisable();

// initialize debug
void debugInit() {
    // clear states
    DBGEN = 0;
    
    // pin directions
    _TRISA3 = 0; // output
    
    // open drain
    _ODA3 = 0; // non od
}

// enable debug mode
void debugEnable() {
    // set debug enable high
    DBGEN = 1;
}

// disable debug mode
void debugDisable() {
    // set debug enable low
    DBGEN = 0;
}
#endif



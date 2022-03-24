/*
 * enviromon main code
 * written by edward kneller
 * 
 */

// includes
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
#define SHT30RHPIN AN5
#define SHT30TEMPPIN AN6

// global variables


// func decs


// main program
int main(void) {
    __startup(); // perform startup routine
                 // will only execute once on device reset
    
    _TRISB3 = 0;
    _ODC3 = 0;
    
    /*
    float vbat;
    while (1) {
    vbat = battery_sample();
    }
    */
    
    
    
    _RB3 = 1; // turn LED on
    while(1);
    return 0;
}
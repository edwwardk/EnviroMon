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

#define TXCYCLES 6
#define SLEEPMINUTES 10

// global variables


// func decs
void initTestLED();

// main program
int main(void) {
    __startup(); // perform startup routine
                 // will only execute once on device reset
    
    initTestLED();
    __delay_ms(2000);
    
    while (1) {
        if (fast) {
            // active monitoring state
            _RB3 = 1;
            
        } else {
            // logging monitoring state
            _RB3 = 0;
            
        }
        Sleep();
    }
    
    return 0;
}


void initTestLED() {
    _TRISB3 = 0;
    _ODC3 = 0;
}
/*
 * enviromon main code
 * written by edward kneller
 * 
 */

// includes
#include <xc.h>
#include "sys-cfg-env.h"

// main program
int main(void) {
    __startup(); // perform startup routine
                 // will only execute once on device reset
    
    // main loop
    while(1) {
        main_sequence();
        __delay_us(1);
    };
    
    return 0;
}
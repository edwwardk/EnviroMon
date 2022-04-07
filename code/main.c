/*
 * main.c
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
        main_sequence(); // only loop if in auto mode
        __delay_us(1);
        Sleep();
    };
    
    return 0;
}
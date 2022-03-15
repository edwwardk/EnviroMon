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
float hum, temp, vhum, vtemp, van1;

// func decs
void measTest();

// main program
int main(void) {
    __startup(); // perform startup routine
    
    
    // cfg test led
    _TRISB3 = 0; // rb3 output
    _ODB3 = 0; // non-od
    
    
    while (1) {
        van1 = adcMeasure(AN1);
        vhum = adcMeasure(AN5);
        hum = sht30RH(SHT30RHPIN);
        vtemp = adcMeasure(AN6);
        temp = sht30Temp(SHT30TEMPPIN);
        __delay_ms(100);
    }
    return 0;
}


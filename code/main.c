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
    
    uint8_t test;
    while (1) {
        test = spi1_read();
    }
     */
    
    uint8_t lora_data[10], loraid, i;
    
    while (1) {
        loraid = lora_read(0x42); // read hoperf id
        for (i = 0; i < 10; i++) {
            lora_data[i] = lora_read(i); // read address i
            __delay_us(10);
        }
    }
    
    _RB3 = 1; // turn LED on
    while(1);
    return 0;
}
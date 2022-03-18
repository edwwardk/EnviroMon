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
void testLora();

// main program
int main(void) {
    __startup(); // perform startup routine
                 // will only execute once on device reset
    
    initTestLED();
    testLora();
    __delay_ms(500);
    
    
    uint16_t vbat = batSingleSample();
    
    uint16_t loraData1 = loraRead(0x42);
    uint16_t loraData2 = loraRead(0x12);
    
    while (1) {
        if (fast) {
            // active monitoring state
            _RB3 = 1;
            
        } else {
            // logging monitoring state
            _RB3 = 0;
            
        }
    }
    return 0;
}


void initTestLED() {
    _TRISB3 = 0;
    _ODC3 = 0;
}

void testLora() {
    RFEN = 1; // enable rf regulator
    RFRST = 1; // keep reset high
}
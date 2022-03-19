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
    
    __delay_ms(100);
    
    uint8_t lora_data[10], i;
    
    for (i = 0; i < 10; i++) {
        lora_data[i] = lora_read(i);
    }
    
    float vbat = battery_sample();
    
    
    //uint16_t loraData1 = loraRead(0x42);
    //uint16_t loraData2 = loraRead(0x12);
    
    
    _RB3 = 1; // turn LED on
    while(1);
    return 0;
}


void initTestLED() {
    _TRISB3 = 0;
    _ODC3 = 0;
}
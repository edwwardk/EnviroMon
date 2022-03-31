/*
 * enviromon main code
 * written by edward kneller
 * 
 */

// includes
#include <xc.h>
#include "sys-cfg-env.h"

// func decs
void test_routine();

// main program
int main(void) {
    __startup(); // perform startup routine
                 // will only execute once on device reset
    
    // setup debug led; RB3
    _TRISB3 = 0;
    _ODC3 = 0;
    
    test_routine();
    
    // monitoring loop
    while(1) {
        // sample sensors
        // transmit samples
        // sleep
    }
    return 0;
}

void test_routine() {
    uint8_t t = 1, h = 2, b = 3;
    // check current time
    while (1) {
        lora_send(temperature, sizeof(temperature));
        lora_send(humidity, sizeof(humidity));
        lora_send(battery, sizeof(battery));
        
        
        temperature[sample_value] += t;
        humidity[sample_value] += h;
        battery[sample_value] -= b;
        
        
        if (temperature[sample_value] > 35) {
            temperature[sample_value] = 5;
        }
        
        if (humidity[sample_value] > 80) {
            humidity[sample_value] = 10;
        }
        
        if (battery[sample_value] < 10) {
            battery[sample_value] = 90;
        }
        
        __delay_ms(7500);
    }
}
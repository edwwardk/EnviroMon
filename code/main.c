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
uint8_t seconds, minutes, hours, days, months, years, controlreg;

// main program
int main(void) {
    __startup(); // perform startup routine
                 // will only execute once on device reset
    
    // setup debug led; RB3
    _TRISB3 = 0;
    _ODC3 = 0;
    
    uint8_t message[] = "test message";
    
    uint8_t temperature[12] = {
        0, // to - 0
        1, // from - 1
        2, // id - 2
        3, // flags - 3
        1, // sample id - 4
        22, // year - 5
        03, // month - 6
        29, // day - 7
        10, // hour - 8
        25, // minute - 9
        30, // second - 10
        25 // value - 11
    };
    
    uint8_t humidity[12] = {
        
    };
    
    uint8_t battery[12] = {
        
    };
    
    
    int i = 10;
    // check current time
    while (1) {
        lora_send(temperature, sizeof(temperature));
        i++;
        
        temperature[11] = i;
        
        if (i > 240) {
            i = 0;
        }
        
        /*
        for (i = 20; i < 75; i++) {
            temperature[11] = i;
            lora_send(temperature, sizeof(temperature));
            __delay_ms(500);
        }
        */
        
        
        
        
        /*
        seconds = rtc_time(SECONDS);
        minutes = rtc_time(MINUTES);
        hours = rtc_time(HOURS);
        days = rtc_time(DAYS);
        months = rtc_time(MONTHS);
        years = rtc_time(YEARS);
        controlreg = rtc_read_byte(CONTROL);
        */
        __delay_ms(1000);
    }
    
    while(1); // trap program
    return 0;
}
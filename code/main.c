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
    
    
    uint8_t hello[20] = "hello world!";
    uint8_t name[20] = "what is your name?";
    
    
    // check current time
    while (1) {
        lora_send(hello, sizeof(hello));
        lora_send(name, sizeof(name));
        
        
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
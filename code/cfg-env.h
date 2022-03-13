/* 
 * envcfg.h
 * written by edward kneller
 * 
 * configures all modules, control regs...
 * includes xc.h
 * 
 */

// include catch clause
#ifndef CFG_ENV_H
#define CFG_ENV_H

// ensure xc.h inclusion
#include <xc.h>

// other includes
#include "sys-env.h"
#include "adc-env.h"
#include "i2c-env.h"
#include "mem-env.h"
#include "rtcc-env.h"
#include "spi-env.h"
#include "usb-env.h"

// func decs
void __startup();
void intInit();

// perform startup initializations
void __startup() {
    pmdDisableAll(); // disable all peripheral modules
    intInit(); // init external interrupts
}

// configure external interrupts
void intInit() {
    // clear states
    PORTBbits.RB7 = 0; // int0
    PORTBbits.RB13 = 0; // int1
    
    // set as inputs
    TRISBbits.TRISB7 = 1; // int0
    TRISBbits.TRISB13 = 1; // int1
   
    // external interrupt pps
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    RPINR0bits.INT1R = 13; // map int1
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
    
    // positive edge triggered
    INTCON2bits.INT0EP = 0; // int0
    INTCON2bits.INT1EP = 0; // int1
    
    // clear interrupt flags
    IFS0bits.INT0IF = 0; // int0
    IFS1bits.INT1IF = 0; // int1
    
    // enable interrupts
    IEC0bits.INT0IE = 1; // int0
    IEC1bits.INT1IE = 1; // int1
}

// int0 isr
void __attribute__((__interrupt__, no_auto_psv)) _INT0Interrupt(void) {
    IFS0bits.INT0IF = 0; // reset int0 flag
}

// int1 isr
void __attribute__((__interrupt__, no_auto_psv)) _INT1Interrupt(void) {
    IFS1bits.INT1IF = 0; // reset int1 flag
}
#endif



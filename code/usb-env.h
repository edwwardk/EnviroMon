/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef USB_ENV_H
#define USB_ENV_H

// ensure xc.h inclusion
#include <xc.h>

// other includes


// constant defs
#define VBUS_DETECT PORTBbits.RB5

// func decs
void usbInit();

void usbInit() {
    // clear rb5 state, set as input
    VBUS_DETECT = 0;
    TRISBbits.TRISB5 = 1;
    
    // TODO: figure out when this is supposed to happen
    // enable usb1 power
    PMD4bits.USB1MD = 0;
    
    // disable usb1 module
    U1CONbits.USBEN = 0;
}

// usb1 module isr
void __attribute__((__interrupt__, no_auto_psv)) _USB1Interrupt(void) {
    // TODO: figure out what interrupt flags mean what
}
#endif



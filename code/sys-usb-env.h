/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef SYS_USB_ENV_H
#define SYS_USB_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
#define VBUS_DETECT PORTBbits.RB5

// global variables

// func decs
void usbInit();

// initialize usb module
void usbInit() {
    // clear rb5 state, set as input
    VBUS_DETECT = 0;
    _TRISB5 = 1;
    
    // TODO: figure out when this is supposed to happen
    // enable usb1 power
    _USB1MD = 0;
    
    // disable usb1 module
    _USBEN = 0;
}
#endif



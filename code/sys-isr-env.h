/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * isr header file, contains all interrupt routines
 * 
 */

// include catch clause
#ifndef SYS_ISR_ENV_H
#define SYS_ISR_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// int0 isr
void __attribute__((__interrupt__, no_auto_psv)) _INT0Interrupt(void) {
    _INT0IF = 0; // reset int0 flag
}

// int1 isr
void __attribute__((__interrupt__, no_auto_psv)) _INT1Interrupt(void) {
    _INT1IF = 0; // reset int1 flag
}

// rtcc isr
void __attribute__((__interrupt__, no_auto_psv)) _RTCCInterrupt(void) {
    _RTCIF = 0; // reset rtcc flag
    // peform wake routine
}

// usb1 module isr
void __attribute__((__interrupt__, no_auto_psv)) _USB1Interrupt(void) {
    // TODO: figure out what interrupt flags mean what
}
#endif



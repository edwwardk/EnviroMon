/* 
 * sys-isr-env.h
 * written by edward kneller
 * 
 * handles all interrupt services routines
 * centralized for easy access
 * 
 * 
 * ~~~ defines ~~~
 * 
 * 
 * ~~~ global variables ~~~
 * 
 * 
 * ~~~ functions ~~~
 * void _INT0Interrupt();
 * - isr for external INT0
 * 
 * void _INT1Interrupt();
 * - isr for external INT1
 * 
 * void _RTCCInterrupt();
 * - isr for RTCC alarm
 * 
 * void _USB1Interrupt();
 * - isr for USB interrupts
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
    RFEN = 0;
}

// int1 isr
void __attribute__((__interrupt__, no_auto_psv)) _INT1Interrupt(void) {
    _INT1IF = 0; // reset int1 flag
    RFEN = 1;
}

// rtcc isr
void __attribute__((__interrupt__, no_auto_psv)) _RTCCInterrupt(void) {
    _RTCIF = 0; // reset rtcc flag
    
    // peform wake routine
}

// usb1 module isr
void __attribute__((__interrupt__, no_auto_psv)) _USB1Interrupt(void) {
    _USB1IF = 0; // reset usb1 flag
    
    // TODO: figure out what interrupt flags mean what
}
#endif



/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * isr header file, contains all interrupt routines
 * 
 */

// include catch clause
#ifndef ISR_ENV_H
#define ISR_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-env.h"

// int0 isr
void __attribute__((__interrupt__, no_auto_psv)) _INT0Interrupt(void) {
    _INT0IF = 0; // reset int0 flag
}

// int1 isr
void __attribute__((__interrupt__, no_auto_psv)) _INT1Interrupt(void) {
    _INT1IF = 0; // reset int1 flag
}

// adc1 module isr
void __attribute__((__interrupt__, no_auto_psv)) _ADC1Interrupt(void) {
    _AD1IF = 0; // reset adc flag
}

// usb1 module isr
void __attribute__((__interrupt__, no_auto_psv)) _USB1Interrupt(void) {
    // TODO: figure out what interrupt flags mean what
}
#endif



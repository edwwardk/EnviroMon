/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <xc.h>

void usbInit();

void usbInit() {
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
}

#endif



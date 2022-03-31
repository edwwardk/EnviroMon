/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef SYS_RTCC_ENV_H
#define SYS_RTCC_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// func decs
void rtccInit();

// initialize rtcc module
void rtccInit() {
    PMD3bits.RTCCMD = 0; // enable rtcc power
    
    _RTCEN = 0; // disable rtcc module
    _RTCWREN = 1; // enable write to rtcc registers
    
    //_AMASK = 0b0001; // alarm every second
    _AMASK = 0b0010; // alarm every 10 seconds
    //_AMASK = 0b0011; // alarm every minute
    //_AMASK = 0b0100; // alarm every 10 minutes
    
    _CHIME = 1; // enable alarm rollover (repeat infinite)
    _ARPT = 3; // repeat a couple times at least
    
    _ALRMEN = 1; // enable rtcc alarm
    
    _RTSECSEL = 0b10; // source clock is lprc
    
    _RTCWREN = 0; // disable write to rtcc registers
    _RTCIF = 0; // clear rtcc flag
    _RTCIE = 1; // enable rtcc interrupt
    
    _RTCEN = 1; // enable rtcc module
}
#endif



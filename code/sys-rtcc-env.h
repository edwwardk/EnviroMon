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
void rtcc_init();

void rtcc_unlock();

// initialize rtcc module
void rtcc_init() {
    rtcc_unlock();
    
    _RTCEN = 0;
    
    _AMASK = 0b0010; // alarm every 10 seconds
    //_AMASK = 0b0011; // alarm every minute
    
    _ALRMEN = 1; // enable rtcc alarm
    _CHIME = 1; // enable alarm rollover (repeat infinite);
    
    _RTCEN = 1; // enable rtcc module
    
    //_RTCWREN = 0; // disable write to rtcc registers

    // configure interrupts
    _RTCIF = 0; // disable rtcc flag
    _RTCIP = 7; // set rtcc interrrupt priority
    _RTCIE = 1; // enable rtcc interrupt
}

// unlock rtcc write protected registers
void rtcc_unlock() {
    // save state of w1, w2, w3
    asm volatile("push w1");
    asm volatile("push w2");
    asm volatile("push w3");
    
    // perform unlock sequence
    asm volatile("disi #5");
    asm volatile("mov #NVMKEY, w1");
    asm volatile("mov #0x55, w2");
    asm volatile("mov w2, [w1]");
    asm volatile("mov #0xAA, w3");
    asm volatile("mov w3, [w1]");
    asm volatile("bset _RCFGCAL, #13"); // set RTCWREN bit
    
    // recover state
    asm volatile("pop w1");
    asm volatile("pop w2");
    asm volatile("pop w3");
}
#endif



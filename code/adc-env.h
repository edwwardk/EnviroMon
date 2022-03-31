/* 
 * adccfg.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef ADC_ENV_H
#define ADC_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
#define VREFP 2.048
#define VREFN 0

// analog inputs
// numbered left to right on header, starting with 3rd pin
#define AN1 0b01010 // AN10
#define AN2 0b01001 // AN9
#define AN3 0b00100 // AN4
#define AN4 0b00110 // AN6
#define AN5 0b00111 // AN7
#define AN6 0b01000 // AN8

// func decs
void adcInit();
float adcMeasure(uint8_t);
void vref_enable();
void vref_disable();

// initialize adc
void adcInit() {
    // cfg vref enable pin
    VREFEN = 0; // reset state
    _TRISA1 = 0; // set output
    
    _ADC1MD = 0; // enable adc power
    _ADON = 0; // disable adc module
    
    // set pins as inputs
    _TRISB14 = 1; // an10/rp14
    _TRISB15 = 1; // an9/rp15
    _TRISB2 = 1; // an4/rp2
    _TRISC0 = 1; // an6/rp16
    _TRISC1 = 1; // an7/rp17
    _TRISC2 = 1; // an8/rp18
    
    // set pins as analog
    _PCFG10 = 0; // an10
    _PCFG9 = 0; // an9
    _PCFG4 = 0; // an4
    _PCFG6 = 0; // an6
    _PCFG7 = 0; // an7
    _PCFG8 = 0; // an8
    
    // con1
    _FORM = 0; // integer output
    _SSRC = 0b111; // auto convert
    _ASAM = 0; // begin sample when SAMP set
    
    // con2
    _VCFG = 0b001; // v+ = vref; v- = avss
    _BUFM = 0; // one 16-word buffer
    _ALTS = 0; // always use muxa
    
    // con3
    _ADRC = 0; // clock from sys clock
    _SAMC = 0b00001; // 1Tad sample time
    _ADCS = 0; // tad = tcy
    
    // chs
    _CH0NA = 0; // mux a v- = vr-
    
    VREFEN = 1; // enable vref
    _ADON = 1; // enable adc module
    __delay_us(500); // vref settling time
}

// measure adc
float adcMeasure(uint8_t ch) {
    _CH0SA = ch; // select channel
    
    _SAMP = 1; // start sample
    __delay_us(1); // sample time
    while(!_DONE); // wait for conversion
    
    // return calced voltage
    return (ADC1BUF0 * ((VREFP - VREFN) / 1024.0));
}

// enable vref
void vref_enable() {
    VREFEN = 1;
    __delay_ms(1); // settling time
}

// disable vref
void vref_disable() {
    VREFEN = 0;
}
#endif



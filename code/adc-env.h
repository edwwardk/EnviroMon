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

// ensure xc.h inclusion
#include <xc.h>

// other includes


// constant defs


// func decs
void adcInit();
void adcEnable();
void adcDisable();

// initialize adc
void adcInit() {
    // enable adc power
    PMD1bits.ADC1MD = 0;
    
    // disable adc module
    AD1CON1bits.ADON = 0;
    
    // set pins as inputs
    TRISBbits.TRISB14 = 1; // an10/rp14
    TRISBbits.TRISB15 = 1; // an9/rp15
    TRISBbits.TRISB2 = 1; // an4/rp2
    TRISCbits.TRISC0 = 1; // an6/rp16
    TRISCbits.TRISC1 = 1; // an7/rp17
    TRISCbits.TRISC2 = 1; // an8/rp18
    
    // set pins as analog
    AD1PCFGLbits.PCFG10 = 1; //  an10
    AD1PCFGLbits.PCFG9 = 1; // an9
    AD1PCFGLbits.PCFG4 = 1; // an4
    AD1PCFGLbits.PCFG6 = 1; // an6
    AD1PCFGLbits.PCFG7 = 1; // an7
    AD1PCFGLbits.PCFG8 = 1; // an8
    
    // set vr+ to vref+, vr- to avss
    AD1CON2bits.VCFG = 0b001;
    
    // disable adc power
    PMD1bits.ADC1MD = 1;
}

void adcEnable() {
    // enable power
    PMD1bits.ADC1MD = 0;
    
    // enable module
    AD1CON1bits.ADON = 1;
}

void adcDisable() {
    // disable module
    AD1CON1bits.ADON = 0;
    
    // disable power
    PMD1bits.ADC1MD = 1;
}
#endif



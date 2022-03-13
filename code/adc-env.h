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
#define VREFP 2.048
#define VREFM 0
#define VREFEN PORTAbits.RA1

// analog inputs
// numbered left to right on header, starting with 3rd pin
#define APIN1 0b01010 // AN10
#define APIN2 0b01001 // AN9
#define APIN3 0b00100 // AN4
#define APIN4 0b00110 // AN6
#define APIN5 0b00111 // AN7
#define APIN6 0b01000 // AN8

// func decs
void adcInit();
void adcEnable();
void adcDisable();
void adcSample();
float adcMeasure(uint8_t);

// initialize adc
void adcInit() {
    // cfg vref enable pin
    VREFEN = 0;
    TRISAbits.TRISA1 = 0;
    
    PMD1bits.ADC1MD = 0; // enable adc power
    AD1CON1bits.ADON = 0; // disable adc module
    
    // set pins as inputs
    TRISBbits.TRISB14 = 1; // an10/rp14
    TRISBbits.TRISB15 = 1; // an9/rp15
    TRISBbits.TRISB2 = 1; // an4/rp2
    TRISCbits.TRISC0 = 1; // an6/rp16
    TRISCbits.TRISC1 = 1; // an7/rp17
    TRISCbits.TRISC2 = 1; // an8/rp18
    
    // set pins as analog
    AD1PCFGLbits.PCFG10 = 1; // an10
    AD1PCFGLbits.PCFG9 = 1; // an9
    AD1PCFGLbits.PCFG4 = 1; // an4
    AD1PCFGLbits.PCFG6 = 1; // an6
    AD1PCFGLbits.PCFG7 = 1; // an7
    AD1PCFGLbits.PCFG8 = 1; // an8
    
    // con1
    AD1CON1bits.FORM = 0; // integer output
    AD1CON1bits.SSRC = 0b111; // auto-convert trigger
    AD1CON1bits.ASAM = 1; // begin sample when SAMP set
    
    // con2
    AD1CON2bits.VCFG = 0b111; // set vr+ to vref+, vr- to avss
    AD1CON2bits.BUFM = 0; // one 16-word buffer
    AD1CON2bits.ALTS = 0; // always use muxa
    AD1CON2bits.CSCNA = 1;
    
    // con3
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 0b00001; // 1Tad sample time
    AD1CON3bits.ADCS = 0;
    
    // chs
    AD1CHSbits.CH0NA = 0; // mux a v- = vr-
}

// enables adc
void adcEnable() {
    VREFEN = 1; // enable vref
    AD1CON1bits.ADON = 1; // enable module
}

// disables adc
void adcDisable() {
    VREFEN = 0; // disable vref
    AD1CON1bits.ADON = 0; // disable module
}

// sample
void adcSample() {
    AD1CON1bits.SAMP = 1; // start sample
    while(!AD1CON1bits.DONE); // wait for conversion to finish
}

// measure adc
float adcMeasure(uint8_t ch) {
    //uint8_t i;
    //uint32_t sum;
    adcEnable(); // enable adc
    AD1CHSbits.CH0SA = ch; // select channel
    adcSample(); // take sample
    
    //for (i = 0; i < 16; i++) {
    //    sum += 1;
    //}
    return 0;
}
#endif



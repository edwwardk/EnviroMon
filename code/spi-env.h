/* 
 * spi-env.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef SPI_ENV_H
#define SPI_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs


// global variables


// func decs
void spi1Init();
void spi2Init();
void spiWrite(uint8_t, uint8_t);
uint8_t spiRead(uint8_t);

// init spi1 module (main/rf)
void spi1Init() {
    _SPI1MD = 0; // enable spi1 power
    SPI1STATbits.SPIEN = 0; // disable spi1 module
    
    // pin directions
    _TRISC5 = 1; // MISO input
    _TRISC4 = 0; // MOSI output
    _TRISC3 = 0; // SCLK output
    
    // open drain
    _ODC5 = 0; // MISO non od
    _ODC4 = 0; // MOSI non od
    _ODC3 = 0; // SCLK non od
    
    _PCFG12 = 1; // set SCLK digital
    
    SPI1CON1bits.MSTEN = 1; // enable master mode
    SPI1CON1bits.CKP = 0; // clock idle low
    SPI1CON1bits.SMP = 0; // sample in middle
    SPI1CON1bits.CKE = 1; // data changes on falling edge
    
    // set spi freq to 1MHz
    SPI1CON1bits.SPRE = 0b111; // 1:1 secondary prescale
    SPI1CON1bits.PPRE = 0b10; // 4:1 primary prescale
    
    SPI1STATbits.SPIEN = 1; // enable spi1 module
}

// init spi2 module (memory))
void spi2Init() {
    _SPI2MD = 0; // enable spi2 power
    SPI2STATbits.SPIEN = 0; // disable spi module
    
    // pin directions
    _TRISC6 = 1; // MEMDI input
    _TRISC8 = 0; // MEMDO output
    _TRISC9 = 0; // MEMCLK output
    _TRISC7 = 0; // MEMCS output
    
    // open drain
    _ODC6 = 0; // MEMDI non od
    _ODC8 = 0; // MEMDO non od
    _ODC9 = 0; // MEMCLK non od
    _ODC7 = 0; // MEMCS non od
    
    SPI2STATbits.SPIEN = 1; // enable spi2 module
}

// write a byte
void spiWrite(uint8_t bus, uint8_t data) {
    if (bus == 1) {
        while (SPI1STATbits.SPITBF); // wait for tx to start
        SPI1BUF = data; // write data to buffer
    } else if (bus == 2) {
        while (SPI2STATbits.SPITBF); // wait for tx to start
        SPI2BUF = data; // write data to buffer
    }
}

// read a byte
uint8_t spiRead(uint8_t bus) {
    if (bus == 1) {
        while (!SPI1STATbits.SPIRBF); // wait for rx full
        return SPI1BUF; // return buffer
    } else if (bus == 2) {
        while (!SPI2STATbits.SPIRBF); // wait for rx full
        return SPI2BUF; // return buffer
    }
    return 0;
}
#endif



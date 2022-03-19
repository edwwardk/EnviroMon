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
void spi1_write(uint8_t);
uint8_t spi1_read();

// init spi1 module (main/rf)
void spi1Init() {
    _SPI1MD = 0; // enable spi1 power
    SPI1STATbits.SPIEN = 0; // disable spi1 module
    
    // pps
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    // inputs
    _SDI1R = MISO; // miso
    _SDI2R = MEMDI; // memdi
    
    // outputs
    MOSI = _RPOUT_SDO1; // mosi
    SCLK = _RPOUT_SCK1OUT; // sclk
    MEMDO = _RPOUT_SDO2; //  memdo
    MEMCLK = _RPOUT_SCK2OUT; // memclk
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
    
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
    SPI1STATbits.SPIROV = 0; // clear overflow
    
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
void spi1_write(uint8_t data) {
    //__delay_us(10);
    SPI1BUF = data; // write data to buffer
    while (SPI1STATbits.SPITBF); // wait for tx to start
}

// read a byte
uint8_t spi1_read() {
    //__delay_us(10);
    //SPI1BUF = 0x00; // initiate bus cycle
    while (!SPI1STATbits.SPIRBF); // wait for rx full
    return SPI1BUF;// & 0xFF; // return buffer
}
#endif



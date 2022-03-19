/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef SPI_LORA_ENV_H
#define SPI_LORA_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
#define LORAWRITE 0x80
#define LORAREAD 0x7F

// global variables


// func decs
void lora_init();
void loraWrite(uint8_t);
uint8_t loraRead(uint8_t, uint8_t);

// initialize lora module
void lora_init() {
    // set pins output
    _TRISA8 = 0; // RFEN
    _TRISB4 = 0; // RFRST
    _TRISA4 = 0; // RFINT
    _TRISA9 = 0; // RFCS
    
    // set pins non-od
    _ODA8 = 0; // RFEN
    _ODB4 = 0; // RFRST
    _ODA4 = 0; // RFINT
    _ODA9 = 0; // RFCS
    
    // set states
    RFEN = 1; // enable rf regulator
    RFRST = 1; // hold rf reset high
}

// write bytes to lora module
void lora_write(uint8_t address, uint8_t data) {
    address = address | 0x80; // set msb to 1 for write
    
    RFCS = 0; // select chip
    __delay_us(1);
    spi1_write(address); // write address
    spi1_write(data); // write all data bytes
    RFCS = 1; // deselect chip
}

// read byte from lora module
uint8_t lora_read(uint8_t address) {
    uint8_t data; // buffer
    
    address = address & 0x7F; // set msb to 0 for read
    
    RFCS = 0; // select chip
    __delay_us(1);
    spi1_write(address); // write address
    data = spi1_read();
    RFCS = 1; // deselect chip
    return data;
}
#endif



/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures eeprom
 * uses spi2 module
 * contains eeprom operation functions
 * 
 * includes xc.h
 * 
 */

// include catch clause
#ifndef SPI_MEM_ENV_H
#define SPI_MEM_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
#define _SPI2EN SPI2STATbits.SPIEN

#define READ 0x03
#define WRITE 0x02
#define WREN 0x06
#define WRDI 0x04
#define RDSR 0x05
#define WRSR 0x01

// global variables


// func decs
void memInit();
//uint memRead();
void memWrite();

// initialize memory
void memInit() {
    // enable spi2 power
    _SPI2MD = 0;
    
    // disable spi module
    _SPI2EN = 0;
    
    // pin dirs
    _TRISC6 = 1; // MEMDI input
    _TRISC8 = 0; // MEMDO output
    _TRISC9 = 0; // MEMCLK output
    _TRISC7 = 0; // MEMCS output
    
    // open drain
    _ODC6 = 0; // MEMDI non od
    _ODC8 = 0; // MEMDO non od
    _ODC9 = 0; // MEMCLK non od
    _ODC7 = 0; // MEMCS non od
    
    // disable spi2 power
    _SPI2MD = 1;
}
#endif



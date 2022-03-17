/* 
 * spicfg.h
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
#define _SPI1EN SPI1STATbits.SPIEN

// global variables


// func decs
void spiInit();

void spiInit() {
    _SPI1MD = 0; // enable spi1 power
    _SPI1EN = 0; // disable spi1 module
    
    
    
    _SPI1EN = 1; // enable spi1 module
}
#endif



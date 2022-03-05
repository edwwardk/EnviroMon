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

#include <xc.h>

void spiInit();

void spiInit() {
    SPI1STATbits.SPIEN = 0; // disable spi module
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    
    
    
    
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
    SPI1STATbits.SPIEN = 0; // disable spi module
}


#endif



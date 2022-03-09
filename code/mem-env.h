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
#ifndef MEM_ENV_H
#define MEM_ENV_H

// ensure xc.h inclusion
#include <xc.h>

// other includes


// constant defs
// instructions
#define READ 0x03
#define WRITE 0x02
#define WREN 0x06
#define WRDI 0x04
#define RDSR 0x05
#define WRSR 0x01

// pins
#define MEM_MISO_PIN 22 // MEMDI
#define MEM_CS_PIN PORTCbits.RC7; // MEMCS

// io sources
#define SDI2 RPINR22bits.SDI2R
#define SDO2 10
#define SCK2OUT 11


// func decs
void memInit();
//uint memRead();
void memWrite();


// initialize memory
void memInit() {
    // enable spi2 power
    PMD1bits.SPI2MD = 0;
    
    // disable spi module
    SPI2STATbits.SPIEN = 0;
    
    // pin dirs
    TRISCbits.TRISC6 = 1; // MEMDI input
    TRISCbits.TRISC8 = 0; // MEMDO output
    TRISCbits.TRISC9 = 0; // MEMCLK output
    TRISCbits.TRISC7 = 0; // MEMCS output
    
    // open drain
    ODCCbits.ODC6 = 0; // MEMDI non od
    ODCCbits.ODC6 = 0; // MEMDO non od
    ODCCbits.ODC6 = 0; // MEMCLK non od
    ODCCbits.ODC6 = 0; // MEMCS non od
    
    // configure pps
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock pps
    SDI2 = MEM_MISO_PIN; // map sdi2 to MEMDI
    RPOR12bits.RP24R = SDO2; // map MEMDO to sdo2
    RPOR12bits.RP25R = SCK2OUT; // map MEMCLK to sck2out
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock pps
    
    // disable spi2 power
    PMD1bits.SPI2MD = 1;
}
#endif



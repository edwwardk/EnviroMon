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
#define LORABUS 1
#define LORAWRITE 0x80
#define LORAREAD 0x7F

// global variables


// func decs
void loraWrite(uint8_t, uint8_t[]);
uint8_t loraRead(uint8_t);

// write bytes to lora module
void loraWrite(uint8_t address, uint8_t data[]) {
    uint8_t i; // index variable
    
    address |= LORAWRITE; // set msb to 1 for write
    
    RFCS = 0; // select chip
    spiWrite(LORABUS, address); // write address
    for (i = 0; i < sizeof(data); i++) {
        spiWrite(LORABUS, data[i]); // write all data bytes
    }
    RFCS = 1; // deselect chip
}

// read byte from lora module
uint8_t loraRead(uint8_t address) {
    uint8_t data; // buffer
    
    address &= LORAREAD; // set msb to 0 for read
    
    RFCS = 0; // select chip
    spiWrite(LORABUS, address); // write address
    data = spiRead(LORABUS);
    RFCS = 1; // deselect chip
    return data;
}
#endif



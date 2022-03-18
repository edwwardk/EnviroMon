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
// eeprom functions
#define READ 0x03
#define WRITE 0x02
#define WREN 0x06
#define WRDI 0x04
#define RDSR 0x05
#define WRSR 0x01


// global variables


// func decs

#endif



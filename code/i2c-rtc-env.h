/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef I2C_RTC_ENV_H
#define I2C_RTC_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
#define RTCWRITE 0xDE // write operation
#define RTCREAD 0xDF // read operation

#define CONTROL 0x07 // control register
#define OSCTRIM 0x09 // oscillator trim register

// time registers
#define SECOND 0x00
#define MINUTE 0x01
#define HOUR 0x02
#define DAY 0x04
#define MONTH 0x05
#define YEAR 0x06

// global variables


// func decs
void rtc_write_byte(uint8_t, uint8_t);
uint8_t rtc_read_byte(uint8_t);

uint8_t rtc_time(uint8_t);

// write byte to rtc sram
void rtc_write_byte(uint8_t address, uint8_t data) {
    i2c_start(); // send start bit
    i2c_tx_byte(RTCWRITE); // write command
    i2c_tx_byte(address); // write mem address
    i2c_tx_byte(data); // write data
    i2c_stop(); // send stop bit
}

uint8_t rtc_read_byte(uint8_t address) {
    uint8_t data; // buffer
    
    i2c_start(); // send start bit
    i2c_tx_byte(RTCWRITE); // read command
    i2c_tx_byte(address); // write address
    i2c_start(); // send restart
    i2c_tx_byte(RTCREAD); // send read command
    data = i2c_rx_byte(NACK); // rx byte with nack
    i2c_stop(); // send stop bit
    
    return data;
}

// outputs selected time as binary coded byte
uint8_t rtc_time(uint8_t time) {
    uint8_t data = rtc_read_byte(time);
    
    // format time output
    switch (time) {
        case SECOND:
            data = data & 0x7F; // mask b7
            break;
        case MINUTE:
            data = data & 0x7F; // mask b7
            break;
        case HOUR:
            data = data & 0x3F; // mask b7-b6
            break;
        case DAY:
            data = data & 0x3F; // mask b7-b6
            break;
        case MONTH:
            data = data & 0x1F; // mask b7-b5
            break;
        case YEAR:
            data = data; // no mask
            break;
    }
    
    return data;
}
#endif



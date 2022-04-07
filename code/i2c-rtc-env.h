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
#define SECONDS 0x00
#define MINUTES 0x01
#define HOURS 0x02
#define WEEKDAYS 0x03
#define DAYS 0x04
#define MONTHS 0x05
#define YEARS 0x06

// alarm 0 registers
#define ALM0SEC 0x0A
#define ALM0MIN 0x0B
#define ALM0HOUR 0x0C
#define ALM0WKDAY 0x0D
#define ALM0DATE 0x0E
#define ALM0MTH 0x0F

// global variables


// func decs
void rtc_write_byte(uint8_t, uint8_t);
uint8_t rtc_read_byte(uint8_t);

uint8_t rtc_time(uint8_t);
void rtc_set_time(void);

void rtc_alarm_min();

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
        case SECONDS:
            data = data & 0x7F; // mask b7
            break;
        case MINUTES:
            data = data & 0x7F; // mask b7
            break;
        case HOURS:
            data = data & 0x3F; // mask b7-b6
            break;
        case DAYS:
            data = data & 0x3F; // mask b7-b6
            break;
        case MONTHS:
            data = data & 0x1F; // mask b7-b5
            break;
        case YEARS:
            data = data; // no mask
            break;
    }
    
    return data;
}

// write time to rtc
void rtc_set_time(void) {
    rtc_write_byte(SECONDS, 0); // stop oscillator
    
    rtc_write_byte(MINUTES, 0x05); // write mintues
    rtc_write_byte(HOURS, 0b00001001); // write hours
    rtc_write_byte(WEEKDAYS, 0b00101010); // write weekdays
    rtc_write_byte(DAYS, 0x28); // write days
    rtc_write_byte(MONTHS, 0x03); // write months
    rtc_write_byte(YEARS, 0x22); // write years
    
    rtc_write_byte(SECONDS, 0b10000000); // start time at 0 sec
}

void rtc_alarm_min() {
    rtc_write_byte(SECONDS, 0); // stop oscillator
    
    rtc_write_byte(CONTROL, 0b00011000); // enable alarm0
    rtc_write_byte(ALM0WKDAY, 0b00000000); // cfg alarm0
    rtc_write_byte(ALM0SEC, 0); // alarm on 0 sec
    // clears alarm flag, sets alarm polarity, sets mask
    // alarm will pull mfp low on seconds match
    
    rtc_write_byte(SECONDS, 0b1000000); // start oscillator
}

void rtc_clear_alm0() {
    uint8_t data = rtc_read_byte(ALM0WKDAY);
    data = data & 0x08;
    
    rtc_write_byte(ALM0WKDAY, data);
}
#endif



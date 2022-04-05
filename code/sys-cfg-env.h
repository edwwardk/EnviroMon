/* 
 * sys-cfg-env.h
 * written by edward kneller
 * 
 */

// include catch clause
#ifndef SYS_CFG_ENV_H
#define SYS_CFG_ENV_H

// CONFIG4
#pragma config DSWDTPS = DSWDTPSA       // DSWDT Postscale Select (1:2,097,152 (36 minutes))
#pragma config DSWDTOSC = LPRC          // Deep Sleep Watchdog Timer Oscillator Select (DSWDT uses Low Power RC Oscillator (LPRC))
#pragma config RTCOSC = LPRC            // RTCC Reference Oscillator Select (RTCC uses Low Power RC Oscillator (LPRC))
#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (BOR disabled in Deep Sleep)
#pragma config DSWDTEN = OFF            // Deep Sleep Watchdog Timer (DSWDT disabled)

// CONFIG3
#pragma config WPFP = WPFP63            // Write Protection Flash Page Segment Boundary (Highest Page (same as page 42))
#pragma config SOSCSEL = IO             // Secondary Oscillator Pin Mode Select (SOSC pins have digital I/O functions (RA4, RB4))
#pragma config WUTSEL = FST             // Voltage Regulator Wake-up Time Select (Fast regulator start-up time used)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Segmented code protection disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Last page and Flash Configuration words are unprotected)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary Oscillator disabled)
#pragma config I2C1SEL = PRI            // I2C1 Pin Select bit (Use default SCL1/SDA1 pins for I2C1 )
#pragma config IOL1WAY = OFF            // IOLOCK One-Way Set Enable (The IOLOCK bit can be set and cleared using the unlock sequence)
#pragma config OSCIOFNC = ON            // OSCO Pin Configuration (OSCO pin functions as port I/O (RA3))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor (Sw Disabled, Mon Disabled)
#pragma config FNOSC = FRC              // Initial Oscillator Select (Fast RC Oscillator (FRC))
#pragma config PLL96MHZ = ON            // 96MHz PLL Startup Select (96 MHz PLL Startup is enabled automatically on start-up)
#pragma config PLLDIV = DIV12           // USB 96 MHz PLL Prescaler Select (Oscillator input divided by 12 (48 MHz input))
#pragma config IESO = ON                // Internal External Switchover (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS8192           // Watchdog Timer Postscaler (1:8,192)
#pragma config FWPSA = PR32             // WDT Prescaler (Prescaler ratio of 1:32)
#pragma config WINDIS = OFF             // Windowed WDT (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = ON             // Watchdog Timer (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config GWRP = OFF               // General Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

// fcyc define
#define FCY 4000000 // fcy = fosc/2

// system includes
#include <xc.h>
#include <p24fj64gb004.h>
#include <libpic30.h>
#include <stdio.h>
#include <stdlib.h>

// constant defs
// pps inputs
#define INT1 13 // pin 11 - rp13
#define MISO 21 // pin 38 - rp21
#define MEMDI 22 // pin 2 -  rp22

// pps outputs
#define MOSI _RP20R // pin 37 - rp20
#define SCLK _RP19R // pin 36 - rp19
#define MEMDO _RP24R // pin 4 - rp24
#define MEMCLK _RP25R // pin 5 - rp25

// port pins
#define MEMCS _RC7 // pin 3 - rc7
#define VREFEN _RA1 // pin 20 - ra1
#define RFEN _RA8 // pin 32 - ra8
#define RFRST _RB4 // pin 33 - rb4
#define RFCS _RA9 // pin 35 - ra9
#define MEMWP _RA10 // pin 12 - ra10
#define MEMHOLD _RA7 // pin 13 - ra7
#define RTCMF _RA2 // pin 30 - ra2
#define DBGEN _RA3 // pin 31 - ra3

// values
#define VDDVAL 2.8 // system vdd

// global variables
enum {
    auto_mode,
    manual_mode
};
uint8_t run_mode = auto_mode;

// func decs
void sys_init();
void pmd_disable_all();

// initialize misc system cfgs
void sys_init() {
    _NSTDIS = 1; // disable interrupt nesting
}

// disable all modules
void pmd_disable_all() {
    // disable all timers
    _T5MD = 1;
    _T4MD = 1;
    _T3MD = 1;
    _T2MD = 1;
    _T1MD = 1;
    
    // disable both i2c
    _I2C1MD = 1;
    _I2C2MD = 1;
    
    // disable both uart
    _U2MD = 1;
    _U1MD = 1;
    
    // disable both spi
    _SPI2MD = 1;
    _SPI1MD = 1;
    
    // disable adc
    _ADC1MD = 1;
    
    // disable all input capture
    _IC5MD = 1;
    _IC4MD = 1;
    _IC3MD = 1;
    _IC2MD = 1;
    _IC1MD = 1;
    
    // disable all output compare
    _OC5MD = 1;
    _OC4MD = 1;
    _OC3MD = 1;
    _OC2MD = 1;
    _OC1MD = 1;
    
    // disable cmp
    // triple comparator i think
    _CMPMD = 1;
    
    // enable rtcc
    _RTCCMD = 0;
    
    // disable pmp
    _PMPMD = 1;
    
    // disable crc
    _CRCMD = 1;
    
    // disable upwm
    // potentially pwm module?
    _UPWMMD = 1;
    
    // disable refo
    // reference clock output
    _REFOMD = 1;
    
    // disable ctmu
    // charge time measurement unit
    _CTMUMD = 1;
    
    // disable lvd
    // low voltage detection
    _LVDMD = 1;
    
    // disable usb
    _USB1MD = 1;
}

// protocol includes
#include "i2c-env.h"
#include "spi-env.h"

// module includes
#include "adc-env.h"
#include "sys-rtcc-env.h"
#include "sys-intcfg-env.h"

// device specific includes
#include "i2c-rtc-env.h"
#include "i2c-batmon-env.h"
#include "spi-lora-env.h"
#include "spi-mem-env.h"

// startup sequence
#include "sys-run-env.h"

// operation sequences
#include "sample-env.h"

// isrs includes
#include "sys-isr-env.h"

#endif
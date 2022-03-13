/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef SYS_ENV_H
#define SYS_ENV_H

// CONFIG4
#pragma config DSWDTPS = DSWDTPSA       // DSWDT Postscale Select (1:2,097,152 (36 minutes))
#pragma config DSWDTOSC = LPRC          // Deep Sleep Watchdog Timer Oscillator Select (DSWDT uses Low Power RC Oscillator (LPRC))
#pragma config RTCOSC = LPRC            // RTCC Reference Oscillator Select (RTCC uses Low Power RC Oscillator (LPRC))
#pragma config DSBOREN = OFF            // Deep Sleep BOR Enable bit (BOR disabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer (DSWDT enabled)

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
#pragma config FCKSM = CSECME           // Clock Switching and Fail-Safe Clock Monitor (Sw Enabled, Mon Enabled)
#pragma config FNOSC = FRCDIV           // Initial Oscillator Select (Fast RC Oscillator with Postscaler (FRCDIV))
#pragma config PLL96MHZ = OFF           // 96MHz PLL Startup Select (96 MHz PLL Startup is enabled by user in software( controlled with the PLLEN bit))
#pragma config PLLDIV = DIV12           // USB 96 MHz PLL Prescaler Select (Oscillator input divided by 12 (48 MHz input))
#pragma config IESO = ON                // Internal External Switchover (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = OFF             // Windowed WDT (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config GWRP = OFF               // General Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = ON              // JTAG Port Enable (JTAG port is enabled)

// ensure xc.h inclusion
#include <xc.h>

// fcyc define
#define FCY 4000000

// other includes
#include <libpic30.h>
#include <stdio.h>

// constant defs


// func decs
void pmdDisableAll();

// disable all modules
void pmdDisableAll() {
    // disable all timers
    PMD1bits.T5MD = 1;
    PMD1bits.T4MD = 1;
    PMD1bits.T3MD = 1;
    PMD1bits.T2MD = 1;
    PMD1bits.T1MD = 1;
    
    // disable both i2c
    PMD1bits.I2C1MD = 1;
    PMD3bits.I2C2MD = 1;
    
    // disable both uart
    PMD1bits.U2MD = 1;
    PMD1bits.U1MD = 1;
    
    // disable both spi
    PMD1bits.SPI2MD = 1;
    PMD1bits.SPI1MD = 1;
    
    // disable adc
    PMD1bits.ADC1MD = 1;
    
    // disable all input capture
    PMD2bits.IC5MD = 1;
    PMD2bits.IC4MD = 1;
    PMD2bits.IC3MD = 1;
    PMD2bits.IC2MD = 1;
    PMD2bits.IC1MD = 1;
    
    // disable all output compare
    PMD2bits.OC5MD = 1;
    PMD2bits.OC4MD = 1;
    PMD2bits.OC3MD = 1;
    PMD2bits.OC2MD = 1;
    PMD2bits.OC1MD = 1;
    
    // disable cmp
    // triple comparator i think
    PMD3bits.CMPMD = 1;
    
    // disable rtcc
    PMD3bits.RTCCMD = 1;
    
    // disable pmp
    // parallel master port
    PMD3bits.PMPMD = 1;
    
    // disable crc
    PMD3bits.CRCMD = 1;
    
    // disable upwm
    // potentially pwm module?
    PMD4bits.UPWMMD = 1;
    
    // disable refo
    // reference clock output
    PMD4bits.REFOMD = 1;
    
    // disable ctmu
    // charge time measurement unit
    PMD4bits.CTMUMD = 1;
    
    // disable lvd
    // low voltage detection
    PMD4bits.LVDMD = 1;
    
    // disable usb
    PMD4bits.USB1MD = 1;
}
#endif



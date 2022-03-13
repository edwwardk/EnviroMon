/* 
 * TEMPLATE.h
 * written by edward kneller
 * 
 * configures pps, control regs, initial states
 * includes xc.h
 * 
 */

// include catch clause
#ifndef SHT30_ENV_H
#define SHT30_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-env.h"

// constant defs

// global variables


// func decs
float sht30RH(uint8_t);
float sht30Temp(uint8_t);

// read %relative humidity
float sht30RH(uint8_t pin) {
    return (-12.5 + (125 * (adcMeasure(pin) / VDDVAL)));
}

// read degC temperature
float sht30Temp(uint8_t pin) {
     return (-66.875 + (218.75 * (adcMeasure(pin) / VDDVAL)));
}
#endif



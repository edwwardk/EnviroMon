/* 
 * template.h
 * written by edward kneller
 * 
 * template description
 * 
 * 
 * ~~~ defines ~~~
 * 
 * 
 * ~~~ global variables ~~~
 * 
 * 
 * ~~~ functions ~~~
 */

// include catch clause
#ifndef SAMPLE_ENV_H
#define SAMPLE_ENV_H

// ensure sys inclusions
#include <xc.h>
#include "sys-cfg-env.h"

// constant defs
#define SHT30RHPIN AN5
#define SHT30TEMPPIN AN6

// sample array indices
enum {
    sample_id,
    sample_value,
    sample_length
};

// sample ids
enum {
    temperature_id = 1,
    humidity_id,
    battery_id
};

// sample holding arrays
uint8_t temperature[sample_length] = {temperature_id};
uint8_t humidity[sample_length] = {humidity_id};
uint8_t battery[sample_length] = {battery_id};

// func decs
void sample_all();
void sample_transmit();
float sht30_humidity(uint8_t);
float sht30_temperature(uint8_t);


// sample temperature, humidity, battery
void sample_all() {
    // TODO: figure out how to transmit floats
}

// transmit all samples
void sample_transmit() {
    
}

// read %relative humidity
float sht30_humidity(uint8_t pin) {
    return (-12.5 + (125 * (adcMeasure(pin) / VDDVAL)));
}

// read degC temperature
float sht30_temperature(uint8_t pin) {
     return (-66.875 + (218.75 * (adcMeasure(pin) / VDDVAL)));
}

#endif



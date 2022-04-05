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

#define SAMPLELENGTH 5

// sample array indices
enum {
    sample_id,
    sample_value,
};

// sample ids
enum {
    temperature_id = 1,
    humidity_id,
    battery_id
};

// sample holding arrays
uint8_t temperature[SAMPLELENGTH] = {temperature_id};
uint8_t humidity[SAMPLELENGTH] = {humidity_id};
uint8_t battery[SAMPLELENGTH] = {battery_id};

// conversion unions
union {
    float ufloat;
    uint8_t ubytes[4];
} union_temperature, union_humidity, union_battery;

// func decs
void main_sequence();
void sample_all();
void sample_transmit();
float sht30_humidity(uint8_t);
float sht30_temperature(uint8_t);

// perform main operation sequence
void main_sequence() {
    vref_enable(); // enable vref
    sample_all(); // sample sensors
    vref_disable(); // disable vref
    sample_transmit(); // transmit samples
    
    // flash led
    _RB3 = 1;
    __delay_us(5);
    _RB3 = 0;
    
    Sleep(); // go to sleep
}

// sample temperature, humidity, battery
void sample_all() {
    union_temperature.ufloat = sht30_temperature(SHT30TEMPPIN);
    union_humidity.ufloat = sht30_humidity(SHT30RHPIN);
    union_battery.ufloat = battery_voltage();
    
    uint8_t i;
    for (i = 0; i < sizeof(union_temperature.ubytes); i ++) {
        temperature[i+1] = union_temperature.ubytes[i];
        humidity[i+1] = union_humidity.ubytes[i];
        battery[i+1] = union_battery.ubytes[i];
    }
}

// transmit all samples
void sample_transmit() {
    lora_send(temperature, SAMPLELENGTH);
    lora_send(humidity, SAMPLELENGTH);
    lora_send(battery, SAMPLELENGTH);
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



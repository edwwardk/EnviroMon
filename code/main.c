/*
 * enviromon main code
 * written by edward kneller
 * 
 */

// includes
#include "cfg-env.h"


#include "adc-env.h"

int main(void) {
    __startup(); // init all modules, pps
    
    TRISBbits.TRISB3 = 0;
    ODCBbits.ODB3 = 0;
    
    vrefInit();
    VREFEN = 1;
    
    while (1);
    return 0;
}
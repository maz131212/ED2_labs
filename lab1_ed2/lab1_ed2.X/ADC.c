/*
 * File:   ADC.c
 * Author: axelmazariegos
 *
 * Created on July 16, 2021, 5:17 PM
 */

#include <stdint.h>
#include <xc.h>

uint8_t readADC(void) {
    
    uint8_t val = ADRESH;
    PIR1bits.ADIF = 0;
    
    return val;
}

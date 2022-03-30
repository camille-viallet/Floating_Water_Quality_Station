#ifndef TURBIDITY_H
#define TURBIDITY_H

#include <stdio.h>
#include <math.h>

#include "ztimer.h"
#include "periph/adc.h"

#define RES ADC_RES_12BIT

/**
 * The turbidity sensor need to be connected on the A4 pin on the Lora-E5 mini
 **/

int turbidityInit(void);
float getTurbidity(void);
void printTurbidity(double turbidity);

#endif /*TURBIDITY_H*/
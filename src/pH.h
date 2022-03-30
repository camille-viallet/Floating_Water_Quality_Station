#ifndef PH_H
#define PH_H

#include <stdio.h>
#include <math.h>

#include "ztimer.h"
#include "periph/adc.h"

#define RES ADC_RES_12BIT

/**
 * The pH sensor need to be connected on the A3 pin on the Lora-E5 mini
 **/

int pHInit(void);
float getpH(void);
void printpH(double pH);

#endif /*PH_H*/
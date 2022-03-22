#ifndef PH_H
#define PH_H

#include <stdio.h>
#include <math.h>

#include "ztimer.h"
#include "periph/adc.h"

#define RES ADC_RES_10BIT

/**
 * The pH sensor need to be connected on the A3 pin on the Lora-E5 mini
 **/

int pHInit(void);
double getpH(void);

#endif /*PH_H*/
#ifndef SENSORS_H
#define SENSORS_H

#include "cayenne_lpp.h"

#include "ds18.h"
#include "ds18_params.h"

#include "turbidity.h"
#include "pH.h"

#define RES ADC_RES_12BIT

void sensorsInit(void);
void getSensors(cayenne_lpp_t *lpp);
void addSensorsToCayenne(cayenne_lpp_t *lpp);

#endif /*SENSORS_H*/
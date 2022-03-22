#include "pH.h"
/**
 * Measure the pH value with the sensor SEN0169 : https://wiki.dfrobot.com/Analog_pH_Meter_Pro_SKU_SEN0169
 **/

int pHInit(void)
{
    return adc_init(ADC_LINE(1));
}

double getpH(void)
{
    int sample = adc_sample(ADC_LINE(1), RES);
    if (sample < 0)
    {
        puts("pH : ADC_LINE(1): selected resolution not applicable\n");
    }
    else
    {
        double value = ((double)sample * 5.0 / 4096.0) * 1000;
        double equation = -(value / 59.16 - 7);
        puts("pH value : %f\n", equation);
        return equation;
    }
    return -1;
}

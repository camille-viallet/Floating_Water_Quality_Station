#include "pH.h"
#define Offset 1.39
/**
 * Measure the pH value with the sensor SEN0169 : https://wiki.dfrobot.com/Analog_pH_Meter_Pro_SKU_SEN0169
 **/

float pH = 0.;
float tension = 0.;

int pHInit(void)
{
    return adc_init(ADC_LINE(1));
}

float getpH(void)
{
    int32_t sample = adc_sample(ADC_LINE(1), RES);
    if (sample < 0)
    {
        puts("pH : ADC_LINE(1): selected resolution not applicable\n");
    }
    else
    {
        tension = (sample * 5.0 / 4095.0);
        pH = 14-(3.5 * tension) + Offset;
        return pH;
    }
    return -1;
}

void printpH(void)
{
    printf("pH : %f, Tension : %f V \n", pH, tension);
}

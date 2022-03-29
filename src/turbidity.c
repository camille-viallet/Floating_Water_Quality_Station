
#include "turbidity.h"
/**
 * Measure the pH value with the sensor SEN0169 : https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189
 **/
float turbidity = 0.;
float value = 0.;
float offset = 0.7887;

int turbidityInit(void)
{
    return adc_init(ADC_LINE(0));
}

float getTurbidity(void)
{
    int32_t sample = adc_sample(ADC_LINE(0), RES);

    if (sample < 0)
    {
        puts("turbidity : ADC_LINE(0): selected resolution not applicable\n");
    }
    else
    {
        printf("sample %ld\n", sample);
        value = (float)sample * 5.0 / 4095.0 - offset;
        if (value < 2.5)
        {
            turbidity = 3000;
        }
        else
        {
            turbidity = -1120.4 * pow(value, 2.0) + 5742.3 * value - 4352.9;
        }
        if (turbidity < 0)
        {
            turbidity = 0;
        }
        return turbidity;
    }
    return -1;
}

void printTurbidity(void)
{
    printf("Turbidity : %f NTU , Tension  : %f V\n", turbidity, value);
}

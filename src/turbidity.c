
#include "turbidity.h"

int turbidityInit(void)
{
    return adc_init(ADC_LINE(0));
}

double getTurbidity(void)
{
    int sample = adc_sample(ADC_LINE(0), RES);
    if (sample < 0)
    {
        printf("turbidity : ADC_LINE(0): selected resolution not applicable\n");
    }
    else
    {
        double value = (double)sample * 5.0 / 4096.0;
        double equation = -1120.4 * pow(value, 2.0) + 5742.3 * value - 4352.9;
        return equation;
    }
    return -1;
}

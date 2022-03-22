
#include "turbidity.h"
/**
 * Measure the pH value with the sensor SEN0169 : https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189
 **/
double turbidity = 0.;

int turbidityInit(void)
{
    return adc_init(ADC_LINE(0));
}

double getTurbidity(void)
{
    int sample = adc_sample(ADC_LINE(0), RES);
    if (sample < 0)
    {
        puts("turbidity : ADC_LINE(0): selected resolution not applicable\n");
    }
    else
    {
        double value = (double)sample * 5.0 / 4096.0;
        turbidity = -1120.4 * pow(value, 2.0) + 5742.3 * value - 4352.9;
        return turbidity;
    }
    return -1;
}

void printTurbidity(void)
{
    char str[20];
    int tur = (int)(turbidity * 100);
    sprintf(str, "pH : %d.%02d ºC",
            tur / 100,
            tur % 100);
    puts(str);
}

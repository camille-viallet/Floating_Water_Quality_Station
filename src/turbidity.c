
#include "turbidity.h"
/**
 * Measure the turbidity value with the sensor SEN0169 : https://wiki.dfrobot.com/Turbidity_sensor_SKU__SEN0189
 **/
float turbidity = 0.;
float value = 0.;
float offset = 0.7887; // the offset was chosen because of the method that we are using here

int turbidityInit(void)
{
    return adc_init(ADC_LINE(0)); // ADC_LINE(0) corresponds to the A4 pin on our board
}

float getTurbidity(void)
{
    int32_t sample = adc_sample(ADC_LINE(0), RES); // we get the value on the A4 pin

    if (sample < 0) // if the value doesn't exist, we are sending an error message
    {
        puts("turbidity : ADC_LINE(0): selected resolution not applicable\n");
    }
    else // otherwise, we are calculating the real turbidity value
    {
        printf("sample %ld\n", sample);
        value = (float)sample * 5.0 / 4095.0 - offset; // we get the voltage (the value returned by the sensor are between 0 and 4096)
        if (value < 2.5) // If the voltage is under 2.5, the turbidity is still at 3000 (which is its higher value)
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

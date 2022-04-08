#include "pH.h"
#define Offset 1.39 // the offset was chosen because of the method that we are using here
/**
 * Measure the pH value with the sensor SEN0169 : https://wiki.dfrobot.com/Analog_pH_Meter_Pro_SKU_SEN0169
 **/

float tension = 0.;

int pHInit(void)
{
    return adc_init(ADC_LINE(1)); // ADC_LINE(1) corresponds to the A3 pin on our board
}

float getpH(void)
{
    int32_t sample = adc_sample(ADC_LINE(1), RES); // we get the value on the A3 pin
    if (sample < 0) // if the value doesn't exist, we are sending an error message
    {
        puts("pH : ADC_LINE(1): selected resolution not applicable\n");
    }
    else // otherwise, we are calculating the real turbidity value
    {
        tension = (sample * 5.0 / 4095.0); // we get the voltage (the value returned by the sensor are between 0 and 4096)
        float pH = 14-(3.5 * tension) + Offset;
        return pH;
    }
    return -1;
}

void printpH(double pH)
{
    printf("pH : %f, Tension : %f V \n", pH, tension);
}

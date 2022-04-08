#include "sensors.h"

/* Declare globally the sensor DS18 descriptor */
static ds18_t ds18;

double turbidity;
double pH;
double temp;

void sensorsInit(void) {
    /*Initialize turbidity sensor : if it fails, return an error message */
    if (turbidityInit() < 0)
        puts("Turbidity sensor initialization failed");
    
      /*Initialize pH sensor : if it fails, return an error message */
    if (pHInit() < 0)
        puts("pH sensor initialization failed");

    /*Initialize temperature sensor : if it fails, return an error message */
    if (ds18_init(&ds18, &ds18_params[0]) != DS18_OK)
        puts("Temperature sensor initialization failed");
}

void getSensors(cayenne_lpp_t *lpp) {
    /* Declare the variable temperature */
    int16_t temperature = 0.;

    /* We are using the function which is getting the data from the temperature sensor */
    if (ds18_get_temperature(&ds18, &temperature) == DS18_OK)
    {
        temp = (double)temperature / 100.; // We need to divide the value to obtain the temperature in Celsius degrees
        printf("Temperature : %f °C\n", temp);
    }
    else // If there is no data, it returns the following error message
    {
        puts("[Error] Could not read temperature");
    }

    /* Get the turbidity value */
    turbidity = getTurbidity();
    printTurbidity(turbidity);

    /* Get the pH value */
    pH = getpH();
    printpH(pH);

    addSensorsToCayenne(lpp);
}

void addSensorsToCayenne(cayenne_lpp_t *lpp) {
    /* Prepare cayenne lpp payload and add the temperature value to the Cayenne LPP descriptor */
    cayenne_lpp_add_temperature(lpp, 0, temp);

    /* Convert the turbidity value in Cayenne format and add it to the Cayenne LPP descriptor */ 
    cayenne_lpp_add_analog_input(lpp, 1, turbidity);

    /* Convert the pH value in Cayenne format and add it to the Cayenne LPP descriptor */
    cayenne_lpp_add_analog_input(lpp, 2, pH);
}
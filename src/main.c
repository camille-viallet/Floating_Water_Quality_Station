#include <string.h>

#include "timex.h"
#include "ztimer.h"

#include "sx126x.h"
#include "sx126x_netdev.h"
#include "sx126x_params.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

#include "ds18.h"
#include "ds18_params.h"

#include "turbidity.h"
#include "pH.h"

#include "board.h"

/* Add the cayenne_lpp header here */
#include "cayenne_lpp.h"

/* Declare globally the sx127x radio driver descriptor */
static sx126x_t sx126x;

/* Declare globally the loramac descriptor */
static semtech_loramac_t loramac;

/* Declare globally Cayenne LPP descriptor here */
static cayenne_lpp_t lpp;

/* Declare globally the sensor DS18 descriptor */
static ds18_t ds18;

/* Device and application informations required for OTAA activation */

// Emeric TTN
//static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = {0x2C, 0xF7, 0xF1, 0x20, 0x24, 0x90, 0x05, 0x33};
//
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = {0xC4, 0xD9, 0x58, 0x6D, 0x09, 0xC7, 0xB7, 0x88};
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = {0x1F, 0x55, 0xCE, 0x3C, 0x45, 0x6C, 0xAB, 0x6F, 0x16, 0x49, 0x0B, 0x9D, 0xC9, 0xD6, 0xC7, 0xC2};

// Camille TTN
/*static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = {0x2C, 0xF7, 0xF1, 0x20, 0x24, 0x90, 0x00, 0xBE};
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
*/

// Emeric Chirpstack
/*static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = {0x2c, 0xf7, 0xf1, 0x20, 0x24, 0x90, 0x05, 0x33};
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = {0x54, 0x70, 0x68, 0xC7, 0xBB, 0x7F, 0xE1, 0x78, 0xF2, 0x6E, 0x4B, 0x53, 0x80, 0xF1, 0x7F, 0xD1};
*/

static void sender(void)
{
    while (1)
    {
        /* wait 20 secs */
        ztimer_sleep(ZTIMER_MSEC, 20 * MS_PER_SEC);

        // Get the temperature value and convert it in Cayenne format
        int16_t temperature = 0;
        float temp = 0;

        //char str[100];

        if (ds18_get_temperature(&ds18, &temperature) == DS18_OK)
        {
            bool negative = (temperature < 0);
            if (negative)
            {
                temp = -temperature;
            }
            temp = (float)temperature / 100.;
            printf("Temperature : %f °C\n", temp);
        }
        else
        {
            puts("[Error] Could not read temperature");
        }

        /// Prepare cayenne lpp payload here
        cayenne_lpp_add_temperature(&lpp, 0, temp);

        // Get the turbidity value and convert it in Cayenne format
        double turbidity = getTurbidity();
        printTurbidity();
        cayenne_lpp_add_analog_input(&lpp, 1, turbidity);

        // Get the pH value and convert it in Cayenne format
        double pH = getpH();
        printpH();
        cayenne_lpp_add_analog_input(&lpp, 2, pH);


        /* send the LoRaWAN message */
       /* uint8_t ret = semtech_loramac_send(&loramac, lpp.buffer, lpp.cursor);
        if (ret == SEMTECH_LORAMAC_TX_DONE)
        {
            puts("Send Data OK");
        }
        else if (ret == SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED)
        {
            puts("Duty Cycle Restriction");
        }
        else if (ret == SEMTECH_LORAMAC_TX_ERROR)
        {
            puts("Invalid Parameter given");
        }*/

        /* clear buffer once done here */
        cayenne_lpp_reset(&lpp);
    }

    /* this should never be reached */
    return;
}

int main(void)
{
    /*Initialize turbidity sensor*/
    if (turbidityInit() < 0)
    {
        puts("Turbidity sensor initialization failed");
    }
      /*Initialize turbidity sensor*/
    if (pHInit() < 0)
    {
        puts("pH sensor initialization failed");
    }
    /*Initialize temperature sensor*/
    if (ds18_init(&ds18, &ds18_params[0]) != DS18_OK)
        puts("Temperature sensor initialization failed");

    /* initialize the radio driver */
    sx126x_setup(&sx126x, &sx126x_params[0], 0);
    loramac.netdev = &sx126x.netdev;
    loramac.netdev->driver = &sx126x_driver;

    /* initialize the loramac stack */
    semtech_loramac_init(&loramac);

    /* use a fast datarate so we don't use the physical layer too much */
    semtech_loramac_set_dr(&loramac, 5);

    /* set the LoRaWAN keys */
    semtech_loramac_set_deveui(&loramac, deveui);
    semtech_loramac_set_appeui(&loramac, appeui);
    semtech_loramac_set_appkey(&loramac, appkey);

    /* start the OTAA join procedure */
    puts("Starting join procedure");
    /*uint8_t state = semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA);
    if (state == SEMTECH_LORAMAC_JOIN_SUCCEEDED)
    {
        puts("Join procedure succeeded");
    }
    else if (state == SEMTECH_LORAMAC_ALREADY_JOINED)
    {
        puts("Already join");
        return 1;
    }
    else if (state == SEMTECH_LORAMAC_BUSY)
    {
        puts("In progress");
    }
    else if (state == SEMTECH_LORAMAC_JOIN_FAILED)
    {
        puts("Join Failed");
        return 1;
    }
    else
    {
        puts("Error on the join procedure");
        return 1;
    }
    puts("end join procedure");*/

    /* call the sender function */
    sender();
    puts("end sender");
    return 0;
}

#include <string.h>

#include "timex.h"
#include "ztimer.h"

#include "sx126x.h"
#include "sx126x_netdev.h"
#include "sx126x_params.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

//#include "hts221.h"
//#include "hts221_params.h"

#include "board.h"

/* TODO: Add the cayenne_lpp header here */
#include "cayenne_lpp.h"

/* Declare globally the sx127x radio driver descriptor */
static sx126x_t sx126x;

/* Declare globally the loramac descriptor */
static semtech_loramac_t loramac;

/* TODO: Declare globally Cayenne LPP descriptor here */
static cayenne_lpp_t lpp;

/* Device and application informations required for OTAA activation */
// Camille TTN
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = {0x2C, 0xF7, 0xF1, 0x20, 0x24, 0x90, 0x00, 0xBE};
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06};
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};

/*
// Camille Helium
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = {0x60, 0x81,0xF9,0x6C,0x47,0xF9,0xA7,0xD3};                                                 //Camille
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = {0x60,0x81,0xF9,0x45,0x86,0x89,0x57,0xBB};                                                 //Camille
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = {0xB8,0x53,0xCA,0xC4,0x29,0x03,0x23,0x9F,0xDF,0x24,0x39,0x30,0x20,0x79,0x30,0xC8}; //Camille
*/
static void sender(void)
{
    while (1)
    {
        /* wait 20 secs */
        ztimer_sleep(ZTIMER_MSEC, 20 * MS_PER_SEC);

        /* do some measurements */
        uint16_t humidity = 20;
        int16_t temperature = 0;

        /* TODO: prepare cayenne lpp payload here */
        cayenne_lpp_add_temperature(&lpp, 0, (float)temperature);
        cayenne_lpp_add_relative_humidity(&lpp, 1, (float)humidity);

        /* send the LoRaWAN message */
        uint8_t ret = semtech_loramac_send(&loramac, lpp.buffer, lpp.cursor);
        if (ret == SEMTECH_LORAMAC_TX_DONE)
        {
            printf("Send Data");
        }
        else if (ret == SEMTECH_LORAMAC_DUTYCYCLE_RESTRICTED)
        {
            printf("Duty Cycle Restriction");
        }
        else if (ret == SEMTECH_LORAMAC_TX_ERROR )
        {
            printf("Invalid Parameter given");
        }

        /* TODO: clear buffer once done here */
        cayenne_lpp_reset(&lpp);
    }

    /* this should never be reached */
    return;
}

int main(void)
{

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
    uint8_t state = semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA);
    if (state == SEMTECH_LORAMAC_JOIN_SUCCEEDED)
    {
        puts("Join procedure succeeded");
    }
    else if (state == SEMTECH_LORAMAC_ALREADY_JOINED)
    {
        puts("Already join");
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
    printf("end join procedure");

    /* call the sender function */
    sender();
    printf("end sender");
    return 0;
}

/*
 * Copyright (C) 2014-2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Test application for peripheral ADC drivers
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>

#include "ztimer.h"
#include "periph/adc.h"

#define RES             ADC_RES_10BIT
#define DELAY_MS        100U

int main(void)
{
    int sample = 0;

    puts("\nRIOT ADC peripheral driver test\n");
    puts("This test will sample all available ADC lines once every 100ms with\n"
         "a 10-bit resolution and print the sampled results to STDIO\n\n");

    /* initialize all available ADC lines */
    //for (unsigned i = 0; i < ADC_NUMOF; i++) {
        if (adc_init(ADC_LINE(0)) < 0) {
            printf("Initialization of ADC_LINE(0) failed\n");
            return 1;
        } else {
            printf("Successfully initialized ADC_LINE(0)\n");
        }
    //}

    while (1) {
        //for (unsigned i = 0; i < ADC_NUMOF; i++) {
            sample = adc_sample(ADC_LINE(0), RES);
            if (sample < 0) {
                printf("ADC_LINE(0): selected resolution not applicable\n");
            } else {
                printf("ADC_LINE(0): %d.%02d\n", sample*5/4096, sample*5%4096);
            }
        //}
        ztimer_sleep(ZTIMER_MSEC, DELAY_MS);
    }

    return 0;
}

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
int main() {
    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    stdio_init_all();

    int count = 0; // Counter variable to keep track of input count
   
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("Start!\n");
 
    while (1) {
        char message[100];
        scanf("%s", message);
        printf("message: %s\r\n",message);

       if (count % 2 == 0) {
            // Turn on the LED
            gpio_put(LED_PIN, 1);
        } else {
            // Turn off the LED
            gpio_put(LED_PIN, 0);
        }
        
        count++; // Increment the count for the next iteration
        
        sleep_ms(50);
    }
}
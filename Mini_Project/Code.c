/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include <stdio.h>

int main() {

    const uint LED_PIN = 20;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    const uint LED_PIN1 = 25;
    gpio_init(LED_PIN1);
    gpio_set_dir(LED_PIN1, GPIO_OUT);
    const uint LED_PIN2 = 24;
    gpio_init(LED_PIN2);
    gpio_set_dir(LED_PIN2, GPIO_OUT);
    const uint BUTTON_PIN = 26;
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    const uint SLIDER_RIGHT_PIN = 27;
    gpio_init(SLIDER_RIGHT_PIN);
    gpio_set_dir(SLIDER_RIGHT_PIN, GPIO_IN);
    const uint SLIDER_LEFT_PIN = 28;
    gpio_init(SLIDER_LEFT_PIN);
    gpio_set_dir(SLIDER_LEFT_PIN, GPIO_IN);

    while (true) {
        if(gpio_get(BUTTON_PIN) && gpio_get(SLIDER_RIGHT_PIN)){
        gpio_put(LED_PIN, 0);
        gpio_put(LED_PIN1, 1);
        gpio_put(LED_PIN2, 1);
        sleep_ms(2000);
        }
        else if(gpio_get(BUTTON_PIN) && gpio_get(SLIDER_LEFT_PIN)){
        gpio_put(LED_PIN, 1);
        gpio_put(LED_PIN1, 1);
        gpio_put(LED_PIN2, 0);
        sleep_ms(2000);
        }
        else{
        gpio_put(LED_PIN, 0);
        gpio_put(LED_PIN1, 0);
        gpio_put(LED_PIN2, 0);  
        sleep_ms(2000);
        }
    }

}
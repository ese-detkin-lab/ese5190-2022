/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "hardware/adafruit_qtpy_rp2040.h"

#define IS_RGBW true
#define NUM_PIXELS 150

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 2
#endif
#define PICO_DEFAULT_WS2812_POWER_PIN 11
#define BOOT_PIN 21

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}


int main() {
    //set_sys_clock_48();
    stdio_init_all();
  

    // todo get free sm
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    int sequence[200]={};
    for (int i=0; i<200; i++) {
        sequence[i]=0;
    }
    const uint POW_PIN = PICO_DEFAULT_WS2812_POWER_PIN;
    gpio_init(POW_PIN);
    gpio_set_dir(POW_PIN, GPIO_OUT);


    while (1) {
        if(!(gpio_get(BOOT_PIN))==1){
            sleep_ms(200);
            for (int x=0; x<200; x++){
            printf("Enter BOOT_PIN value loop\n");
            uint bootval = !(gpio_get(BOOT_PIN));
            sleep_ms(50);
                if (bootval==1){
                    sequence[x]=1;
                }
                else{
                    sequence[x]=0;
                }
            }

            sleep_ms(200);

            for (int a=0; a<200; a++){
                printf("Entered POW_PIN set loop\n");
                gpio_put(POW_PIN, sequence[a]);
                printf("Neopixel sequences\n");
                put_pixel(urgb_u32(0xC7,0x15,0x85));
                sleep_ms(50);
            }
        }
        //printf("Hello ! Neopixel Blinks\n");
    }
}

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "blink.pio.h"
#define QTPY_BOOT_PIN 21
const uint boot_pin = QTPY_BOOT_PIN;
void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq);

int main() {
    setup_default_uart();

    // todo get free sm
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &blink_program);
    uint offset1 = pio_add_program(pio, &bootpin_program);
    bootpin_program_init(pio,3,offset1,boot_pin);
    printf("Loaded program at %d\n", offset);

    while(true){
    if((uint8_t)pio_sm_get(pio,3)==0){
    blink_pin_forever(pio, 0, offset, 20, 4);
    blink_pin_forever(pio, 1, offset, 25, 4);   
    }
    else{
    blink_pin_forever(pio, 1, offset, 25, 4);
    blink_pin_forever(pio, 2, offset, 24, 4);
    }
    }
}

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    printf("Blinking pin %d at %d Hz\n", pin, freq);

    // PIO counter program takes 3 more cycles in total than we pass as
    // input (wait for n + 1; mov; jmp)
    
    pio->txf[sm] = (clock_get_hz(clk_sys) / (2 * freq)) - 3;
}

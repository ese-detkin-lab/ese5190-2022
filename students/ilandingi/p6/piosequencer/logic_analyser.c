/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// PIO logic analyser example
//
// This program captures samples from a group of pins, at a fixed rate, once a
// trigger condition is detected (level condition on one pin). The samples are
// transferred to a capture buffer using the system DMA.
//
// 1 to 32 pins can be captured, at a sample rate no greater than system clock
// frequency.

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/structs/bus_ctrl.h"
// #include "adafruit_qtpy_rp2040.h" 
// Some logic to analyse:
// #include "hardware/structs/pwm.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
const uint CAPTURE_PIN_BASE = 24;   /* the first pin number */
const uint CAPTURE_PIN_COUNT = 2;   /* total number of pins based on PIN_BASE*/
const uint CAPTURE_N_SAMPLES = 32*3;  /* total sample cycles of one pin */

static inline uint bits_packed_per_word(uint pin_count) {
    const uint SHIFT_REG_WIDTH = 32;
    /*not quite understand*/
    //  32%2=0
    return SHIFT_REG_WIDTH - (SHIFT_REG_WIDTH % (pin_count));
}

void logic_analyser_init(PIO pio, uint sm, uint pin_base, uint pin_count, float div) {
    // Load a program to capture n pins. This is just a single `in pins, n`
    // instruction with a wrap.
    uint16_t capture_prog_instr = pio_encode_in(pio_pins, pin_count);   /*  => $ IN pio_pins pin_count
                                                                            (pio_pins=0, source =PINS)
                                                                            pin_count=2, shift 2bits to ISR 
                                                                            datasheet 3.2.3.2 ISR  */
    struct pio_program capture_prog = {
            .instructions = &capture_prog_instr,
            .length = 1,
            .origin = -1
    };
    uint offset = pio_add_program(pio, &capture_prog);                  /*  Create the pio program */

    // Configure state machine to loop over this `in` instruction forever,
    // with autopush enabled.
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_in_pins(&c, pin_base);
    sm_config_set_wrap(&c, offset, offset);
    sm_config_set_clkdiv(&c, div);
    // Note that we may push at a < 32 bit threshold if pin_count does not
    // divide 32. We are using shift-to-right, so the sample data ends up
    // left-justified in the FIFO in this case, with some zeroes at the LSBs.
                                                /* push_threshold */
    sm_config_set_in_shift(&c, true, true, bits_packed_per_word(pin_count));
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_RX);
    pio_sm_init(pio, sm, offset, &c);
}

void logic_analyser_arm(PIO pio, uint sm, uint dma_chan, uint32_t *capture_buf, size_t capture_size_words,
                        uint trigger_pin, bool trigger_level) {
    pio_sm_set_enabled(pio, sm, false);
    // Need to clear _input shift counter_, as well as FIFO, because there may be
    // partial ISR contents left over from a previous run. sm_restart does this.
    pio_sm_clear_fifos(pio, sm);
    pio_sm_restart(pio, sm);

    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);
    channel_config_set_dreq(&c, pio_get_dreq(pio, sm, false));  //Return the DREQ to use for pacing transfers to/from a particular state machine FIFO.
                                                    // bool is_tx= false
    dma_channel_configure(dma_chan, &c,
        capture_buf,        // Destination pointer
        &pio->rxf[sm],      // Source pointer
        capture_size_words, // Number of transfers
        true                // Start immediately
    );

    pio_sm_exec(pio, sm, pio_encode_wait_gpio(trigger_level, trigger_pin)); /* stall until the first up edge */
    pio_sm_set_enabled(pio, sm, true);
}

void print_capture_buf(const uint32_t *buf, uint pin_base, uint pin_count, uint32_t n_samples) {
    // Display the capture buffer in text form, like this:
    // 00: __--__--__--__--__--__--
    // 01: ____----____----____----
    printf("Capture:\n");
    // Each FIFO record may be only partially filled with bits, depending on
    // whether pin_count is a factor of 32.
    uint record_size_bits = bits_packed_per_word(pin_count);
    for (int pin = 0; pin < pin_count; ++pin) {
        printf("%02d: ", pin + pin_base);
        for (int sample = 0; sample < n_samples; ++sample) {
            uint bit_index = pin + sample * pin_count;
            uint word_index = bit_index / record_size_bits;
            // Data is left-justified in each FIFO entry, hence the (32 - record_size_bits) offset
            uint word_mask = 1u << (bit_index % record_size_bits + 32 - record_size_bits);
            printf(buf[word_index] & word_mask ? "-" : "_");
        }
        printf("\n");
    }
    // for(int pin=0;pin<pin_count;pin++){
        printf("%02d: ", 0 + pin_base);
        for (int sample = 0; sample < n_samples; ++sample) {
            // uint bit_index = pin + sample * pin_count;
            // uint word_index = bit_index / record_size_bits;
            // // Data is left-justified in each FIFO entry, hence the (32 - record_size_bits) offset
            // uint word_mask = 1u << (bit_index % record_size_bits + 32 - record_size_bits);
            // printf(buf[word_index] & word_mask ? "-" : "_");
            printf("%x",buf[sample]);
        }
    // }
    
}

#define QTPY_BOOT_PIN 21

int main() {
    stdio_init_all();
    // uint64_t
    while(stdio_usb_connected()!=true);

    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    gpio_init(CAPTURE_PIN_BASE);
    gpio_init(CAPTURE_PIN_BASE+1);
    printf("PIO logic analyser example\n");
    gpio_set_dir(CAPTURE_PIN_BASE, GPIO_IN);
    gpio_set_dir(CAPTURE_PIN_BASE+1, GPIO_IN);
    // gpio_pull_up(CAPTURE_PIN_BASE);
    // gpio_pull_up(CAPTURE_PIN_BASE+1);

    // We're going to capture into a u32 buffer, for best DMA efficiency. Need
    // to be careful of rounding in case the number of pins being sampled
    // isn't a power of 2.
    uint total_sample_bits = CAPTURE_N_SAMPLES * CAPTURE_PIN_COUNT+31; // 96*2
    // total_sample_bits += bits_packed_per_word(CAPTURE_PIN_COUNT) - 1;

    uint buf_size_words = total_sample_bits /32;
    printf("buf_size_words=%d\n",buf_size_words);
    uint32_t *capture_buf = malloc(buf_size_words * sizeof(uint32_t));
    hard_assert(capture_buf);

    // Grant high bus priority to the DMA, so it can shove the processors out
    // of the way. This should only be needed if you are pushing things up to
    // >16bits/clk here, i.e. if you need to saturate the bus completely.
    bus_ctrl_hw->priority = BUSCTRL_BUS_PRIORITY_DMA_W_BITS | BUSCTRL_BUS_PRIORITY_DMA_R_BITS;

    PIO pio = pio0;
    uint sm = 0;
    uint dma_chan = 0;
    uint32_t counter=0;
    uint32_t prev_sda=0;
    uint32_t prev_scl=0;
    logic_analyser_init(pio, sm, CAPTURE_PIN_BASE, CAPTURE_PIN_COUNT, 1.f);
    while(true){
        // printf("Arming trigger\n");
        logic_analyser_arm(pio, sm, dma_chan, capture_buf, buf_size_words, CAPTURE_PIN_BASE, true);

        while(gpio_get(QTPY_BOOT_PIN)>0);/*wait until press button*/

        // The logic analyser should have started capturing as soon as it saw the
        // first transition. Wait until the last sample comes in from the DMA.
        dma_channel_wait_for_finish_blocking(dma_chan);
        printf("\nSDA\n");
        for (int i = 0; i < buf_size_words; ++i) {
            for(int j=0;j<32;j+=2){
                // printf(capture_buf[i]>>j == 1? '-':'.');
                // printf("%c",capture_buf[i]&(0x01<<j)? '-':'_');
                printf("%c",(capture_buf[i]>>j)&0x01 ? '-':'_');
            }    
            printf(",") ;
        }
        printf("\nSCL\n");
        for (int i = 0; i < buf_size_words; ++i) {
            for(int j=1;j<32;j+=2){
                // printf(capture_buf[i]>>j == 1? '-':'.');
                // printf("%c",capture_buf[i]&(0x01<<j)? '-':'_');
                printf("%c",(capture_buf[i]>>j)&0x01 ? '-':'_');
            }   
            printf(",") ;
        }

        uint32_t prev_counter=counter;
        printf("SDA\n");
        for(uint32_t i=0;i<buf_size_words;i++){
            for(int j=0;j<32;j+=2){
                if((capture_buf[i]>>j)&0x01^prev_sda){
                    prev_sda=!prev_sda;
                    printf("SDA:%d,",counter);
                    printf(",%d\n",prev_sda);
                }
                counter++;
            }
        }
        counter=prev_counter;
        printf("SCL\n");
        for(uint32_t i=0;i<buf_size_words;i++){
            for(int j=1;j<32;j+=2){
                if((capture_buf[i]>>j)&0x01^prev_scl){
                    prev_scl=!prev_scl;
                    printf("\tSCL:%d,",counter);
                    printf(",%d\n",prev_scl);
                }
                counter++;
            }
        }
    }
}

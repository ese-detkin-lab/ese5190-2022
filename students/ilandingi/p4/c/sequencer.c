#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "hardware/gpio.h"
#include "neopixel.h"
#include "repl.h"


#define QTPY_BOOT_PIN 21
#define clk_sys 5

const uint CAPTURE_N_SAMPLES = 512;

const uint NUMBER_BUF_SIZE = 7;

void record(uint8_t *boot_buf, uint pin_base, uint n_sample){
    for (int index = 0; index < n_sample; ++index){
        boot_buf[index] = !(gpio_get(pin_base));
        if(boot_buf[index]){
            neopixel_set_rgb(0x000000ff);
        }else{
            neopixel_set_rgb(0x00000000);
        }
        sleep_ms(10);
    }
}

void display(const uint8_t *buf, int ration, uint length){
    printf("Start playing record...\n");
    for (int index = 0; index < length; ++index) {
        if(buf[index]){
            neopixel_set_rgb(0x000000ff);
        }else{
            neopixel_set_rgb(0x00000000);
        }
        sleep_us(10000/ration);
    }
}


typedef struct {
    uint32_t command;
    uint32_t button_is_pressed;
    uint32_t light_color;
} Sequencer; 


int main() {

    stdio_init_all();
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();

    Sequencer status;
    status.command =  0x00000000;
    status.button_is_pressed = 0x00000000;
    status.light_color =   0x000000ff; //Blue

    uint8_t * capture_buf = malloc(CAPTURE_N_SAMPLES * sizeof(uint8_t));

    int ans = 1;

    while (true) {
        status.command = getchar_timeout_us(0); // don't block main loop
        switch(status.command) { // poll every cycle
            case 'r':
                printf("r\n");
                neopixel_set_rgb(0x00ff0000); //Red
                Rread();
                break;
            case 'w':
                printf("w\n");
                neopixel_set_rgb(0x00ffffff); //White
                Rwrite();
                break;
            case 't':
                printf("Recording from boot pin\n");
                record(capture_buf, QTPY_BOOT_PIN, CAPTURE_N_SAMPLES);
                printf("Recording done!\n");
                break;
            case 'p':
                printf("the speed up replay velocity you want is?\n");
                scanf("%d", &ans);
                printf("it will repkay in speed: %d\n", ans);
                display(capture_buf, ans, CAPTURE_N_SAMPLES);
                printf("Done!\n");
                break;
        }
        if (gpio_get(QTPY_BOOT_PIN)) { // poll every cycle, 0 = "pressed"
            status.button_is_pressed = 0x00000000;
            status.light_color = 0x000000ff;
        } else {
            status.button_is_pressed = 0x00000001;
        }
        if (status.button_is_pressed) { // poll every cycle
            neopixel_set_rgb(status.light_color);
        } else {
            neopixel_set_rgb(0x00000000);
        }
        sleep_ms(10); // don't DDOS the serial console
    }
    return 0;
}   
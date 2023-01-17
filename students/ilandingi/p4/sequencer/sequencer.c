#include "pico/stdlib.h"
#include <stdio.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "repl.h"
#include "ws2812.pio.h" // pio0
#include <inttypes.h>

#define QTPY_BOOT_PIN 21

#define READ 'r'
#define WRITE 'W'
#define record 's'
#define replay 'g'


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
    uint32_t flag = 0x00000000;

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
            case 's':
                printf("s\n");
                while (true){
                    flag = 0x00000000;
                    flag = getchar_timeout_us(0);
                    if (gpio_get(QTPY_BOOT_PIN)) { // poll every cycle, 0 = "pressed"
                        printf("1\n");
                        status.button_is_pressed = 0x00000000;
                        status.light_color = 0x000000ff;
                    } else {
                        printf("2\n");
                        status.button_is_pressed = 0x00000001;
                    }
                    if (status.button_is_pressed) { // poll every cycle
                        neopixel_set_rgb(status.light_color);
                    } else {
                        neopixel_set_rgb(0x00000000);
                    }
                    if(flag=='N'){
                        break;
                    }
                    sleep_ms(10);
                }
                break;
            case 'g':
                while(true){
                    flag = 0x00000000;
                    flag = getchar_timeout_us(0);
                    if(flag == 'p'){
                        neopixel_set_rgb(0x000000ff);
                    }
                    if(flag == 'n'){
                        neopixel_set_rgb(0x00000000);
                    }
                    if (flag == 'N') {
                        break;
                    }
                    sleep_ms(10); 
                }
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

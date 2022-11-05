#include "pico/stdlib.h"
#include <stdio.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "registers.h"
#define QTPY_BOOT_PIN 21

//sio base 0xd0000000
//offset 0x00000004

volatile uint32_t * boot_pin_adress;
uint32_t full_gpio_register_value;
uint32_t pin21_selection_mask;
uint32_t selected_pin_state;
uint32_t shifted_pin_21_state;

typedef struct {
    uint32_t last_serial_byte;
    uint32_t button_is_pressed;
    uint32_t light_color;
} Flashlight; 

void render_to_console(Flashlight status) {
    // adjust console window height to match 'frame size'
    for (uint8_t i=0; i<10; i++) { 
        printf("\n");
    }
    printf("button_is_pressed:  0x%08x\n",   status.button_is_pressed);
    printf("light_color:        0x%08x\n",   status.light_color);
}  

int main() {

    stdio_init_all();
    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();

    Flashlight status;
    status.last_serial_byte =  0x00000000;
    status.button_is_pressed = 0x00000000;
    status.light_color =       0x000000ff;

    while (true) {
        status.last_serial_byte = getchar_timeout_us(0); // don't block main loop
        switch(status.last_serial_byte) { // poll every cycle
            case 'r':
                status.light_color = 0x00ff0000;
                break;
            case 'g':
                status.light_color = 0x0000ff00;
                break;
            case 'b':
                status.light_color = 0x000000ff;
                break;
            case 'w':
                status.light_color = 0x00ffffff;
                break;
        }
        //if (gpio_get(QTPY_BOOT_PIN)) { // poll every cycle, 0 = "pressed" ORIGINAL CODE FOR IF STATEMENT
        boot_pin_adress = (volatile uint32_t *) 0xd0000004;
        full_gpio_register_value = (uint32_t) *boot_pin_adress;
        pin21_selection_mask = 1u << 21;
        selected_pin_state = full_gpio_register_value & pin21_selection_mask;            
        shifted_pin_21_state = selected_pin_state >> 21;
        if(shifted_pin_21_state) {   
            status.button_is_pressed = 0x00000000;
        } else {
            status.button_is_pressed = 0x00000001;
        }
        if (status.button_is_pressed) { // poll every cycle
            neopixel_set_rgb(status.light_color);
        } else {
            neopixel_set_rgb(0x00000000);
        }
        render_to_console(status);
        sleep_ms(10); // don't DDOS the serial console
    }
    return 0;
}                  

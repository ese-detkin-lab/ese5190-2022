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
#include "sio_registers.h"
#include "hardware/structs/sio.h" 
#include "hardware/gpio.h"

#define IS_RGBW true
#define NUM_PIXELS 150

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 12
#define BOOT 21
#endif

typedef struct {
    uint32_t status;
} boot_stat; 
typedef          uint32_t   VALUE;
typedef volatile uint32_t * ADDRESS;

VALUE register_read(ADDRESS address) {
    return *address;
}

void register_write(ADDRESS address, VALUE value) {
    *address = value;
}

void set_neopixel_color(uint32_t color) { 
    pio_sm_put_blocking(pio0, 0, color << 8u);      //Write a word of data in state machines's TX FIFO. Block if the TX FIFO is full.
} 
void blink(uint32_t color){
    //The LED will blink 4 times with respective color. 500ms on and 500ms off.
    
      
        set_neopixel_color(color);
        sleep_ms(500);
        set_neopixel_color(0x000000);
        sleep_ms(500);

}
int i;
int main() {
    stdio_init_all();       // Initialize all of present standard stdio types that are linked into binary 
    printf("WS2812 Smoke Test, using pin %d", WS2812_PIN);      //Display which pin is used as WS2812_PIN

    PIO pio = pio0;     //Chooses which PIO instance to be used from 2 available ones i.e. pio0 and pio1
    int sm = 0;     //State machine is set to be 0
    uint offset = pio_add_program(pio, &ws2812_program);       //Find allocation where there is enough space to store our program

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);      //Instantiate an instance of driver program

    int t = 0;
    const uint LED_PIN = 11;        //Defining neopixel power pin 
    const uint BOOT_PIN = BOOT;
    gpio_init(LED_PIN);     //Initializing GPIO pin
    gpio_set_dir(LED_PIN, GPIO_OUT);        // Set the pin as output
    gpio_init(BOOT_PIN);
    gpio_set_dir(BOOT_PIN, GPIO_IN);
    stdio_init_all();
    boot_stat stat;
    gpio_put(LED_PIN, 1);       //Set the pin high
    uint32_t color;
    VALUE a;
    long int command;   
    long int value;                                                                     //Value Variable Declaration
    char operation; 
      printf("Waiting for USB\n");                                                        //Waiting for USB Connection
    while (!stdio_usb_connected()) {
      printf(".");
      sleep_ms(500);
    }
    printf("\nUSB host detected!\n");
    printf("\nWelcome to REPL Console, press 'h' for help\n");  
    while (1) {
        sleep_ms(10);
        printf("\n Enter command: r for reading from a register & w for writing to a register\n",a);
        scanf(" %c",&operation); 
        printf("\n");
        
        switch(operation){                                                              //Switch Case for execution of requested operation
            case 'r':
                printf("\nRead Mode Entered, Enter Address:");
                sleep_ms(10);
                scanf(" %x",&command);                                                  //Reading Address from terminal                                                
                printf("\n%x\n",command);
                a = register_read((ADDRESS)command);                                    //Reading the value from the requested Register
                printf("\n%x\n",a);
                break;
            case 'w':                                                                   //Write Mode Case
                printf("\nWrite Mode Entered, Enter Address:");
                sleep_ms(10);                                                           
                scanf(" %x",&command); 
                printf("\n%x\n",command);                                         //Reading address from the terminal
                printf("\nWrite Mode Entered, Enter Value to be Set:\n");                 
                sleep_ms(10);                                                   
                scanf(" %x",&value);                                                    //Reading value to be set in the register from terminal
                
                register_write((ADDRESS)command,(VALUE)value);                          //Writing the value to the register address
                break;     
            default:
                printf("Invalid Commmand\n"); 
        }

        if(!(1<<21 & a))
            set_neopixel_color(0x00ff0000);
        else 
            set_neopixel_color(0x000000ff);
    }
}
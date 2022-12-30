#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include "neopixel.h"
#include "hardware/gpio.h"
#include "registers.h"
#include <strings.h>
#include <string.h>

#define QTPY_BOOT_PIN 21
#define SIO
#ifndef PICO_DEFAULT_WS2812_PIN
#define PICO_DEFAULT_WS2812_PIN 12
#endif

#ifndef PICO_DEFAULT_WS2812_POWER_PIN
#define PICO_DEFAULT_WS2812_POWER_PIN 11
#endif

volatile uint32_t * address;
char inputs[9];   // to store 8 bit hex input and contains one more bit as string stopping flag
char user_input_1;
uint32_t address_hex;
int legit_con;
int32_t convert_inputs;
int length_of_inputs;
int  count = 0;
int yn_input;
uint32_t value_hex;

typedef struct {
    uint32_t reg_address;
    uint32_t reg_value;
} Register_status; 

void render_to_console(Register_status status) {
    // adjust console window height to match 'frame size'

    printf("reg_address:  0x%08x\n",   status.reg_address);
    printf("reg_value:    0x%08x\n",   status.reg_value);
    for (uint8_t i=0; i<6; i++) { 
        printf("\n");
    }
}  

int check_legit_address(uint32_t convert_inputs){
    int leftover = convert_inputs % 4;
    //printf("check legit: %x\n", leftover);
    if (leftover== 0){
        //printf("The address you want to access is: %u\n", convert_inputs);
        //printf("checklegit:0");
        return 0;
    }
    else {
        printf("The address you want to access is ilegal\n");
        for (uint8_t i=0; i<6; i++) { 
            printf("\n");
        }
        return 1;
    }
}

int get_input(){
        sleep_ms(6000);
        for (int i= 0; i<8; i++ ) {
            user_input_1 = getchar_timeout_us(0);
            inputs[i] = user_input_1;
        }
        //get_input();
        inputs[8] = '\0';
        //let excessive inputs be discarded
        for (int i= 0; i<8; i++ ) {
            getchar_timeout_us(0);
        }
}

int main() {

    stdio_init_all();
    // gpio_init(QTPY_BOOT_PIN);
    // gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();
    stdio_usb_init();

    Register_status status;

    while (!stdio_usb_connected()){
        printf(".");
        sleep_ms(500);
    };
    printf("Now start\n");

    while (true) {

        sleep_ms(10);
        printf("What register would you like to access?\n");
 
        // print inputted address        
        get_input();
        sleep_ms(100);
        convert_inputs = atoi(inputs);
        //printf("int inputs is: %u", convert_inputs);

        legit_con = check_legit_address(convert_inputs);
        if (legit_con == 1){
            //printf("reacched cocntinue\n");
            address_hex = 0;
            status.reg_address = 0;
            status.reg_value = 0;
            continue;
        }
        // long int address_hex = strtol(inputs, NULL, 16);
        int sscanf_status = sscanf(inputs,"%x",&address_hex);
        if (sscanf_status == 1){
                printf("Sscanf status: %d\n", sscanf_status);
                printf("The hex address is: %x\n", address_hex);

                address = (volatile uint32_t *) address_hex;
                status.reg_address = address_hex;
                status.reg_value = (uint32_t) *address;
                render_to_console(status);
                sleep_ms(10);
        }
        else {
            printf("No input has been detected, please retry!\n");
            for (uint8_t i=0; i<6; i++) { 
                printf("\n");
            }
            continue;
        }

        printf("Do you want to write new value to this register? (1 = yes, 0 = no)\n");
        sleep_ms(5000);
        yn_input = getchar_timeout_us(0);
        for (int i= 0; i<8; i++ ) {
            getchar_timeout_us(0);
        }

        if(yn_input == '1'){
            printf("Enter the new 8 bit hex value you want to write in this register:\n");
            get_input();  //input value stores in inputs[]

            // print inputted address        
            sleep_ms(100);
            convert_inputs = atoi(inputs);
 
            int sscanf_status = sscanf(inputs,"%x",&value_hex);
            *address = value_hex;
            if (sscanf_status == 1){
                    printf("sccaf status 1\n");
                    status.reg_value = (uint32_t) *address;
                    render_to_console(status);
            }
            else {
                printf("No input has been detected, please retry!\n");
                for (uint8_t i=0; i<6; i++) { 
                    printf("\n");
                    continue;
                }
            }

        }
        else {
            continue;
        }

    
    }
    return 0;
}  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "registers.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#define ADDRESS_LENGTH 8 //32 bits address
#define MSG_LENGTH 8 //32 bits input

// initialize buffer
char addr[10] = {'0'}; // store 8 bytes hex number = 32 bits binary number
char msg[9] = {'0'}; // store 8 bytes hex number = 32 bits binary number
ADDRESS address;
VALUE value = 0;
uint32_t hex_addr; // addr convertor
uint32_t hex_msg = 0; // msg convertor

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

void access_register(char a[10]){
    uint idx = 0;
    printf("What register would you like to access?\n");
    while(1){
        char c = getchar_timeout_us(200);
        if (c == 0x0D){
            //a[idx] = 0;
            printf("\n");
            return;
        }
        if ((c >= 0x20) && (c <= 0x7E)){
            printf("%c", c);
            if (idx < 10){
                a[idx++] = c;
            }
        }
    }

}

void input_value(char b[8]){
    uint idx = 0;
    printf("What value would you like to input?\n");
    while(1){
        char c = getchar_timeout_us(200);
        if (c == 0x0D){
            printf("\n");
            return;
        }
        if ((c >= 0x20) && (c <= 0x7E)){
            printf("%c", c);
            if (idx < 8){
                b[idx++] = c;
            }
        }
    }
}

void Rread(){
    Register_status status;
    access_register(addr);
    int flag = sscanf(addr, "%x", &hex_addr);
        if(flag == 1){
            printf("Sscanf status: %d\n", flag);
            printf("The hex address is: %x\n", hex_addr);
            address = (ADDRESS) hex_addr;
            status.reg_address = hex_addr;
        }else{
            printf("sscanf faild");
        }
    
    value = register_read(address);
    status.reg_value = value;
    render_to_console(status);

}

void Rwrite(){
    Register_status status;
    access_register(addr);
    int flag = sscanf(addr, "%x", &hex_addr);
        if(flag == 1){
            printf("Sscanf status: %d\n", flag);
            printf("The hex address is: %x\n", hex_addr);
            address = (ADDRESS) hex_addr;
            status.reg_address = hex_addr;
        }else{
            printf("sscanf faild");
        }
    input_value(msg);
    hex_msg = (VALUE)strtol(msg, NULL, 16);
    printf("Start write:\n");
    register_write(address,hex_msg);
    status.reg_value = hex_msg;
    render_to_console(status);
}

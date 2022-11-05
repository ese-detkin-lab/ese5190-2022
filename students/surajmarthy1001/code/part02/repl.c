#include "stdlib.h"
#include "hardware/regs/addressmap.h"
#include "sio.h"
#include "irq.h"
#include "gpio.h"

// function select any 32-bit address to read/write (even if not a valid RP2040 address) from console
uint32_t read_write_address(uint32_t address) {
    printf("Enter address to read/write: ");
    scanf("%d", &address);//change
    printf("Address: %d\n", address);//change
    return address;
}

// function to ask the user for read/write operation
// have to write code for this


int main() {
    stdio_init_all();
    printf("Hello, world!\n");

    uint32_t address = 0;
    while (true) {
        address = read_write_address(address); //this takes the address from console to read/write
      //have to write rest of the code 

    }
}

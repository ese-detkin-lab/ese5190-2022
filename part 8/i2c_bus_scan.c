#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pio_i2c.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#include "registers.h"
#include "adps_registers.h"
#include "adafruit_qtpy_rp2040.h"

#define PIN_SDA 22
#define PIN_SCL 23

bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

void configure_adps(PIO pio, uint sm){
    // ADPS ON
    uint8_t tx_buffer[2] = {0};

    // 256 - 50(Color Integration time) = 0xCE
    tx_buffer[0] = ATIME_REGISTER;
    tx_buffer[1] = (uint8_t)(0x81);
    pio_i2c_write_blocking(pio, sm, ADPS_ADDRESS, tx_buffer, 2);

    //Cotrol Register Configure
    tx_buffer[0] = ADPS_CONTROL_ONE_REGISTER;
    tx_buffer[1] = ADPS_CONTROL_ONE_AGAIN;
    pio_i2c_write_blocking(pio, sm, ADPS_ADDRESS, tx_buffer, 2);

    tx_buffer[0] = ADPS_ENABLE_REGISTER;
    tx_buffer[1] = ADPS_ENABLE_PON | ADPS_ENABLE_AEN | ADPS_ENABLE_PEN;
    pio_i2c_write_blocking(pio, sm, ADPS_ADDRESS, tx_buffer, 2);
}

void adps_read_value(PIO pio, uint sm, uint8_t reg_addr, uint8_t *rx_buffer, uint num_bytes) {
    // Read reg_addr.
    pio_i2c_write_blocking(pio, sm, ADPS_ADDRESS, &reg_addr, 1);  
    pio_i2c_read_blocking(pio, sm, ADPS_ADDRESS, rx_buffer, num_bytes);
}

int main() {
    stdio_init_all();

    PIO pio = pio0;
    uint sm = 0;
    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, PIN_SDA, PIN_SCL);
    
    while(!stdio_usb_connected());

    printf("Welcome to PIO I2C ADPS9960\n");
    
    // ADPS Sensor Configure
    configure_adps(pio, sm);

    while(1) {
        
        // To read values from ALS and Proximity engine check status register
        uint8_t rx_buffer[1] = {0};
        adps_read_value(pio, sm, STATUS_REGISTER, rx_buffer, 1);
        adps_read_value(pio, sm, ID_REGISTER, rx_buffer, 1);

        // Mask to check Proximity and color data to read
        uint8_t data_arr[8] = {0};
        if ((rx_buffer[0] & STATUS_REGISTER_PVALID) == STATUS_REGISTER_PVALID) {
            adps_read_value(pio, sm, PROXIMITY_DATA_REGISTER, data_arr, 1);
            printf("Proximity Value : %d\n", data_arr[0]);
        } 
        if ((rx_buffer[0] & STATUS_REGISTER_AVALID) == STATUS_REGISTER_AVALID) {
            adps_read_value(pio, sm, RGBC_DATA_REGISTER_CDATAL, data_arr, 8);
            uint16_t c_val = (data_arr[1] << 8 | data_arr[0]); 
            uint16_t r_val = (data_arr[3] << 8 | data_arr[2]); 
            uint16_t g_val = (data_arr[5] << 8 | data_arr[4]); 
            uint16_t b_val = (data_arr[7] << 8 | data_arr[6]); 
            printf("Color Values : (%d, %d, %d, %d)\n", r_val, g_val, b_val, c_val);
        }
        sleep_ms(500); 
    }
    return 0;
}
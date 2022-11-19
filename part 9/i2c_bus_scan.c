#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "apds_registers.h"
#include "hardware/pio.h"
#include "ws2812.h"
#include "registers.h"
#include "adafruit_qtpy_rp2040.h"
#include "hardware/clocks.h"
#include "pio_i2c.h"
#include "ws2812.pio.h"

#define PIN_SDA 22
#define PIN_SCL 23

#define IS_RGBW true
#define NUM_PIXELS 150
#define PICO_DEFAULT_WS2812_POWER_PIN 11

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 2
#endif

void put_pixel(uint32_t color){
    uint32_t r = color >> 16;
    uint32_t g = color << 16;
    g = g >> 24;
    uint32_t b = color << 24;
    b = b >> 24;
    uint32_t final_color = ((r << 8) |
                            (g << 16)|
                            (b ));
    pio_sm_put_blocking(pio0, 0, final_color << 8u);
}

void configure_adps(PIO pio, uint sm){
   // ADPS ON
    uint8_t tx_buffer[2] = {0};

    // 256 - 50(Color Integration time) = 0xCE
    tx_buffer[0] = ATIME_REGISTER;
    tx_buffer[1] = (uint8_t)(0x81);
    pio_i2c_write_blocking(pio, sm, APDS_ADDRESS, tx_buffer, 2);

    //Cotrol Register Configure
    tx_buffer[0] = APDS_CONTROL_ONE_REGISTER;
    tx_buffer[1] = APDS_CONTROL_ONE_AGAIN;
    pio_i2c_write_blocking(pio, sm, APDS_ADDRESS, tx_buffer, 2);

    tx_buffer[0] = APDS_ENABLE_REGISTER;
    tx_buffer[1] = APDS_ENABLE_PON | APDS_ENABLE_AEN | APDS_ENABLE_PEN;
    pio_i2c_write_blocking(pio, sm, APDS_ADDRESS, tx_buffer, 2);
}

void adps_read_value(PIO pio, uint sm, uint8_t reg_addr, uint8_t *rx_buffer, uint num_bytes) {
    // Read reg_addr.
    pio_i2c_write_blocking(pio, sm, APDS_ADDRESS, &reg_addr, 1);  
    pio_i2c_read_blocking(pio, sm, APDS_ADDRESS, rx_buffer, num_bytes);
}

uint32_t read_prox_and_color(PIO pio, uint sm){
    // Check the status register, to know if we can read the values from the ALS and Proximity engine.
    uint8_t rx_buffer[1] = {0};
    adps_read_value(pio, sm, STATUS_REGISTER, rx_buffer, 1);
    adps_read_value(pio, sm, ID_REGISTER, rx_buffer, 1);

    uint16_t c_value = 0;
    uint16_t r_value = 0;
    uint16_t g_value = 0;
    uint16_t b_value =0;

    //checking if our Proximity and color data is ready to be read.
    uint8_t data_arr[8] = {0};
    if ((rx_buffer[0] & STATUS_REGISTER_PVALID) == STATUS_REGISTER_PVALID) {
        adps_read_value(pio, sm, PROXIMITY_DATA_REGISTER, data_arr, 1);
        printf("Proximity Value : %d\n", data_arr[0] - 230);
    } 
    if ((rx_buffer[0] & STATUS_REGISTER_AVALID) == STATUS_REGISTER_AVALID) {
        adps_read_value(pio, sm, RGBC_DATA_REGISTER_CDATAL, data_arr, 8);
        c_value = (data_arr[1] << 8 | data_arr[0]); 
        r_value = (data_arr[3] << 8 | data_arr[2]); 
        g_value = (data_arr[5] << 8 | data_arr[4]); 
        b_value = (data_arr[7] << 8 | data_arr[6]); 
        printf("Color Value : (%d, %d, %d, %d)\n", r_value, g_value, b_value, c_value);
    }
    uint32_t final_color_packet = 0;
    if ((r_value> g_value) && (r_value > b_value)) {
        final_color_packet = ((uint8_t)((r_value*255) / 65536) << 16);
    } else if ((g_value > r_value) && (g_value > b_value)) {
        final_color_packet = ((uint8_t)((g_value*255) / 65536) << 8);
    } else if ((b_value > r_value) && (b_value > r_value)) {
        final_color_packet = (uint8_t)((b_value*255) / 65536);
    }
    return final_color_packet;
}

int main() {
    const uint POWER_PIN_NAME = PICO_DEFAULT_WS2812_POWER_PIN;
    gpio_init(POWER_PIN_NAME);
    gpio_set_dir(POWER_PIN_NAME, GPIO_OUT);
    gpio_put(POWER_PIN_NAME, 1);
    stdio_init_all();
    
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    PIO pio_1 = pio0;
    uint sm_1 = 1;
    uint offset_1 = pio_add_program(pio_1, &i2c_program);
    i2c_program_init(pio_1, sm_1, offset_1, PIN_SDA, PIN_SCL);
    
    // Wait until USB is connected.
    while(!stdio_usb_connected());

    printf("Welcome to PIO I2C ADPS9960\n");;

    configure_adps(pio_1, sm_1);
    
    uint32_t color_data_value = 0;

    while(1) {
    
        color_data_value = read_prox_and_color(pio_1, sm_1);
        printf("Color Packet Value: 0x%06x\n", color_data_value);
        put_pixel(color_data_value);
        sleep_ms(500);
        put_pixel(0);
    }
 
    return 0;
}

/*
We can now actually measure the timings you modeled in the last lab. 
Add APDS9960 support to your sensor, then set your system 
up to capture the following timing info:

* color packet delivered to PIO module
* bit delivered to WS2812 (24x/packet)
* full packet delivered to WS2812
* brightness changed on APDS

Run the experiment in both dark and light room settings 
(record initial ambient brightness in each case). 
The Neopixel should start 'off' and the ADPS9960 should be initialized with 
your preferred sampling rate (you may want to try a few different rates). 
Run the experiment for at least 100 samples at brightness settings of 0%, 25%, 50%, 75%, 100% 
(making sure to give the ADPS reading enough time to 'settle' each time Neopixel is turned off).

Report the observed 'jitter' based on misalignment with the free-running PWM module on the WS2812.
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "string.h"
#include "APDS9960.h"
#include "pio_i2c.h"


#define POWER_ENABLE 1
#define PROXIMITY_ENABLE 1
#define ALS_ENABLE 1
#define GESTURE_ENABLE 0

#define ALS_GAIN 0
#define ALS_TIME 219

#define INIT_CONFIG (GESTURE_ENABLE << 6u) | (PROXIMITY_ENABLE << 2u) | (ALS_ENABLE << 1u) | POWER_ENABLE

const int addr = 0x39;
const int max_read = 250;

#define PIN_SDA 22
#define PIN_SCL 23



void APDS9960_init(PIO pio, uint sm) {
    // use the "handheld device dynamic" optimal setting (see datasheet)
    uint8_t buf[2];

    // send register number followed by its corresponding value
    buf[0] = ENABLE_REG;
    buf[1] = INIT_CONFIG;
    pio_i2c_write_blocking(pio, sm, addr, buf, 2, false);

    buf[0] = ALS_TIME_REG;
    buf[1] = ALS_TIME;
    pio_i2c_write_blocking(pio, sm, addr, buf, 2, false);
}

void read_proximity(PIO pio, uint sm, int32_t* proximity) {

    uint8_t buf[1];
    uint8_t reg = PDATA_REG;
    pio_i2c_write_blocking(pio, sm, addr, &reg, 1, true);  // true to keep master control of bus
    pio_i2c_read_blocking(pio, sm, addr, buf, 1, false);  // false - finished with bus

    *proximity = buf[0];
}

void read_rgbc(PIO pio, uint sm, int32_t* r, int32_t* g, int32_t* b, int32_t* c) {

    uint8_t buf[2];
    uint8_t reg = CDATA_REG_L;
    pio_i2c_write_blocking(pio, sm, addr, &reg, 1, true);  // true to keep master control of bus
    pio_i2c_read_blocking(pio, sm, addr, buf, 8, false);  // false - finished with bus

    *c = (buf[1] << 8) | buf[0];
    *r = (buf[3] << 8) | buf[2];
    *g = (buf[5] << 8) | buf[4];
    *b = (buf[7] << 8) | buf[6];
}

/*    
int main() {
    stdio_init_all();

    uint offset = pio_add_program(pio, &i2c_program);
    i2c_program_init(pio, sm, offset, PIN_SDA, PIN_SCL);

    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    
    //gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    //gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    //gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    //gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);


    sleep_ms(5000);

    PIO pio = pio0;
    uint sm = 0;

    APDS9960_init(pio, sm);
    printf("Hello, APDS9960! Reading raw data from module...\n");

    while (true) {
        
        int32_t proximity;
        int32_t r,g,b,c;

        read_proximity(pio, sm, &proximity);
        read_rgbc(pio, sm, &r, &g, &b, &c);

        printf("proximity: %d   ",proximity);
        printf("r:%d, g:%d, b:%d, c:%d\n", r, g, b, c);

        // Wait for data to refresh
        //sleep_ms(1000);

    }
}
*/
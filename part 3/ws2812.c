#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "adafruit_qtpy_rp2040.h"
#define IS_RGBW true
#define NUM_PIXELS 150

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
#define WS2812_PIN 2
#endif
#define PICO_DEFAULT_WS2812_POWER_PIN 11
#define QTPY_BOOT_PIN 21
const uint boot_pin = QTPY_BOOT_PIN;

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

typedef struct{
    uint32_t statval;
} status;

void replay(int *data);

void record(int *data){
   for(int i=0; i<5000; i++){
		sleep_ms(2);
		if(gpio_get(boot_pin)==0)
			data[i] = 1;
        else 
            data[i] = 0;
	}
	sleep_ms(1000);
    replay(data);
}

void replay(int *data){
    for(int i=0; i<5000; i++){
		sleep_ms(1);
		if(data[i] == 1){
			put_pixel(0xFF0000);
			printf("%d", 1);
		} 
        else{
			put_pixel(0x000000);
			printf("%d", 0);
			}
        put_pixel(0x000000);
	    sleep_ms(1);
		}
	printf("\n");
}

int main() {
    const uint POW_PIN = PICO_DEFAULT_WS2812_POWER_PIN;
    gpio_init(POW_PIN);
    gpio_set_dir(POW_PIN, GPIO_OUT);
    gpio_put(POW_PIN,1);
    stdio_init_all();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    status stat;
    stat.statval = 0x00000000;

    int data[5000];

    while (1) {
        char option;
        scanf("%c",&option);
        if (option=='r')
            record(data);
        else if (option == 'p')
            replay(data);
    }
}
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "ws2812.pio.h"
#include "adafruit_qtpy_rp2040.h" 
#include "registers.h"
#include "neopixel.h"

#define QTPY_BOOT_PIN 21
#define E_READ      'r'
#define E_WRITE     'w'
#define E_RGB       'c'
#define E_READIO    '<'
#define E_SETPIN    'p'
#define E_WRITEIO   '>'

int g_Pin; // default read pin

void funcRead(){
    ADDRESS address;
    VALUE readVal;
    scanf("%x", &address);
    readVal = register_read(address);
    printf("v%08x", readVal);
}
void funcWrite(){
    ADDRESS address;
    VALUE writeVal;
    scanf("%08x", &address);
    scanf("%08x", &writeVal);
    register_write(address, writeVal);
}

// neopixel_set_rgb()
void funcRGB(){
    VALUE rgbVal;
    scanf("%x", &rgbVal);
    uint32_t grb = ((rgbVal & 0xFF0000) >> 8) | ((rgbVal & 0x00FF00) << 8) | (rgbVal & 0x0000FF);
    pio_sm_put_blocking(pio0, 0, grb << 8u);
    printf("v%08x", rgbVal);
}

void funcSetPin(){
    scanf("%d", &g_Pin);
}

void funcGpioRead(){
    int pin = 0;  // must use type int (not uint_8) and %d in scanf
    scanf("%d", &pin);
    int res = gpio_get(pin);
    printf("o%d", res);
    if(res == 1) {
        neopixel_set_rgb(0x00000f0f);
    } else {
        neopixel_set_rgb(0x00000000);
    }
}

void funcGpioReadDefault(){
    printf("o%d", gpio_get(g_Pin));
}

void funcPIOWrite(){
    char value = 0xff;
    value = getchar_timeout_us(0);
    // scanf("%d",&value);  
    if(value == '1'){
        neopixel_set_rgb(0x000000ff);  
    }
    else if(value == '0'){
        neopixel_set_rgb(0x0000ff00);
    }
}

int main() {
    stdio_init_all();
    while(stdio_usb_connected() != true);

    gpio_init(QTPY_BOOT_PIN);
    gpio_set_dir(QTPY_BOOT_PIN, GPIO_IN);
    neopixel_init();

    uint8_t event = 0;

    while(1 > 0){
        event = getchar_timeout_us(0);
        if(event == E_READ){
            neopixel_set_rgb(0x000000ff);   //blue
            funcRead();
        }
        else if(event == E_WRITE){
            neopixel_set_rgb(0x0000ff00);   //green
            funcWrite();
        }
        else if(event == E_RGB){
            neopixel_set_rgb(0x00ff0000);   // red
            funcRGB();
        }
        else if(event == E_READIO){
            neopixel_set_rgb(0x00000f0f);   // yellow
            funcGpioReadDefault();
        }
        else if(event == E_SETPIN){
            funcSetPin();
        }
        else if(event == E_WRITEIO){
            funcPIOWrite();
        }
    }
    return 0;
}  

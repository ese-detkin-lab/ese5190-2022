cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(pio_logic_analyser C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


add_executable(ws2812)

target_sources(ws2812 PRIVATE ws2812.c registers.h)

target_link_libraries(ws2812 PRIVATE pico_stdlib hardware_pio hardware_dma)
pico_add_extra_outputs(ws2812)

pico_enable_stdio_usb(ws2812 1)
pico_enable_stdio_uart(ws2812 0)

# add url via pico_set_program_url
# example_auto_set_url(ws2812)

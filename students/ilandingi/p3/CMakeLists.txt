cmake_minimum_required(VERSION 3.13) # CMAKE (heading)
include(pico_sdk_import.cmake) # CMAKE -> PICO SDK (include)

project(part3 C CXX ASM) # CMAKE ("project")
pico_sdk_init() # PICO SDK (initialization)

add_executable(part3) # CMAKE (target)

pico_generate_pio_header(part3 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated) # PICO SDK (PIO)

target_sources(part3 PRIVATE part3.c register.h neopixel.c)

target_link_libraries(part3 PRIVATE pico_stdlib hardware_pio) # CMAKE -> C linker)

pico_enable_stdio_usb(part3 1) # PICO SDK (USB)
pico_enable_stdio_uart(part3 0) # PICO SDK (USB)

pico_add_extra_outputs(part3) # PICO SDK (UF2)

cmake_minimum_required(VERSION 3.13) # CMAKE (heading)
include(pico_sdk_import.cmake) # CMAKE -> PICO SDK (include)

project(Flashlight C CXX ASM) # CMAKE ("project")
pico_sdk_init() # PICO SDK (initialization)

add_executable(flashlight) # CMAKE (target)

pico_generate_pio_header(flashlight ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated) # PICO SDK (PIO)

target_sources(flashlight PRIVATE main.c neopixel.c) # CMAKE -> C (compiler)
# target_sources(flashlight PRIVATE flashlight.c neopixel.c) # CMAKE -> C (compiler)

target_link_libraries(flashlight PRIVATE pico_stdlib hardware_pio) # CMAKE -> C (linker)

pico_enable_stdio_usb(flashlight 1) # PICO SDK (USB)
pico_enable_stdio_uart(flashlight 0) # PICO SDK (USB)

pico_add_extra_outputs(flashlight) # PICO SDK (UF2)

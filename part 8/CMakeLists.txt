cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(lab_2b_p8 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()


add_executable(pio_i2c_bus_scan)

pico_generate_pio_header(pio_i2c_bus_scan ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)

pico_enable_stdio_usb(pio_i2c_bus_scan 1)
pico_enable_stdio_uart(pio_i2c_bus_scan 0)

target_sources(pio_i2c_bus_scan PRIVATE
        i2c_bus_scan.c
        pio_i2c.c
        pio_i2c.h
        registers.h
        adps_registers.h
        )

target_link_libraries(pio_i2c_bus_scan PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_i2c_bus_scan)

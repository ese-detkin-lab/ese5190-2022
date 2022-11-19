cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(adps_protocol C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(pio_i2c_bus_scan)

pico_generate_pio_header(pio_i2c_bus_scan ${CMAKE_CURRENT_LIST_DIR}/i2c.pio ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)
pico_generate_pio_header(pio_i2c_bus_scan ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

pico_enable_stdio_usb(pio_i2c_bus_scan 1)
pico_enable_stdio_uart(pio_i2c_bus_scan 0)

target_sources(pio_i2c_bus_scan PRIVATE
        i2c_bus_scan.c
        pio_i2c.c
        pio_i2c.h
        registers.h
        apds_registers.h
        ws2812.h
        )

# add_custom_target(pio_i2c_bus_scan DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py)
# add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
#         DEPENDS ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
#         COMMAND Pioasm -o python ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
#         )
# add_dependencies(pio_i2c_bus_scan pio_ws2812_datasheet)
target_link_libraries(pio_i2c_bus_scan PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_i2c_bus_scan)

cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(pico_examples C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})
set(PICO_BOARD "adafruit_qtpy_rp2040")
# Initialize the SDK
pico_sdk_init()

# include(example_auto_set_url.cmake)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_executable(pio_logic_analyser)

target_sources(pio_logic_analyser PRIVATE logic_analyser.c)

target_link_libraries(pio_logic_analyser PRIVATE pico_stdlib hardware_pio hardware_dma hardware_i2c)

pico_enable_stdio_usb(pio_logic_analyser 1) # PICO SDK (USB)
pico_enable_stdio_uart(pio_logic_analyser 0) # PICO SDK (USB)

pico_add_extra_outputs(pio_logic_analyser) # PICO SDK (UF2)

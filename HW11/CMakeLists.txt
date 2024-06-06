<<<<<<< HEAD
cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(nick_pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NICK_PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
pico_sdk_init()

# Add multi example
add_subdirectory(5mp)
add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )
=======
add_executable(rp2040
        pwm.c
        ssd1306.c
        )

# pull in common dependencies
target_link_libraries(rp2040 pico_stdlib hardware_adc hardware_i2c hardware_pwm hardware_uart)
pico_enable_stdio_usb(rp2040 1)
pico_enable_stdio_uart(rp2040 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(rp2040)

>>>>>>> 587293daeef592ade73198da7b20966a49335ce3

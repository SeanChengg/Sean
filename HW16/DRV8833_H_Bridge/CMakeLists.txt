cmake_minimum_required(VERSION 3.13)

# Pull in the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

add_executable(DRV8833_H_Bridge
    main.c
)

target_sources(DRV8833_H_Bridge PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/main.c
)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(DRV8833_H_Bridge PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(DRV8833_H_Bridge PUBLIC
    pico_stdlib
    hardware_adc
    hardware_i2c
    hardware_pwm
    hardware_uart
)

pico_enable_stdio_usb(DRV8833_H_Bridge 1)
pico_enable_stdio_uart(DRV8833_H_Bridge 0)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

pico_add_extra_outputs(DRV8833_H_Bridge)

# add url via pico_set_program_url
# example_auto_set_url(imu)
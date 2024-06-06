cmake_minimum_required(VERSION 3.13)

# Pull in the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

add_executable(imu
    mpu6050.c # main.c
    usb_descriptors.c
)

target_sources(imu PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/mpu6050.c
    ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(imu PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(imu PUBLIC
    pico_stdlib
    hardware_adc
    hardware_i2c
    hardware_pwm
    hardware_uart
    pico_unique_id
    tinyusb_device
    tinyusb_board
)

pico_enable_stdio_usb(imu 1)
pico_enable_stdio_uart(imu 0)

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

pico_add_extra_outputs(imu)

# add url via pico_set_program_url
# example_auto_set_url(imu)
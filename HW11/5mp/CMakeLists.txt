add_executable(rp2040
        5mp.c
        )

# pull in common dependencies
target_link_libraries(5mp pico_stdlib hardware_adc hardware_i2c hardware_pwm hardware_uart)
pico_enable_stdio_usb(5mp 1)
pico_enable_stdio_uart(5mp 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(5mp)


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


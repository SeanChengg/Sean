add_executable(rpizerow
        uart.c
        ssd1306.c
        )

# pull in common dependencies
target_link_libraries(rpizerow pico_stdlib hardware_adc hardware_i2c hardware_uart)
pico_enable_stdio_usb(rpizerow 1)
pico_enable_stdio_uart(rpizerow 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(rpizerow)


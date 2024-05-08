add_executable(cp2102n
        uart.c
        ssd1306.c
        )

# pull in common dependencies
target_link_libraries(cp2102n pico_stdlib hardware_adc hardware_i2c hardware_uart)
pico_enable_stdio_usb(cp2102n 1)
pico_enable_stdio_uart(cp2102n 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(cp2102n)


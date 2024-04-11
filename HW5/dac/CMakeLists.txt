add_executable(dac
        dac.c
        )

# pull in common dependencies
target_link_libraries(dac pico_stdlib hardware_adc hardware_spi)
pico_enable_stdio_usb(dac 1)
pico_enable_stdio_uart(dac 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(dac)


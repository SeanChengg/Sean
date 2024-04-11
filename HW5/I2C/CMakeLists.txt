add_executable(I2CMCP23008
I2CMCP23008.c
        )

# pull in common dependencies
target_link_libraries(I2CMCP23008 pico_stdlib hardware_adc hardware_spi hardware_i2c)
pico_enable_stdio_usb(I2CMCP23008 1)
pico_enable_stdio_uart(I2CMCP23008 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(I2CMCP23008)


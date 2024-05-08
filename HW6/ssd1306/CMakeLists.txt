add_executable(ssd1306
        main.c
        ssd1306.c
        )

# pull in common dependencies
target_link_libraries(ssd1306 pico_stdlib hardware_adc hardware_i2c)
pico_enable_stdio_usb(ssd1306 1)
pico_enable_stdio_uart(ssd1306 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(ssd1306)


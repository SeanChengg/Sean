#include <stdio.h>
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#define GPIO_OUT 1
#define GPIO_IN 0
 // device has default bus address of 0x76
#define ADDR _u(0b0100000)

// hardware registers
#define REG_IODIR _u(0x00)
#define REG_GPIO _u(0x09)
#define REG_OLAT _u(0x0A)
const uint8_t PICO_I2C_SDA_PIN = 8;
const uint8_t PICO_I2C_SCL_PIN = 9;

void mcp23008_init() {
    // use the "handheld device dynamic" optimal setting (see datasheet)
    uint8_t buf[2];

    // send register number followed by its corresponding value
    buf[0] = REG_IODIR;
    buf[1] = 0b01111111;
    i2c_write_blocking(i2c_default, ADDR, buf, 2, false);
}

void set(char s, uint8_t left) {
    // use the "handheld device dynamic" optimal setting (see datasheet)
    uint8_t buf[2];
    // send register number followed by its corresponding value
    buf[0] = REG_OLAT;
    buf[1] = s << left;
    i2c_write_blocking(i2c_default, ADDR, buf, 2, false);
}

uint read_gpio() {
    uint8_t buf[1];
    uint8_t reg = REG_GPIO;
    i2c_write_blocking(i2c_default, ADDR, &reg, 1, true);  // true to keep master control of bus
    i2c_read_blocking(i2c_default, ADDR, buf, 1, false);  // false - finished with bus

    if (buf[0]&0b1==0b1){
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    stdio_init_all();

    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("MCP23008_Start!\n");

    const uint LED = 25;
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    // I2C is "open drain", pull ups to keep signal high when no data is being sent
    i2c_init(i2c_default, 100 * 1000);
    gpio_init(PICO_I2C_SDA_PIN);
    gpio_init(PICO_I2C_SCL_PIN);
    gpio_set_function(PICO_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_I2C_SCL_PIN, GPIO_FUNC_I2C);

    mcp23008_init(); // gp7 is output, gp0 is input 


    sleep_ms(250); // sleep so that data polling and register update don't collide
    while (1) {
        //blink gpio25
        gpio_put(LED, 1);
        sleep_ms(100);
        gpio_put(LED, 0);
        sleep_ms(100);

        
        if(read_gpio() == 1){// read from gp0
        // if gp0 is high 
            set(1, 7);//set gp7 high
        } else {
            set(0, 7);// set gp7 low
            printf("GPIO0_LOW!\n");
        }
        sleep_ms(250);
    }
}

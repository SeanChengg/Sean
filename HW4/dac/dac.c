#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define GPIO_OUT 1
#define GPIO_IN 0

const uint PICO_SPI_SCK_PIN = 2;
const uint PICO_SPI_TX_PIN = 3;
const uint PICO_SPI_CSN_PIN = 5;

static uint16_t sine_wave[50];
static uint16_t triangle_wave[100];

void generate_tri_waves();
void generate_sine_waves();
static void write_register(uint8_t reg, uint8_t data);
static void write_analog_value(uint8_t waveform_select, int i);
static inline void cs_select();
static inline void cs_deselect();

void generate_sine_waves() {
    const uint16_t dac_max = 1023;  // maximum value that the 10-bit DAC can accept
    //const uint16_t dac_min = 0;
    
        for (int i = 0; i < 50; i++) {
        float radians = sin(M_PI * 2 * ((float)i / 49)); //calculates the sine value for that angle, which ranges from -1 to 1. First alculates the fraction of the complete cycle for each sample index i. It ranges from 0 (0/49) to 1 (49/49) in steps of 1/49. Converts this fraction to an angle in radians by multiplying it with 2π
        sine_wave[i] = (radians + 1) * dac_max / 2;// shifts the sine values from the range [-1, 1] to the range [0, 2]. scales the shifted sine values to the range [0, dac_max], where dac_max is the maximum value that the DAC can accept
        }
    }
void generate_tri_waves(){
    const uint16_t dac_max = 1023;
    uint16_t step = dac_max / 50;// calculates the increment or decrement value for each sample, such that the wave goes from 0 to dac_max and back to 0 in 100 samples
        for (int i = 0; i < 50; i++) {
        triangle_wave[i] = step * i;// generates the increasing part of the triangle wave by multiplying the step value with the sample index i
        }
        for (int i = 0; i < 50; i++){
        triangle_wave[50+i] = dac_max - step * i;// generates the decreasing part of the triangle wave by subtracting the step value multiplied by the sample index from dac_max
        }
    }


static void write_register(uint8_t reg, uint8_t data) {
    uint8_t buf[2];
    buf[0] = reg;
    buf[1] = data;
    cs_select();
    spi_write_blocking(spi_default, buf, 2);
    cs_deselect();
}

static void write_analog_value(uint8_t waveform_select, int i) {
    uint16_t analog = 0;

    if (waveform_select == 0) {
        analog |= (triangle_wave[i] << 2);
        analog |= (0b0111 << 12);
    } else {
        if (i < 50) {
            analog |= (sine_wave[i] << 2);
            analog |= (0b1111 << 12);
        } else {
            analog |= (sine_wave[i - 50] << 2);
            analog |= (0b1111 << 12);
        }
    }

    write_register(analog >> 8, analog);
}

static inline void cs_select(void) {
    __asm__ __volatile__("nop \n nop \n nop");
    gpio_put(PICO_SPI_CSN_PIN, 0);
    __asm__ __volatile__("nop \n nop \n nop");
}

static inline void cs_deselect(void) {
    __asm__ __volatile__("nop \n nop \n nop");
    gpio_put(PICO_SPI_CSN_PIN, 1);
    __asm__ __volatile__("nop \n nop \n nop");
}
int main() {
    stdio_init_all();
        while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("Start!\n");

    const uint LED_PIN = 15;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    spi_init(spi_default, 12 * 1000); // SPI at 12kHz
    gpio_set_function(PICO_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_SPI_TX_PIN, GPIO_FUNC_SPI);
 
    gpio_init(PICO_SPI_CSN_PIN);
    gpio_set_dir(PICO_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(PICO_SPI_CSN_PIN, 1);

    generate_sine_waves();
    generate_tri_waves();
    static uint16_t analog = 0;
    while (1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);

        for (int i = 0; i < 100; i++) {
            write_analog_value(1, i); // Write sine wave
            write_analog_value(0, i); // Write triangle wave
            sleep_ms(1000/100);
        }
    }

    return 0;
}

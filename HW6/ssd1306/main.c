#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "ssd1306.h"
#include "font.h"
#define ADC_RANGE 4090
const uint8_t PICO_I2C_SCL_PIN = 21;
const uint8_t PICO_I2C_SDA_PIN = 20;

//int i = 0;
//char message[50];
//sprintf(message, "hello %d", i);
void drawChar(int x, int y, char letter){
    for (int i = 0; i < 5 ; i++){
        char c = ASCII[letter-32][i]; // c represent column of pixel
        for (int j = 0; j < 8; j++){
            char bit = (c >> j) & 0b1;

            if(bit == 0b1){
                ssd1306_drawPixel(x+i,y+j,1);
            }
            else {
                ssd1306_drawPixel(x+i,y+j,0);
            }
        }
    }
}

void ssd1306_drawString(int x, int y, char * m){
    int i = 0;
    while(m[i]){
        drawChar(x+i*5,y,m[i]);
        i++;
    }
    // ssd1306_update();
}

int main() {
    stdio_init_all();
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("SSD1306_Start!\n");
    // default LED
    const uint LED = 25;
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    //ADC value
    adc_init(); // init the adc module
    adc_gpio_init(26); // set ADC0 pin to be adc input instead of GPIO
    adc_select_input(0); // select to read from ADC0

    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_I2C_SCL_PIN, GPIO_FUNC_I2C);

    ssd1306_setup();
    int i = 0;
    char message[100];
    while(1){
        //blink gpio25
        gpio_put(LED, 1);
        sleep_ms(100);
        gpio_put(LED, 0);
        sleep_ms(100);
        
        // for(int j = 1; j <= 25; j++){
        //     for (int k = 1; k <= 4; k++){
        //         sprintf(message, "%c", '$');
        //         ssd1306_drawString(1,1, message);
        //         ssd1306_drawString(1,k*8, message);
        //         ssd1306_drawString(j*5,1, message);
        //         ssd1306_update();
        //         ssd1306_drawString(j*5,k*8, message);
        //         ssd1306_update();
        //     }
        // }
        unsigned int start = to_us_since_boot(get_absolute_time());
        // sprintf(message, "i = %d", i);
        // ssd1306_drawString(1,1,message);
        // ssd1306_update();
        // i++;
        uint16_t adc_value = adc_read();
        sprintf(message, "ADC = %.3f V", (adc_value*30.3)/ADC_RANGE);
        ssd1306_drawString(0,0,message);
        ssd1306_update();
        
        unsigned int stop = to_us_since_boot(get_absolute_time());
        unsigned int t = stop - start;
        sprintf(message, "FPS = %f", 1000000.0/t);
        ssd1306_drawString(0,16,message);
        ssd1306_update();
        sleep_ms(250);
    }


    sleep_ms(250); // sleep so that data polling and register update don't collide
}

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/time.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "ssd1306.h"
#include "font.h"
#define SERVO 22 // the built in LED on the Pico
#define LED 25
#define ADC_RANGE 4090
#define UART_ID uart1
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1

static int chars_rxed = 0;
volatile int i = 0;
volatile char m [100];
const uint8_t PICO_I2C_SCL_PIN = 21;
const uint8_t PICO_I2C_SDA_PIN = 20;

uint slice_num;
uint16_t wrap;
uint16_t servo_min_level;
uint16_t servo_max_level;

void intialize_servo_pwm(){
    gpio_set_function(SERVO, GPIO_FUNC_PWM); // Set the LED Pin to be PWM
    slice_num = pwm_gpio_to_slice_num(SERVO); // Get PWM slice number
    float div = 40; // must be between 1-255
    pwm_set_clkdiv(slice_num, div); // divider
    wrap = 62500; // when to rollover, must be less than 65535
    pwm_set_wrap(slice_num, wrap);
    pwm_set_enabled(slice_num, true); // turn on the PWM
    servo_min_level = wrap * 0.028;// set the duty cycle to 2.5%
    servo_max_level = wrap * 0.122;// set the duty cycle to 12.5%
}

void set_servo_angle(float angle){
            if(angle < 0 || angle > 180){
                printf("Invalid number \n");
                return;
            }else{
                uint16_t pwm_level = servo_min_level + ((servo_max_level - servo_min_level)* (angle/180));
                pwm_set_gpio_level(SERVO, pwm_level);
            }
        }

// RX interrupt handler
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
        if(ch == '\n'){
            m[i] = 0;
            i = 0;
            printf("From Zero: %s\n", m);
        }else{
            m[i] = ch;
            i++;
        }
    }
}

int main() {
    stdio_init_all();
    intialize_servo_pwm();
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    // default LED
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    // Set up our UART with a basic baud rate.
    uart_init(UART_ID, 2400);
    // Set the TX and RX pins by using the function select on the GPIO
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
    uart_set_fifo_enabled(UART_ID, false);
    int UART_IRQ = UART1_IRQ;
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);
    uart_set_irq_enables(UART_ID, true, false);
    gpio_init(PICO_I2C_SDA_PIN);
    gpio_init(PICO_I2C_SCL_PIN);
    i2c_init(i2c_default, 100*1000);
    gpio_set_function(PICO_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_I2C_SCL_PIN, GPIO_FUNC_I2C);

   

    while(1){
        //blink gpio25
        gpio_put(LED, 1);
        sleep_ms(100);
        gpio_put(LED, 0);
        sleep_ms(100);

       

        for(float angle = 0; angle < 180; angle ++){
            set_servo_angle(angle);
            sleep_ms(2000/180);
        }

        for(float angle = 180; angle > 0; angle --){
            set_servo_angle(angle);
            sleep_ms(2000/180);
        }

        // int i = 0;
        // char message[100];
        // scanf("%s", &message);
        // printf("Computer sent: %s\n",message);

        // char txm[100];
        // sprintf(txm, "%s\n", message);
        // uart_puts(UART_ID, txm);
        // sleep_ms(250);
        //return 0;
    }
}

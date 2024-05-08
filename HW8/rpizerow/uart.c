#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/time.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "ssd1306.h"
#include "font.h"
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
// volatile int x = 0;
const uint8_t PICO_I2C_SCL_PIN = 21;
const uint8_t PICO_I2C_SDA_PIN = 20;

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
        // if(letter == '\n'){
        //     x = 0
        // } else {
        // drawChar(0,x,ch)
        // x+=5;
        // }
        // if (uart_is_writable(UART_ID)) {
        //     // Change it slightly first!
        //     ch++;
        //     uart_putc(UART_ID, ch);
        // }
        // chars_rxed++;
    }
}

int main() {
    stdio_init_all();
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    //printf("CP2102N_Start!\n");
    
    // default LED
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);

    // Set up our UART with a basic baud rate.
    uart_init(UART_ID, 2400);
    // Set the TX and RX pins by using the function select on the GPIO
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // The call will return the actual baud rate selected, which will be as close as
    // possible to that requested
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART1_IRQ;
    //int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);

    // Initialize SDA and SCL pins on Pico
    gpio_init(PICO_I2C_SDA_PIN);
    gpio_init(PICO_I2C_SCL_PIN);

    // Initialize I2C
    i2c_init(i2c_default, 100*1000);
    gpio_set_function(PICO_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_I2C_SCL_PIN, GPIO_FUNC_I2C);


    while(1){
        //blink gpio25
        gpio_put(LED, 1);
        sleep_ms(100);
        gpio_put(LED, 0);
        sleep_ms(100);


        int i = 0;
        char message[100];
        scanf("%s", &message);
        printf("Computer sent: %s\n",message);

        char txm[100];
        sprintf(txm, "%s\n", message);
        uart_puts(UART_ID, txm);
        sleep_ms(250);
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

// GPIO pins for motor control
#define MOTOR_PWM_L 6   // PWM for left motor
#define MOTOR_IO_L 14    // Direction for left motor
#define MOTOR_PWM_R 7 // PWM for right motor
#define MOTOR_IO_R 15   // Direction for right motor

// Maximum PWM value
#define PWM_WRAP 62500

// Gain curve parameters
#define GAIN_CURVE_CENTER 50
#define GAIN_CURVE_WIDTH 20
#define GAIN_CURVE_MAX_SPEED 100

static volatile int left_duty_cycle, right_duty_cycle;

// The PWM counters use the 125MHz system clock as a source
static const float divider = 1;  // must be between 1-255

void set_motor_duty_cycles(int line_position) {
    int error = line_position - GAIN_CURVE_CENTER;

    // Apply gain curve
    if (abs(error) < GAIN_CURVE_WIDTH) {
        left_duty_cycle = right_duty_cycle = GAIN_CURVE_MAX_SPEED;
    } else {
        int curve_slope = GAIN_CURVE_MAX_SPEED / (100 - GAIN_CURVE_WIDTH);
        left_duty_cycle = GAIN_CURVE_MAX_SPEED - abs(error - GAIN_CURVE_WIDTH) * curve_slope;
        right_duty_cycle = GAIN_CURVE_MAX_SPEED - abs(error + GAIN_CURVE_WIDTH) * curve_slope;
    }

    // Set motor duty cycles
    pwm_set_gpio_level(MOTOR_PWM_L, left_duty_cycle * PWM_WRAP / 100);
    pwm_set_gpio_level(MOTOR_PWM_R, right_duty_cycle * PWM_WRAP / 100);
}

int main() {
    stdio_init_all();
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    // Initialize GPIO pins for left motor
    gpio_init(MOTOR_IO_L);
    gpio_set_dir(MOTOR_IO_L, GPIO_OUT);
    gpio_put(MOTOR_IO_L, false); // Set left motor direction (false for forward)

    // Initialize GPIO pins for right motor
    gpio_init(MOTOR_IO_R);
    gpio_set_dir(MOTOR_IO_R, GPIO_OUT);
    gpio_put(MOTOR_IO_R, false); // Set right motor direction (false for forward)

    // Initialize PWM for left motor
    gpio_set_function(MOTOR_PWM_L, GPIO_FUNC_PWM);
    unsigned int slice_num = pwm_gpio_to_slice_num(MOTOR_PWM_L);
    pwm_set_clkdiv(slice_num, divider);
    pwm_set_wrap(slice_num, PWM_WRAP);
    pwm_set_enabled(slice_num, true);

    // Initialize PWM for right motor
    gpio_set_function(MOTOR_PWM_R, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(MOTOR_PWM_R);
    pwm_set_clkdiv(slice_num, divider);
    pwm_set_wrap(slice_num, PWM_WRAP);
    pwm_set_enabled(slice_num, true);

    while (1) {
        int line_position;

        printf("Enter line position (0-100): \r\n");
        scanf("%d", &line_position);
        set_motor_duty_cycles(line_position);
    }

    return 0;
}





// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/pwm.h"


// // Define pins' functionalities on Pico
// #define LEFT_PWM_PIN 6
// #define RIGHT_PWM_PIN 7
// #define LEFT_IO_PIN 14
// #define RIGHT_IO_PIN 15
// // Define for speed control
// #define LEFT_MOST_LINE 0
// #define RIGHT_MOST_LINE 100
// static int line_threshold = 30;




// // The PWM counters use the 125MHz system clock as a source
// static const float divider = 1;               // must be between 1-255
// static const short unsigned int wrap = 62500; // when to rollover, must be less than 65535
// // Since the speed is related to PWM, and PWM is ranged by wrap,
// // let's assign wrap to full_speed for readability
// static const uint full_speed = wrap;
// static volatile int left_duty_cycle;
// static volatile int right_duty_cycle;


// void calc_duty_cycles(int line_pos);
// bool switch_state(bool state, int button_pin);


// int main()
// {
//    // Initialization
//    stdio_init_all();
//    while (!stdio_usb_connected())
//    {
//        sleep_ms(100);
//    }


//    unsigned int slice_num;
//    // Set PWM for the left motor
//    gpio_set_function(LEFT_PWM_PIN, GPIO_FUNC_PWM);  // Set the PWM pin
//    slice_num = pwm_gpio_to_slice_num(LEFT_PWM_PIN); // Get PWM slice number
//    pwm_set_clkdiv(slice_num, divider);              // Set the clock divider
//    pwm_set_wrap(slice_num, wrap);
//    pwm_set_enabled(slice_num, true); // turn on the PWM
//    // Initialize the GPIO pin for the left motor output
//    gpio_init(LEFT_IO_PIN);
//    gpio_set_dir(LEFT_IO_PIN, GPIO_OUT);
//    // Set PWM for the right motor
//    gpio_set_function(RIGHT_PWM_PIN, GPIO_FUNC_PWM);  // Set the PWM pin
//    slice_num = pwm_gpio_to_slice_num(RIGHT_PWM_PIN); // Get PWM slice number
//    pwm_set_clkdiv(slice_num, divider);               // Set the clock divider
//    pwm_set_wrap(slice_num, wrap);
//    pwm_set_enabled(slice_num, true); // turn on the PWM
//    // Initialize the GPIO pin for the right motor output
//    gpio_init(RIGHT_IO_PIN);
//    gpio_set_dir(RIGHT_IO_PIN, GPIO_OUT);


//    printf("Start!\n");
//    int line_pos;


//    while (true)
//    {
//        gpio_put(LEFT_IO_PIN, 1);

//        // Asks the user to enter a number for motor control,
//        // it between 1 and 100
//        printf("Please enter a number for motor control (between 1 and 100): \r\n");
//        // Reads the number entered by the user
//        scanf("%d", &line_pos);
//        calc_duty_cycles(line_pos);
//        printf("Detected PWM for left: %d, for right: %d\r\n", left_duty_cycle, right_duty_cycle);
//        // Pass the duty cycle calculated and the digital output information to the left wheel

//        pwm_set_gpio_level(LEFT_PWM_PIN, full_speed - left_duty_cycle);
//        // Pass the duty cycle calculated and the digital output information to the left wheel
//        pwm_set_gpio_level(RIGHT_PWM_PIN, right_duty_cycle);
//        gpio_put(RIGHT_IO_PIN, 0);
//    }
//    return 0;
// }


// void calc_duty_cycles(int line_pos)
// {
//    // For the simplest version, the controller is proportional, no derivative or integral terms.
//    // But the curve will be nonlinear
//    float gradient = full_speed / line_threshold;
//    if (line_pos < line_threshold)
//    {
//        left_duty_cycle = gradient * line_pos;
//        right_duty_cycle = full_speed;
//    }
//    else if (line_pos > RIGHT_MOST_LINE - line_threshold)
//    {
//        left_duty_cycle = full_speed;
//        right_duty_cycle = -gradient * line_pos + gradient * RIGHT_MOST_LINE;
//    }
//    else
//    {
//        left_duty_cycle = full_speed;
//        right_duty_cycle = full_speed;
//    }
// }




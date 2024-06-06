#include <stdlib.h>
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
#include "font.h"
#include "ssd1306.h"
#include "bsp/board.h"
#include "tusb_config.h"
#include "usb_descriptors.h"
#include "mpu6050_addr.h"

#define IMU_ARRAY_DATA_LEN 14

const uint8_t PICO_I2C_SCL_PIN = 19;
const uint8_t PICO_I2C_SDA_PIN = 18;

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void led_blinking_task(void);
void hid_task(void);

void imu_init();
void imu_config(uint8_t reg_addr, uint8_t fsr_config);
uint8_t imu_read(uint8_t reg_addr);
uint8_t whoami();
int16_t get_value(uint8_t data[], uint8_t index);
float accel_value(uint8_t data[], uint8_t index);
float gyro_value(uint8_t data[], uint8_t index);
float temp_value(uint8_t data[], uint8_t index);
void burst_read(uint8_t first_reg_addr, uint8_t buf[], uint8_t data_len);
/*------------- MAIN -------------*/
int main(void)
{
  stdio_init_all();
    // while (!stdio_usb_connected()) {
    //     sleep_ms(100);
    // }
  //default LED
  const uint LED = 25;
  gpio_init(LED);
  gpio_set_dir(LED, GPIO_OUT);

  board_init();
  tusb_init();

  i2c_init(i2c_default, 10000);
  gpio_init(PICO_I2C_SDA_PIN);
  gpio_init(PICO_I2C_SCL_PIN);
  gpio_set_function(PICO_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_I2C_SCL_PIN, GPIO_FUNC_I2C);

  imu_init();
  uint8_t whoamI = whoami();
  printf("WHO_AM_I: %d\n", whoamI);
  printf("mpu6050_Start!\n");
  while (1)
  {
    tud_task(); // tinyusb device task
    led_blinking_task();
    hid_task();
  }
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(uint8_t report_id, uint32_t btn)
{
  // skip if hid is not ready yet
  if ( !tud_hid_ready() ) return;

  switch(report_id)
  {
    case REPORT_ID_KEYBOARD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_A;

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    break;

    case REPORT_ID_MOUSE:
    {
      uint8_t imu_buf[IMU_ARRAY_DATA_LEN];
      burst_read(ACCEL_XOUT_H,imu_buf, IMU_ARRAY_DATA_LEN);
        float x_accel = accel_value(imu_buf, 0);
        float y_accel = accel_value(imu_buf, 2);
        float z_accel = accel_value(imu_buf, 4);
        float x_gyro = gyro_value(imu_buf, 8);
        float y_gyro = gyro_value(imu_buf, 10);
        float z_gyro = gyro_value(imu_buf, 12);
      

      // no button, right + down, no scroll, no pan
      tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, 5, 5, 0, 0);
    }
    break;

    case REPORT_ID_CONSUMER_CONTROL:
    {
      // use to avoid send multiple consecutive zero report
      static bool has_consumer_key = false;

      if ( btn )
      {
        // volume down
        uint16_t volume_down = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
        tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_down, 2);
        has_consumer_key = true;
      }else
      {
        // send empty key report (release key) if previously has key pressed
        uint16_t empty_key = 0;
        if (has_consumer_key) tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty_key, 2);
        has_consumer_key = false;
      }
    }
    break;

    case REPORT_ID_GAMEPAD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_gamepad_key = false;

      hid_gamepad_report_t report =
      {
        .x   = 0, .y = 0, .z = 0, .rz = 0, .rx = 0, .ry = 0,
        .hat = 0, .buttons = 0
      };

      if ( btn )
      {
        report.hat = GAMEPAD_HAT_UP;
        report.buttons = GAMEPAD_BUTTON_A;
        tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));

        has_gamepad_key = true;
      }else
      {
        report.hat = GAMEPAD_HAT_CENTERED;
        report.buttons = 0;
        if (has_gamepad_key) tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
        has_gamepad_key = false;
      }
    }
    break;

    default: break;
  }
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void)
{
  // Poll every 10ms
  const uint32_t interval_ms = 10;
  static uint32_t start_ms = 0;

  if ( board_millis() - start_ms < interval_ms) return; // not enough time
  start_ms += interval_ms;

  uint32_t const btn = board_button_read();

  // Remote wakeup
  if ( tud_suspended() && btn )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }else
  {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    send_hid_report(REPORT_ID_KEYBOARD, btn);
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) instance;
  (void) len;

  uint8_t next_report_id = report[0] + 1;

  if (next_report_id < REPORT_ID_COUNT)
  {
    send_hid_report(next_report_id, board_button_read());
  }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance;

  if (report_type == HID_REPORT_TYPE_OUTPUT)
  {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_id == REPORT_ID_KEYBOARD)
    {
      // bufsize should be (at least) 1
      if ( bufsize < 1 ) return;

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
      {
        // Capslock On: disable blink, turn led on
        blink_interval_ms = 0;
        board_led_write(true);
      }else
      {
        // Caplocks Off: back to normal blink
        board_led_write(false);
        blink_interval_ms = BLINK_MOUNTED;
      }
    }
  }
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // blink is disabled
  if (!blink_interval_ms) return;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}




void imu_init(){
  imu_config(PWR_MGMT_1, 0b00);
  imu_config(ACCEL_CONFIG, 0b00);
  imu_config(GYRO_CONFIG, 0b11);
}

void imu_config(uint8_t reg_addr, uint8_t fsr_config){
  uint8_t buf[2] = {reg_addr, fsr_config};
  i2c_write_blocking(i2c_default, MPU6050_ADDR, buf, 2, false);
}

uint8_t imu_read(uint8_t reg_addr){
  uint8_t message;
  i2c_write_blocking(i2c_default, MPU6050_ADDR, &reg_addr, 1, true);
  i2c_read_blocking(i2c_default, MPU6050_ADDR, &message, 1, false);
  return message;
}

uint8_t whoami(){
  return imu_read(WHO_AM_I);
}

int16_t get_value(uint8_t data[], uint8_t index){
  return data[index]  << 8 | data[index +1];
}

float accel_value(uint8_t data[], uint8_t index){
  return get_value(data, index) * 0.000061 ;
}

float gyro_value(uint8_t data[], uint8_t index){
  return get_value(data, index) * 0.007630 ;
}

float temp_value(uint8_t data[], uint8_t index){
  return (get_value(data, index) / 340.00)+36.53 ;
}

void burst_read(uint8_t first_reg_addr, uint8_t buf[], uint8_t data_len){
  i2c_write_blocking(i2c_default, MPU6050_ADDR, &first_reg_addr, 1, true);
  i2c_read_blocking(i2c_default, MPU6050_ADDR, buf, data_len, false);
}








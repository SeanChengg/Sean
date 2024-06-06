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
#include "mpu6050_addr.h"


#define IMU_ARRAY_DATA_LEN 14

const uint8_t PICO_I2C_SCL_PIN = 13;
const uint8_t PICO_I2C_SDA_PIN = 12;

//static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void imu_init();
void imu_config(uint8_t reg_addr, uint8_t fsr_config);
uint8_t imu_read(uint8_t reg_addr);
uint8_t whoami();
int16_t get_value(uint8_t data[], uint8_t index);
float accel_value(uint8_t data[], uint8_t index);
float gyro_value(uint8_t data[], uint8_t index);
float temp_value(uint8_t data[], uint8_t index);
void burst_read(uint8_t first_reg_addr, uint8_t buf[], uint8_t data_len);
void print(uint16_t x_accel, uint16_t y_accel, uint16_t z_accel, uint16_t x_gyro, uint16_t y_gyro, uint16_t z_gyro);

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
void print(uint16_t x_accel, uint16_t y_accel, uint16_t z_accel, uint16_t x_gyro, uint16_t y_gyro, uint16_t z_gyro){
    scanf("X_acceleration_is %f g\n" 
          "Y_acceleration_is %f g\n"
          "Z_acceleration_is %f g\n"
          "X_gyroscope_is %f degree_per_sec\n" 
          "Y_gyroscope_is %f degree_per_sec\n"
          "Z_gyroscope_is %f degree_per_sec\n", x_accel, y_accel, z_accel, x_gyro, y_gyro, z_gyro);
}
int main()
{
   stdio_init_all();
   while (!stdio_usb_connected())
   {
       sleep_ms(100);
   }
    printf("Start!\n");
    const uint LED = 25;
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
   // Initialize SDA and SCL pins on Pico
   gpio_init(PICO_I2C_SDA_PIN);
   gpio_init(PICO_I2C_SCL_PIN);
   gpio_set_function(PICO_I2C_SDA_PIN, GPIO_FUNC_I2C);
   gpio_set_function(PICO_I2C_SCL_PIN, GPIO_FUNC_I2C);

   // Initialize I2C
   i2c_init(i2c_default, 100);

   // Initialize MPU6050
   imu_init();
   // Check WHO_AM_I register
   uint8_t whoAmI = whoami();
   printf("WHO_AM_I: %x\n", whoAmI);

   uint8_t IMU_buf[IMU_ARRAY_DATA_LEN];
   burst_read(ACCEL_XOUT_H, IMU_buf, IMU_ARRAY_DATA_LEN);
   float x_accel = accel_value(IMU_buf, 0);
   float y_accel = accel_value(IMU_buf, 2);
   float z_accel = accel_value(IMU_buf, 4);
   float x_gyro = gyro_value(IMU_buf, 8);
   float y_gyro = gyro_value(IMU_buf, 10);
   float z_gyro = gyro_value(IMU_buf, 12);

   print(x_accel, y_accel, z_accel, x_gyro, y_gyro, z_gyro);
}









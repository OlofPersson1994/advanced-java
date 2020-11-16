//Authors Olof Persson Karl Andersson
#include "accelerometer.h"
#include <math.h>
#include <esp_pm.h>
#include <driver/i2c.h>
#include "circular_buffer/circular_buffer.h"
#include "pins.h"

uint8_t getAcc;
int16_t totalAcc = 1;
struct circularBuffer bufferCircular;
#define MPU6050_ADDR 0x68
#define MPU6050_PWR_MGMT_1 0x6B
#define MPU6050_SMPLRT_DIV 0x19

//Configuers the communicationbus between the Microcontroller and the accelerometer
void initI2C(int sdapin, int sclpin)
{
    // configure and install driver
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;             // ESP32 acts as master
    conf.sda_io_num = sdapin;                // pin used for SDA
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE; // The SDA and SCL lines are active low, so they should be pulled up with resistors
    conf.scl_io_num = sclpin;                // SCL pin number
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE; // enables pullup on SDA
    conf.master.clk_speed = 100000;          // Standard mode (100 Kbit/s)
    // configure I2C controller 0
    esp_err_t res = i2c_param_config(I2C_NUM_0, &conf);
    ESP_ERROR_CHECK(res);
    // install driver, no buffers needed in master mode nor special interrupts config
    res = i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0);
    ESP_ERROR_CHECK(res);
    writeI2C(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x00); // power mode awake
    writeI2C(MPU6050_ADDR, MPU6050_SMPLRT_DIV, 250);  //dela med 250 = 32Hz
}

//Writes to the accelerometer
void writeI2C(uint8_t address, uint8_t reg, uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, address << 1 | I2C_MASTER_WRITE, 1);

    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, reg, 1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_write_byte(cmd, data, 1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);
}

//Reads from the accelerometer. First you need to write to it to be able to read from it.
void readI2C(uint8_t address, uint8_t reg, uint8_t *buffer, int len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, address << 1 | I2C_MASTER_WRITE, 1);

    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, reg, 1);
    ESP_ERROR_CHECK(res);

    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);

    cmd = i2c_cmd_link_create();
    res = i2c_master_start(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_write_byte(cmd, address << 1 | I2C_MASTER_READ, 1);

    ESP_ERROR_CHECK(res);
    res = i2c_master_read(cmd, buffer, len, I2C_MASTER_NACK);
    ESP_ERROR_CHECK(res);
    res = i2c_master_stop(cmd);
    ESP_ERROR_CHECK(res);
    res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(res);
    i2c_cmd_link_delete(cmd);
}

//gets z,x,y values from the accelerometer, calculates it with an algorithm and puts that value in the buffer
void getValuesXYZ()
{
    uint32_t squirt;
    volatile int z = 0;
    volatile int x = 0;
    volatile int y = 0;
    readI2C(MPU6050_ADDR, 0x3c, &getAcc, 1);
    totalAcc = getAcc;
    readI2C(MPU6050_ADDR, 0x3b, &getAcc, 1);
    // combine high and low registers into a signed integer
    totalAcc |= ((int16_t)getAcc) << 8;
    x = totalAcc;

    readI2C(MPU6050_ADDR, 0x3e, &getAcc, 1);
    totalAcc = getAcc;
    readI2C(MPU6050_ADDR, 0x3d, &getAcc, 1);
    // combine high and low registers into a signed integer
    totalAcc |= ((int16_t)getAcc) << 8;
    y = totalAcc;

    readI2C(MPU6050_ADDR, 0x40, &getAcc, 1);
    totalAcc = getAcc;
    readI2C(MPU6050_ADDR, 0x3f, &getAcc, 1);
    // combine high and low registers into a signed integer
    totalAcc |= ((int16_t)getAcc) << 8;
    z = totalAcc;

    squirt = (uint32_t)sqrt((x * x) + (y * y) + (z * z));
    addElement(&bufferCircular, squirt);
}
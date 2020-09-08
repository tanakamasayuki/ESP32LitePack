#ifndef __M5LiteMPU6886_H__
#define __M5LiteMPU6886_H__

#include "I2C_MPU6886.h"

class M5LiteMPU6886 {
  public:
    enum Ascale {
      AFS_2G = 0,
      AFS_4G,
      AFS_8G,
      AFS_16G
    };

    enum Gscale {
      GFS_250DPS = 0,
      GFS_500DPS,
      GFS_1000DPS,
      GFS_2000DPS
    };

    void setMPU6886(I2C_MPU6886 *mpu6886) {
      imu = mpu6886;
    }

    int Init(void) {
      return imu->begin();
    }

    void getAccelAdc(int16_t* ax, int16_t* ay, int16_t* az) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("MPU6886", "Not Support");
      *ax = 0;
      *ay = 0;
      *az = 0;
    }
    void getGyroAdc(int16_t* gx, int16_t* gy, int16_t* gz) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("MPU6886", "Not Support");
      *gx = 0;
      *gy = 0;
      *gz = 0;
    }
    void getTempAdc(int16_t *t) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("MPU6886", "Not Support");
      *t = 0;
    }

    void getAccelData(float* ax, float* ay, float* az) {
      imu->getAccel(ax, ay, az);
    }
    void getGyroData(float* gx, float* gy, float* gz) {
      imu->getGyro(gx, gy, gz);
    }
    void getTempData(float *t) {
      imu->getTemp(t);
    }

    void SetGyroFsr(Gscale scale) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("MPU6886", "Not Support");
    }
    void SetAccelFsr(Ascale scale) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("MPU6886", "Not Support");
    }

    void getAhrsData(float *pitch, float *roll, float *yaw) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("MPU6886", "Not Support");
      *pitch = 0;
      *roll = 0;
      *yaw = 0;
    }

  private:
    I2C_MPU6886 *imu;
};

#endif
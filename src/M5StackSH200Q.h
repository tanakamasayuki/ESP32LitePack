#ifndef __M5StackSH200Q_H__
#define __M5StackSH200Q_H__

#include "I2C_SH200Q.h"

class M5StackSH200Q {
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

    void setSH200Q(I2C_SH200Q *SH200Q) {
      imu = SH200Q;
    }

    int Init(void) {
      return imu->begin();
    }

    void getAccelAdc(int16_t* ax, int16_t* ay, int16_t* az) {
      // TODO
      ESP_LOGE("SH200Q", "Not Support");
      *ax = 0;
      *ay = 0;
      *az = 0;
    }
    void getGyroAdc(int16_t* gx, int16_t* gy, int16_t* gz) {
      // TODO
      ESP_LOGE("SH200Q", "Not Support");
      *gx = 0;
      *gy = 0;
      *gz = 0;
    }
    void getTempAdc(int16_t *t) {
      // TODO
      ESP_LOGE("SH200Q", "Not Support");
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

    void SetGyroFsr(Gscale scale) {
      // TODO
      ESP_LOGE("SH200Q", "Not Support");
    }
    void SetAccelFsr(Ascale scale) {
      // TODO
      ESP_LOGE("SH200Q", "Not Support");
    }

    void getAhrsData(float *pitch, float *roll, float *yaw) {
      // TODO
      ESP_LOGE("SH200Q", "Not Support");
      *pitch = 0;
      *roll = 0;
      *yaw = 0;
    }

  private:
    I2C_SH200Q *imu;
};

#endif

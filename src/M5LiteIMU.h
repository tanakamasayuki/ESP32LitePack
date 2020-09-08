#ifndef __M5LiteIMU_H__
#define __M5LiteIMU_H__

#include "I2C_MPU6886.h"
#include "I2C_SH200Q.h"
#include "I2C_BMA423.h"

class M5LiteIMU {
  public:
    enum ImuType {
      IMU_UNKNOWN   =   0,
      IMU_SH200Q    =   1,
      IMU_MPU6886   =   2,
      IMU_BMA423    = 101,
    };

    int Init(void) {
      int imu_flag = _mpu6886->begin();
      if (imu_flag == 0) {
        imuType = IMU_MPU6886;
        return 0;
      }

      imu_flag = _sh200q->begin();
      if (imu_flag == 0) {
        imuType = IMU_SH200Q;
        return 0;
      }

      imu_flag = _bma423->begin();
      if (imu_flag == 0) {
        imuType = IMU_BMA423;
        return 0;
      }

      imuType = IMU_UNKNOWN;
      return -1;
    }

    void setMPU6886(I2C_MPU6886 *mpu6886) {
      _mpu6886 = mpu6886;
    }
    void setSH200Q(I2C_SH200Q *sh200q) {
      _sh200q = sh200q;
    }
    void setBMA423(I2C_BMA423 *bma423) {
      _bma423 = bma423;
    }

    void getGres() __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("IMU", "Not Support");
    }
    void getAres() __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("IMU", "Not Support");
    }

    void getAccelAdc(int16_t *ax, int16_t *ay, int16_t *az) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("IMU", "Not Support");
      *ax = 0;
      *ay = 0;
      *az = 0;
    }
    void getGyroAdc(int16_t *gx, int16_t *gy, int16_t *gz) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("IMU", "Not Support");
      *gx = 0;
      *gy = 0;
      *gz = 0;
    }
    void getTempAdc(int16_t *t) __attribute__((deprecated)) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("IMU", "Not Support");
      *t = 0;
    }

    void getAccelData(float *ax, float *ay, float *az) {
      if (imuType == IMU_MPU6886) {
        _mpu6886->getAccel(ax, ay, az);
      } else if (imuType == IMU_SH200Q) {
        _sh200q->getAccel(ax, ay, az);
      } else if (imuType == IMU_BMA423) {
        _bma423->getAccel(ax, ay, az);
      } else {
        *ax = 0;
        *ay = 0;
        *az = 0;
      }

      if (board == lgfx::board_unknown) {
        *ax = -(*ax);
        *az = -(*az);
      } else if (board == lgfx::board_TTGO_TWatch) {
        *ax = -(*ax);
        *ay = -(*ay);
      }
    }
    void getGyroData(float *gx, float *gy, float *gz) {
      if (imuType == IMU_MPU6886) {
        _mpu6886->getGyro(gx, gy, gz);
      } else if (imuType == IMU_SH200Q) {
        _sh200q->getGyro(gx, gy, gz);
      } else {
        *gx = 0;
        *gy = 0;
        *gz = 0;
      }

      if (board == lgfx::board_unknown) {
        *gx = -(*gx);
        *gz = -(*gz);
      }
    }
    void getTempData(float *t) {
      if (imuType == IMU_MPU6886) {
        _mpu6886->getTemp(t);
      } else if (imuType == IMU_SH200Q) {
        _sh200q->getTemp(t);
      } else {
        *t = 0;
      }
    }

    void getAhrsData(float *pitch, float *roll, float *yaw) __attribute__((deprecated)) {
      // TODO
      ESP_LOGE("IMU", "Not Support");
      *pitch = 0;
      *roll = 0;
      *yaw = 0;
    }

    ImuType imuType;
    int board;
    float aRes;
    float gRes;

  private:
    I2C_MPU6886 *_mpu6886;
    I2C_SH200Q *_sh200q;
    I2C_BMA423 *_bma423;
};

#endif

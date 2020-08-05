#ifndef __M5StackIMU_H__
#define __M5StackIMU_H__

#include "I2C_MPU6886.h"
#include "I2C_SH200Q.h"

class M5StackIMU {
  public:
    enum ImuType {
      IMU_UNKNOWN = 0, IMU_SH200Q, IMU_MPU6886
    };

    int Init(void) {
      int imu_flag = _mpu6886->begin();
      if (imu_flag == 0) {
        imuType = IMU_MPU6886;
      } else {
        imu_flag = _sh200q->begin();
        if (imu_flag == 0) {
          imuType = IMU_SH200Q;
        } else {
          imuType = IMU_UNKNOWN;
          return -1;
        }
      }
      return 0;
    }

    void setMPU6886(I2C_MPU6886 *mpu6886) {
      _mpu6886 = mpu6886;
    }
    void setSH200Q(I2C_SH200Q *sh200q) {
      _sh200q = sh200q;
    }

    void getGres();
    void getAres();

    void getAccelAdc(int16_t *ax, int16_t *ay, int16_t *az);
    void getGyroAdc(int16_t *gx, int16_t *gy, int16_t *gz);
    void getTempAdc(int16_t *t);

    void getAccelData(float *ax, float *ay, float *az) {
      if (imuType == IMU_MPU6886) {
        _mpu6886->getAccel(ax, ay, az);
      } else if (imuType == IMU_SH200Q) {
        _sh200q->getAccel(ax, ay, az);
      } else {
        *ax = 0;
        *ay = 0;
        *az = 0;
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

    void getAhrsData(float *pitch, float *roll, float *yaw);

    ImuType imuType;
    float aRes;
    float gRes;

  private:
    I2C_MPU6886 *_mpu6886;
    I2C_SH200Q *_sh200q;
};

#endif

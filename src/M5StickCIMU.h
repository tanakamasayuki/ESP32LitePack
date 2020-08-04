#ifndef __M5StickCIMU_H__
#define __M5StickCIMU_H__

#include "I2C_MPU6886.h"

class M5StickCIMU {
  public:
    enum ImuType {
      IMU_UNKNOWN = 0, IMU_SH200Q, IMU_MPU6886
    };

    int Init(void) {
      int imu_flag = _mpu6886->begin();
      if (imu_flag == 0) {
        imuType = IMU_MPU6886;
      } else {
        //imu_flag = M5.Sh200Q.Init();
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

    void getGres();
    void getAres();

    void getAccelAdc(int16_t *ax, int16_t *ay, int16_t *az);
    void getGyroAdc(int16_t *gx, int16_t *gy, int16_t *gz);
    void getTempAdc(int16_t *t);

    void getAccelData(float *ax, float *ay, float *az) {
      _mpu6886->getAccel(ax, ay, az);
    }
    void getGyroData(float *gx, float *gy, float *gz) {
      _mpu6886->getGyro(gx, gy, gz);
    }
    void getTempData(float *t) {
      _mpu6886->getTemp(t);
    }

    void getAhrsData(float *pitch, float *roll, float *yaw);

    ImuType imuType;
    float aRes;
    float gRes;

  private:
    I2C_MPU6886 *_mpu6886;
    //I2C_SH200Q
};

#endif

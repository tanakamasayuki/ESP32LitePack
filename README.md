# ESP32 Lite Pack Library

A lightweight compatibility library. You can use any combination of libraries.

## Usage library

### LovyanGFX(like M5Display)
https://github.com/lovyan03/LovyanGFX

### I2C_AXP192(like AXP192)
https://github.com/tanakamasayuki/I2C_AXP192

### I2C_BM8563(like RTC)
https://github.com/tanakamasayuki/I2C_BM8563

### I2C_MPU6886(like MPU6886)
https://github.com/tanakamasayuki/I2C_MPU6886

## Support Devices

- [M5Stick](https://docs.m5stack.com/#/en/core/m5stickc)
- [M5Stick Plus](https://docs.m5stack.com/#/en/core/m5stickc_plus)
- [M5Stack BASIC](https://docs.m5stack.com/#/en/core/basic)
- [M5Stack GRAY](https://docs.m5stack.com/#/en/core/gray)
- [M5Stack FIRE](https://docs.m5stack.com/#/en/core/fire)

## Usage
```c
#include "M5StackAuto.h"

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(10);
  M5.Lcd.fillScreen(BLACK);
  M5.Imu.Init();
  Serial.printf("IMU : %d\n", M5.Imu.imuType);
}

void loop() {
  M5.update();

  M5.Lcd.setCursor(0, 4, 1);

  M5.Lcd.printf("AXP192 Test\n");
  M5.Lcd.printf("\n");

  M5.Lcd.printf("Battery\n");
  M5.Lcd.printf(" State:%6d\n"  , M5.Axp.GetBatState());      // バッテリーが接続されているか(常に1のはず)
  M5.Lcd.printf(" Warn :%6d\n"  , M5.Axp.GetWarningLevel());  // バッテリー残量警告 0:残あり, 1:残なし
  M5.Lcd.printf(" Temp :%6.1f\n", M5.Axp.GetTempInAXP192());  // AXP192の内部温度
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetBatVoltage());    // バッテリー電圧(3.0V-4.2V程度)
  M5.Lcd.printf(" I(mA):%6.1f\n", M5.Axp.GetBatCurrent());    // バッテリー電流(プラスが充電、マイナスが放電)
  M5.Lcd.printf(" W(mW):%6.1f\n", M5.Axp.GetBatPower());      // バッテリー電力(W=V*abs(I))

  M5.Lcd.printf("ASP\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetAPSVoltage());    // ESP32に供給されている電圧

  M5.Lcd.printf("VBus(USB)\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetVBusVoltage());   // USB電源からの電圧
  M5.Lcd.printf(" I(mA):%6.1f\n", M5.Axp.GetVBusCurrent());   // USB電源からの電流

  M5.Lcd.printf("VIN(5V-In)\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetVinVoltage());    // 5V IN端子からの電圧
  M5.Lcd.printf(" I(mA):%6.1f\n", M5.Axp.GetVinCurrent());    // 5V IN端子からの電流

  RTC_TimeTypeDef RTC_TimeStruct;
  RTC_DateTypeDef RTC_DateStruct;
  M5.Rtc.GetTime(&RTC_TimeStruct);
  M5.Rtc.GetData(&RTC_DateStruct);
  M5.Lcd.printf("%04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
  M5.Lcd.printf("%02d:%02d:%02d", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);

  if (M5.BtnA.wasPressed()) {
    Serial.println("M5.BtnA.wasPressed()");
  }
  if (M5.BtnB.wasPressed()) {
    Serial.println("M5.BtnB.wasPressed()");
  }
  if (M5.BtnC.wasPressed()) {
    Serial.println("M5.BtnC.wasPressed()");
  }
  if (M5.BtnA.wasReleased()) {
    Serial.println("M5.BtnA.wasReleased()");
  }
  if (M5.BtnB.wasReleased()) {
    Serial.println("M5.BtnB.wasReleased()");
  }
  if (M5.BtnC.wasReleased()) {
    Serial.println("M5.BtnC.wasReleased()");
  }
  int key = M5.Axp.GetBtnPress();
  if (key) {
    Serial.println(key);
  }

  if (M5.Imu.imuType != 0) {
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float t;

    M5.Imu.getAccelData(&ax, &ay, &az);
    M5.Imu.getGyroData(&gx, &gy, &gz);
    M5.Imu.getTempData(&t);

    Serial.printf(" %f,%f,%f,%f,%f,%f,%f\n", ax, ay, az, gx, gy, gz, t);
  }

  delay(100);
}
```

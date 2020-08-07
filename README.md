# ESP32 Lite Pack Library

A lightweight compatibility library. You can use any combination of libraries.

## Usage library

### LovyanGFX(like M5Display)
https://github.com/lovyan03/LovyanGFX

### FastLED
https://github.com/FastLED/FastLED

### I2C_AXP192(like AXP192)
https://github.com/tanakamasayuki/I2C_AXP192

### I2C_BM8563(like RTC)
https://github.com/tanakamasayuki/I2C_BM8563

### I2C_MPU6886(like MPU6886)
https://github.com/tanakamasayuki/I2C_MPU6886

## Support Devices

- [M5StickC](https://docs.m5stack.com/#/en/core/m5stickc)
- [M5StickC Plus](https://docs.m5stack.com/#/en/core/m5stickc_plus)
- [M5Stack BASIC](https://docs.m5stack.com/#/en/core/basic)
- [M5Stack GRAY](https://docs.m5stack.com/#/en/core/gray)
- [M5Stack FIRE](https://docs.m5stack.com/#/en/core/fire)
- [M5Stack ATOM Lite](https://docs.m5stack.com/#/en/core/atom_lite)
- [M5Stack ATOM Matrix](https://docs.m5stack.com/#/en/core/atom_matrix)
- [M5Stack ATOM ECHO](https://docs.m5stack.com/#/en/atom/atomecho)

## Usage
```c
#include "M5StackAuto.h"

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(10);

  Serial.printf("Lcd Width=%d, Height=%d\n", M5.Lcd.width(), M5.Lcd.height());

  M5.Imu.Init();
  Serial.printf("IMU : %d\n", M5.Imu.imuType);

  M5.dis.drawpix(0, CRGB(255, 0, 0));
  M5.dis.drawpix(2, CRGB(0, 255, 0));
  M5.dis.drawpix(4, CRGB(0, 0, 255));
  M5.dis.drawpix(6, CRGB::White);

  // Not Support(ESP_LOGE)
  M5.Axp.GetWarningLevel();
}

void loop() {
  static int vol = 11;

  M5.update();

  M5.Lcd.setCursor(0, 4, 1);

  M5.Lcd.printf("M5StackAuto\n");

  M5.Lcd.printf("Battery\n");
  M5.Lcd.printf(" Temp :%6.1f\n", M5.Axp.GetTempInAXP192());  // AXP192 Internal temperature
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetBatVoltage());    // Battery Voltage(3.0V-4.2V)
  M5.Lcd.printf(" I(mA):%6.1f\n", M5.Axp.GetBatCurrent());    // Battery Current(+:charge, -:decharge)

  M5.Lcd.printf("ASP\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetAPSVoltage());    // ESP32 Voltage

  M5.Lcd.printf("VBus(USB)\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetVBusVoltage());   // USB Voltage
  M5.Lcd.printf(" I(mA):%6.1f\n", M5.Axp.GetVBusCurrent());   // USB Current

  M5.Lcd.printf("VIN(5V-In)\n");
  M5.Lcd.printf(" V(V) :%6.3f\n", M5.Axp.GetVinVoltage());    // 5V IN Voltage
  M5.Lcd.printf(" I(mA):%6.1f\n", M5.Axp.GetVinCurrent());    // 5V IN Current

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

    M5.Lcd.printf(" Accel   Gyro\n");
    M5.Lcd.printf("X%5.2f%7.1f\n", ax, gx);
    M5.Lcd.printf("Y%5.2f%7.1f\n", ay, gy);
    M5.Lcd.printf("Z%5.2f%7.1f\n", az, gz);
  }

  RTC_TimeTypeDef RTC_TimeStruct;
  RTC_DateTypeDef RTC_DateStruct;
  M5.Rtc.GetTime(&RTC_TimeStruct);
  M5.Rtc.GetData(&RTC_DateStruct);
  M5.Lcd.printf("%04d-%02d-%02d\n", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
  M5.Lcd.printf("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);

  if (M5.BtnA.wasPressed()) {
    Serial.println("M5.BtnA.wasPressed()");
    M5.Beep.tone(1000, 100);
  }
  if (M5.BtnB.wasPressed()) {
    Serial.println("M5.BtnB.wasPressed()");
    vol--;
    M5.Beep.setVolume(vol);
    Serial.printf("vol = %d\n", vol);
  }
  if (M5.BtnC.wasPressed()) {
    Serial.println("M5.BtnC.wasPressed()");
    vol++;
    M5.Beep.setVolume(vol);
    Serial.printf("vol = %d\n", vol);
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

  delay(100);
}
```

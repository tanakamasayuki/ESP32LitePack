#ifndef __M5StickCLite_H__
#define __M5StickCLite_H__

#define LGFX_M5STICKC
#include <LGFX_TFT_eSPI.hpp>        // https://github.com/lovyan03/LovyanGFX
#include "M5StickCAXP192.h"
#include "M5StickCRTC.h"
#include "M5StickCButton.h"
#include "M5StickCIMU.h"
#include "M5StickCMPU6886.h"

// Color
#define BLACK               0x0000
#define NAVY                0x000F
#define DARKGREEN           0x03E0
#define DARKCYAN            0x03EF
#define MAROON              0x7800
#define PURPLE              0x780F
#define OLIVE               0x7BE0
#define LIGHTGREY           0xC618
#define DARKGREY            0x7BEF
#define BLUE                0x001F
#define GREEN               0x07E0
#define CYAN                0x07FF
#define RED                 0xF800
#define MAGENTA             0xF81F
#define YELLOW              0xFFE0
#define WHITE               0xFFFF
#define ORANGE              0xFD20
#define GREENYELLOW         0xAFE5
#define PINK                0xF81F

// Config
#define M5_IR               9
#define M5_LED              10
#define M5_BUTTON_HOME      37
#define M5_BUTTON_RST       39
#define BUTTON_A_PIN        37
#define BUTTON_B_PIN        39
#define SPEAKER_PIN         2
#define TONE_PIN_CHANNEL    0
#define USE_SERIAL          Serial

class M5StickCLite {
  public:
    void begin(bool LCDEnable = true, bool PowerEnable = true, bool SerialEnable = true) {
      // UART
      if (SerialEnable) {
        Serial.begin(115200);
        Serial.flush();
        delay(50);
        Serial.print("M5StickC initializing...");
      }

      Wire1.begin(21, 22);

      // Power
      if (PowerEnable) {
        Axp.begin();
      }

      // LCD INIT
      if (LCDEnable) {
        Lcd.begin();
      }

      if (SerialEnable) {
        Serial.println("OK");
      }

      Rtc.begin();

      Mpu6886.setMPU6886(&mpu6886);
      Imu.setMPU6886(&mpu6886);
    }

    void update() {
      BtnA.read();
      BtnB.read();
    }

    TFT_eSPI Lcd;
    M5StickCAXP192 Axp = M5StickCAXP192();

    M5StickCButton BtnA = M5StickCButton(BUTTON_A_PIN, true, DEBOUNCE_MS);
    M5StickCButton BtnB = M5StickCButton(BUTTON_B_PIN, true, DEBOUNCE_MS);

    M5StickCRTC Rtc;

    M5StickCIMU Imu;
    M5StickCMPU6886 Mpu6886;
    //SH200Q Sh200Q;

    //CommUtil I2C = CommUtil();

  private:
    const uint32_t DEBOUNCE_MS = 10;
    I2C_MPU6886 mpu6886 = I2C_MPU6886(I2C_MPU6886_DEFAULT_ADDRESS, Wire1);
};

M5StickCLite M5;

#endif

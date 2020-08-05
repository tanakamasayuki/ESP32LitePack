#ifndef __M5StackAuto_H__
#define __M5StackAuto_H__

#define LGFX_AUTODETECT
#include <LGFX_TFT_eSPI.hpp>        // https://github.com/lovyan03/LovyanGFX
#include "M5StackAXP192.h"
#include "M5StackRTC.h"
#include "M5StackButton.h"
#include "M5StackIMU.h"
#include "M5StackMPU6886.h"
#include "M5StackSH200Q.h"
#include "M5StackPower.h"
#include "M5StackCommUtil.h"
#include "M5StackSpeaker.h"

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
uint8_t M5_IR             = -1;
uint8_t M5_LED            = -1;
uint8_t BUTTON_A_PIN      = -1;
uint8_t BUTTON_B_PIN      = -1;
uint8_t BUTTON_C_PIN      = -1;
uint8_t SPEAKER_PIN       = -1;
uint8_t TONE_PIN_CHANNEL  = -1;
uint8_t TFCARD_CS_PIN     = -1;

class M5StackAuto {
  public:
    void begin(bool LCDEnable = true, bool PowerEnable = true, bool SerialEnable = true) {
      // UART
      if (SerialEnable) {
        Serial.begin(115200);
        Serial.flush();
        delay(50);
        Serial.print("M5StackAuto");
      }

      // LCD INIT
      if (LCDEnable) {
        Lcd.begin();
        board = (int)Lcd.getBoard();
        if (board == 1) {
          // M5Stack
          Serial.print("(M5Stack)");
          M5_IR             = -1;
          M5_LED            = -1;
          BUTTON_A_PIN      = 39;
          BUTTON_B_PIN      = 38;
          BUTTON_C_PIN      = 37;
          SPEAKER_PIN       = 25;
          TONE_PIN_CHANNEL  =  0;
          TFCARD_CS_PIN     =  4;
        } else if (board == 2) {
          // M5StickC
          Serial.print("(M5StickC)");
          M5_IR             =  9;
          M5_LED            = 10;
          BUTTON_A_PIN      = 37;
          BUTTON_B_PIN      = 39;
          BUTTON_C_PIN      = 99;
          SPEAKER_PIN       = -1;
          TONE_PIN_CHANNEL  = -1;
          TFCARD_CS_PIN     = -1;

          Axp.enable = true;
          Rtc.enable = true;
        } else if (board == 3) {
          // M5StickC Plus
          Serial.print("(M5StickC Plus)");
          M5_IR             =  9;
          M5_LED            = 10;
          BUTTON_A_PIN      = 37;
          BUTTON_B_PIN      = 39;
          BUTTON_C_PIN      = 99;
          SPEAKER_PIN       =  2;
          TONE_PIN_CHANNEL  =  0;
          TFCARD_CS_PIN     = -1;

          Axp.enable = true;
          Rtc.enable = true;
        }
      }

      Wire1.begin(21, 22);

      // Power
      if (PowerEnable) {
        Axp.setAXP192(&axp192);
        Axp.begin(board);
        if (board == 2) {
          // M5StickC LCD Rebegin
          //Lcd.begin();
        }
      }

      Rtc.begin();

      Mpu6886.setMPU6886(&mpu6886);
      Sh200Q.setSH200Q(&sh200q);
      Imu.setMPU6886(&mpu6886);
      Imu.setSH200Q(&sh200q);

      BtnA.begin(BUTTON_A_PIN, true, DEBOUNCE_MS);
      BtnB.begin(BUTTON_B_PIN, true, DEBOUNCE_MS);
      BtnC.setAXP192(&axp192);
      BtnC.begin(BUTTON_C_PIN, true, DEBOUNCE_MS);

      Speaker.setPin(SPEAKER_PIN, TONE_PIN_CHANNEL);

      if (SerialEnable) {
        Serial.println(" initializing...OK");
      }
    }

    void update() {
      BtnA.read();
      BtnB.read();
      BtnC.read();
      Speaker.update();
    }

    TFT_eSPI Lcd;
    M5StackAXP192 Axp = M5StackAXP192();

    M5StackButton BtnA;
    M5StackButton BtnB;
    M5StackButton BtnC;

    M5StackRTC Rtc;

    M5StackIMU Imu;
    M5StackMPU6886 Mpu6886;
    M5StackSH200Q Sh200Q;

    M5StackCommUtil I2C = M5StackCommUtil(Wire);
    M5StackPOWER Power;
    M5StackSPEAKER Speaker;

    int board = 0;

  private:
    const uint32_t DEBOUNCE_MS = 10;
    I2C_MPU6886 mpu6886 = I2C_MPU6886(I2C_MPU6886_DEFAULT_ADDRESS, Wire1);
    I2C_SH200Q sh200q = I2C_SH200Q(I2C_SH200Q_DEFAULT_ADDRESS, Wire1);
    I2C_AXP192 axp192 = I2C_AXP192(I2C_AXP192_DEFAULT_ADDRESS, Wire1);
};

M5StackAuto M5;

#endif

#ifndef __M5Lite_H__
#define __M5Lite_H__

#define LGFX_M5STACK          // M5Stack
#define LGFX_M5STICKC         // M5Stick C
#define LGFX_TTGO_TWATCH      // TTGO T-Watch
#include <LGFX_TFT_eSPI.hpp>  // https://github.com/lovyan03/LovyanGFX
#include "M5LiteAXP192.h"
#include "M5LiteRTC.h"
#include "M5LiteButton.h"
#include "M5LiteIMU.h"
#include "M5LiteMPU6886.h"
#include "M5LiteSH200Q.h"
#include "M5LitePower.h"
#include "M5LiteCommUtil.h"
#include "M5LiteSpeaker.h"
#include "M5LiteLED.h"
#include "M5LiteDebug.h"
#include "M5LiteEx.h"

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

class M5LiteBase {
  public:
    void begin(bool LCDEnable = true, bool PowerEnable = true, bool SerialEnable = true) {
      // UART
      if (SerialEnable) {
        Serial.begin(115200);
        Serial.flush();
        delay(200);
        Serial.print("M5LiteBase");
      }

      Axp.setAXP192(&axp192);
      Mpu6886.setMPU6886(&mpu6886);
      Sh200Q.setSH200Q(&sh200q);
      Imu.setMPU6886(&mpu6886);
      Imu.setSH200Q(&sh200q);
      Imu.setBMA423(&bma423);
      Power.setIP5306(&ip5306);
      BtnC.setAXP192(&axp192);

      // LCD INIT
      if (LCDEnable) {
        Lcd.begin();
        Ex.board = (int)Lcd.getBoard();
        Imu.board = Ex.board;
        if (Ex.board == lgfx::board_M5Stack) {
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

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_M5StackCore2) {
          // M5Stack Core2
          Serial.print("(M5Stack Core2)");
          M5_IR             = -1;
          M5_LED            = -1;
          BUTTON_A_PIN      = -1;
          BUTTON_B_PIN      = -1;
          BUTTON_C_PIN      = -1;
          SPEAKER_PIN       = -1;
          TONE_PIN_CHANNEL  =  0;
          TFCARD_CS_PIN     =  4;

          Axp.enable = true;
          Rtc.enable = true;

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_M5StickC) {
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

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_M5StickCPlus) {
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

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_TTGO_TWatch) {
          // TTGO T-Watch
          Serial.print("(LILYGO TTGO T-Watch)");
          M5_IR             = -1;
          M5_LED            = -1;
          BUTTON_A_PIN      = 36;
          BUTTON_B_PIN      = -1;
          BUTTON_C_PIN      = -1;
          SPEAKER_PIN       = -1;
          TONE_PIN_CHANNEL  = -1;
          TFCARD_CS_PIN     = -1;

          Rtc.enable = true;

          Wire1.begin(21, 22);
        } else if (Ex.board == lgfx::board_unknown) {
          // ATOM
          Serial.print("(M5Stack ATOM)");
          M5_IR             = 12;
          M5_LED            = -1;
          BUTTON_A_PIN      = 39;
          BUTTON_B_PIN      = -1;
          BUTTON_C_PIN      = -1;
          SPEAKER_PIN       = -1;
          TONE_PIN_CHANNEL  = -1;
          TFCARD_CS_PIN     = -1;

          // LCD not use
          Ex.useLcd = false;

          // LED start
          dis.begin();

          // I2C Init
          Wire1.begin(25, 21, 10000);
        } else {
          // Other
          Serial.print("(Other)");

          Wire1.begin(-1, -1);
        }
      } else {
        Wire1.begin(21, 22);
      }

      // Power
      if (PowerEnable) {
        Axp.setBoard(Ex.board);
        Axp.begin();
        if (Ex.useLcd) {
          Lcd.drawPixel(0, 0, 0x0000);
          Lcd.clear();
        }
      }

      Rtc.begin();

      BtnA.begin(BUTTON_A_PIN, true, DEBOUNCE_MS);
      BtnB.begin(BUTTON_B_PIN, true, DEBOUNCE_MS);
      BtnC.begin(BUTTON_C_PIN, true, DEBOUNCE_MS);

      Beep.setPin(SPEAKER_PIN, TONE_PIN_CHANNEL);

      Debug._Lcd = &Lcd;
      Debug._Axp = &Axp;
      Debug._BtnA = &BtnA;
      Debug._BtnB = &BtnB;
      Debug._BtnC = &BtnC;
      Debug._Rtc = &Rtc;
      Debug._Imu = &Imu;
      Debug._Mpu6886 = &Mpu6886;
      Debug._Sh200Q = &Sh200Q;
      Debug._I2C = &I2C;
      Debug._Power = &Power;
      Debug._Beep = &Beep;
      Debug._dis = &dis;
      Ex._Lcd = &Lcd;
      Ex._Axp = &Axp;
      Ex._BtnA = &BtnA;
      Ex._BtnB = &BtnB;
      Ex._BtnC = &BtnC;
      Ex._Rtc = &Rtc;
      Ex._Imu = &Imu;
      Ex._Mpu6886 = &Mpu6886;
      Ex._Sh200Q = &Sh200Q;
      Ex._I2C = &I2C;
      Ex._Power = &Power;
      Ex._Beep = &Beep;
      Ex._dis = &dis;
      Ex._Debug = &Debug;

      if (SerialEnable) {
        Serial.println(" initializing...OK");
      }
    }

    void update() {
      Ex.update();
    }

    TFT_eSPI Lcd;
    M5LiteAXP192 Axp = M5LiteAXP192();

    M5LiteButton BtnA;
    M5LiteButton BtnB;
    M5LiteButton BtnC;

    M5LiteRTC Rtc;

    M5LiteIMU Imu;
    M5LiteMPU6886 Mpu6886;
    M5LiteSH200Q Sh200Q;

    M5LiteCommUtil I2C = M5LiteCommUtil(Wire);
    M5LitePower Power;
    M5LiteSpeaker Beep;
    M5LiteLED dis;

    M5LiteDebug Debug;
    M5LiteEx Ex;

  private:
    const uint32_t DEBOUNCE_MS = 10;
    I2C_MPU6886 mpu6886 = I2C_MPU6886(I2C_MPU6886_DEFAULT_ADDRESS, Wire1);
    I2C_SH200Q sh200q = I2C_SH200Q(I2C_SH200Q_DEFAULT_ADDRESS, Wire1);
    I2C_BMA423 bma423 = I2C_BMA423(I2C_BMA423_DEFAULT_ADDRESS, Wire1);
    I2C_AXP192 axp192 = I2C_AXP192(I2C_AXP192_DEFAULT_ADDRESS, Wire1);
    I2C_IP5306 ip5306 = I2C_IP5306(I2C_IP5306_DEFAULT_ADDRESS, Wire1);
};

M5LiteBase M5Lite;
#define M5 M5Lite

#endif

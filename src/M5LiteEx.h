#ifndef __M5LiteEx_H__
#define __M5LiteEx_H__

class M5LiteEx {
  public:
    int board = 0;
    bool useLcd = true;

    TFT_eSPI *_Lcd;
    M5LiteAXP192 *_Axp;
    M5LiteButton *_BtnA;
    M5LiteButton *_BtnB;
    M5LiteButton *_BtnC;
    M5LiteRTC *_Rtc;
    M5LiteIMU *_Imu;
    M5LiteMPU6886 *_Mpu6886;
    M5LiteSH200Q *_Sh200Q;
    M5LiteCommUtil *_I2C;
    M5LitePower *_Power;
    M5LiteSpeaker *_Beep;
    M5LiteLED *_dis;
    M5LiteDebug *_Debug;

    void update(void) {
      _BtnA->read();
      _BtnB->read();
      _BtnC->read();
      _Beep->update();
      _Debug->update();
    }

    void delay(unsigned long ms) {
      const unsigned long tick = 50;

      while (0 < ms) {
        if (tick < ms) {
          ::delay(tick);
          ms -= tick;
        } else {
          ::delay(ms);
          ms = 0;
        }
        update();
      }
    }

  private:
};

#endif

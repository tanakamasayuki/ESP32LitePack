#ifndef __M5StackPower_H__
#define __M5StackPower_H__

#include <Arduino.h>
#include <Wire.h>

#define SLEEP_MSEC(us)  (((uint64_t)us) * 1000L)
#define SLEEP_SEC(us)   (((uint64_t)us) * 1000000L)
#define SLEEP_MIN(us)   (((uint64_t)us) * 60L * 1000000L)
#define SLEEP_HR(us)    (((uint64_t)us) * 60L * 60L * 1000000L)

class M5StackPOWER
{
  public:
    M5StackPOWER() {
    }
    bool canControl() {
      return false;
    }
    void begin() {
    }

    enum ShutdownTime {
      SHUTDOWN_8S = 0,
      SHUTDOWN_16S,
      SHUTDOWN_32S,
      SHUTDOWN_64S
    };

    bool setKeepLightLoad(bool en) __attribute__((deprecated));
    bool setPowerBoostKeepOn(bool en);
    bool setAutoBootOnLoad(bool en);
    bool setLowPowerShutdown(bool en) __attribute__((deprecated));
    bool setLowPowerShutdownTime(ShutdownTime time);
    bool setPowerBoostOnOff(bool en);
    bool setPowerBoostSet(bool en);
    bool setPowerVin(bool en);
    bool setPowerWLEDSet(bool en);
    bool setPowerBtnEn(bool en);

    bool setVinMaxCurrent(uint8_t cur);
    bool setChargeVolt(uint8_t volt);

    bool setCharge(bool en);
    bool isChargeFull();
    bool isCharging();
    int8_t getBatteryLevel();
    bool batteryMode(bool en);

    void setWakeupButton(uint8_t button);

    bool isResetbyWatchdog();
    bool isResetbyDeepsleep();
    bool isResetbySoftware();
    bool isResetbyPowerSW();

    void deepSleep(uint64_t time_in_us = 0);
    void lightSleep(uint64_t time_in_us = 0);

    void powerOFF();

    void reset();

  private:
    uint8_t _wakeupPin;
};
#endif

#ifndef __RTC_H__
#define __RTC_H__

#include <Wire.h>
#include "I2C_BM8563.h"

typedef struct
{
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
} RTC_TimeTypeDef;

typedef struct
{
  uint8_t WeekDay;
  uint8_t Month;
  uint8_t Date;
  uint16_t Year;
} RTC_DateTypeDef;

class M5StickCRTC {
  public:
    void begin(void) {
      rtc.begin();
    }
    void GetBm8563Time(void);

    void SetTime(RTC_TimeTypeDef* RTC_TimeStruct) {
      rtc.setTime((I2C_BM8563_TimeTypeDef*)RTC_TimeStruct);
    }
    void SetData(RTC_DateTypeDef* RTC_DateStruct) {
      rtc.setDate((I2C_BM8563_DateTypeDef*)RTC_DateStruct);
    }

    void GetTime(RTC_TimeTypeDef* RTC_TimeStruct) {
      rtc.getTime((I2C_BM8563_TimeTypeDef*)RTC_TimeStruct);
    }
    void GetData(RTC_DateTypeDef* RTC_DateStruct) {
      rtc.getDate((I2C_BM8563_DateTypeDef*)RTC_DateStruct);
    }

  private:
    I2C_BM8563 rtc = I2C_BM8563(I2C_BM8563_DEFAULT_ADDRESS, Wire1);
};

#endif

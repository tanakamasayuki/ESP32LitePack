# ESP32 Lite Pack Library

A lightweight compatibility library. You can use any combination of libraries.

## Usage library

### LovyanGFX(like M5Display)
https://github.com/lovyan03/LovyanGFX

### I2C_AXP192(like AXP192)
https://github.com/tanakamasayuki/I2C_AXP192

### I2C_BM8563(like RTC)
https://github.com/tanakamasayuki/I2C_BM8563

## Support Devices

- [M5Stack M5Stick](https://docs.m5stack.com/#/en/core/m5stickc)
- [M5Stack M5Stick Plus](https://docs.m5stack.com/#/en/core/m5stickc_plus)


## Usage
```
#include "M5StickCLite.h"

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(10);
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  M5.Lcd.setCursor(0, 4, 1);
  M5.Lcd.printf("Test\n");
}
```

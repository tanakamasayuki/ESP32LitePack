#include "M5StickCLite.h"

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(10);
  M5.Lcd.fillScreen(BLACK);
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

  if(M5.BtnA.wasPressed()){
    Serial.println("M5.BtnA.wasPressed()");
  }
  if(M5.BtnB.wasPressed()){
    Serial.println("M5.BtnB.wasPressed()");
  }
  if(M5.BtnA.wasReleased()){
    Serial.println("M5.BtnA.wasReleased()");
  }
  if(M5.BtnB.wasReleased()){
    Serial.println("M5.BtnB.wasReleased()");
  }
  int key = M5.Axp.GetBtnPress();
  if(key){
    Serial.println(key);
  }  

  delay(100);
}

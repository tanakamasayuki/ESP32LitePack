#ifndef __M5LiteDebug_H__
#define __M5LiteDebug_H__

class M5LiteDebug {
  public:
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

    void dispHelp(void) {
      Serial.println("M5Lite Debug Command List");
      Serial.println(" ?    : This print");
      Serial.println(" INFO : Print Info");
    }

    void dispInfo(void) {
      Serial.println("M5Lite Info");

      // Mac Address
      uint8_t mac[6];
      esp_read_mac(mac, ESP_MAC_WIFI_STA);
      Serial.printf(" Mac Address : %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

      // Board
      Serial.printf(" Board       : ");
      if (_Imu->board == lgfx::board_M5Stack) {
        // M5Stack
        Serial.println("M5Stack");
      } else if (_Imu->board == lgfx::board_M5StackCore2) {
        // M5Stack Core2
        Serial.println("M5Stack Core2");
      } else if (_Imu->board == lgfx::board_M5StickC) {
        // M5StickC
        Serial.println("M5StickC");
      } else if (_Imu->board == lgfx::board_M5StickCPlus) {
        // M5StickC Plus
        Serial.println("M5StickC Plus");
      } else if (_Imu->board == lgfx::board_TTGO_TWatch) {
        // TTGO T-Watch
        Serial.println("LILYGO TTGO T-Watch");
      } else if (_Imu->board == lgfx::board_unknown) {
        // ATOM
        Serial.println("M5Stack ATOM");
      }

      // LCD
      int width = _Lcd->width();
      int height = _Lcd->height();
      if (0 < width) {
        Serial.printf(" LCD         : Width:%d, Height:%d\n", width, height);
      } else {
        Serial.printf(" LCD         : (NONE)\n");
      }

      // AXP192
      if (_Axp->enable) {
        Serial.printf(" AXP192      : Battery\n");
        Serial.printf("                Temp :%6.1f C\n", _Axp->GetTempInAXP192());    // AXP192 Internal temperature
        Serial.printf("                V    :%6.3f V\n", _Axp->GetBatVoltage());    // Battery Voltage(3.0V-4.2V)
        Serial.printf("                I    :%6.1f mA\n", _Axp->GetBatCurrent());   // Battery Current(+:charge, -:decharge)

        Serial.printf("               ASP(ESP32)\n");
        Serial.printf("                V    :%6.3f V\n", _Axp->GetAPSVoltage());    // ESP32 Voltage

        Serial.printf("               VBus(USB)\n");
        Serial.printf("                V    :%6.3f V\n", _Axp->GetVBusVoltage());   // USB Voltage
        Serial.printf("                I    :%6.1f mA\n", _Axp->GetVBusCurrent());  // USB Current

        Serial.printf("               VIN(5V-In)\n");
        Serial.printf("                V    :%6.3f V\n", _Axp->GetVinVoltage());    // 5V IN Voltage
        Serial.printf("                I    :%6.1f mA\n", _Axp->GetVinCurrent());   // 5V IN Current

      } else {
        Serial.printf(" AXP192      : (NONE)\n");
      }

      // IMU
      Serial.printf(" IMU         : ");
      if (_Imu->imuType == M5LiteIMU::IMU_UNKNOWN) {
        Serial.println("(NONE)");
      } else if (_Imu->imuType == M5LiteIMU::IMU_SH200Q) {
        Serial.println("SH200Q(6-AXIS)");
        float ax, ay, az, gx, gy, gz , t;
        _Imu->getAccelData(&ax, &ay, &az);
        _Imu->getGyroData(&gx, &gy, &gz);
        _Imu->getTempData(&t);
        Serial.printf("               ACCEL\n");
        Serial.printf("                X    :%11.6f\n", ax);
        Serial.printf("                Y    :%11.6f\n", ay);
        Serial.printf("                Z    :%11.6f\n", az);
        Serial.printf("               GYRO\n");
        Serial.printf("                X    :%11.6f\n", gx);
        Serial.printf("                Y    :%11.6f\n", gy);
        Serial.printf("                Z    :%11.6f\n", gz);
        Serial.printf("               TEMP\n");
        Serial.printf("                T    :%11.6f C\n", t);
      } else if (_Imu->imuType == M5LiteIMU::IMU_MPU6886) {
        Serial.println("MPU6886(6-AXIS)");
        float ax, ay, az, gx, gy, gz , t;
        _Imu->getAccelData(&ax, &ay, &az);
        _Imu->getGyroData(&gx, &gy, &gz);
        _Imu->getTempData(&t);
        Serial.printf("               ACCEL\n");
        Serial.printf("                X    :%11.6f\n", ax);
        Serial.printf("                Y    :%11.6f\n", ay);
        Serial.printf("                Z    :%11.6f\n", az);
        Serial.printf("               GYRO\n");
        Serial.printf("                X    :%11.6f\n", gx);
        Serial.printf("                Y    :%11.6f\n", gy);
        Serial.printf("                Z    :%11.6f\n", gz);
        Serial.printf("               TEMP\n");
        Serial.printf("                T    :%11.6f C\n", t);
      } else if (_Imu->imuType == M5LiteIMU::IMU_BMA423) {
        Serial.println("BMA423(3-AXIS:ACCEL)");
        float ax, ay, az;
        _Imu->getAccelData(&ax, &ay, &az);
        Serial.printf("               ACCEL\n");
        Serial.printf("                X    :%11.6f\n", ax);
        Serial.printf("                Y    :%11.6f\n", ay);
        Serial.printf("                Z    :%11.6f\n", az);
      }

      // RTC
      Serial.printf(" RTC         : ");
      if (_Rtc->enable) {
        RTC_TimeTypeDef RTC_TimeStruct;
        RTC_DateTypeDef RTC_DateStruct;
        _Rtc->GetTime(&RTC_TimeStruct);
        _Rtc->GetData(&RTC_DateStruct);
        Serial.printf("%04d-%02d-%02d ", RTC_DateStruct.Year, RTC_DateStruct.Month, RTC_DateStruct.Date);
        Serial.printf("%02d:%02d:%02d\n", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes, RTC_TimeStruct.Seconds);
      } else {
        Serial.println("(NONE)");
      }
    }

    void update() {
      while (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        if (command == "") {
          // Skip
        } else if (command == "?") {
          dispHelp();
        } else if (command == "INFO") {
          dispInfo();
        } else {
          dispHelp();
        }
      }
    }
};

#endif

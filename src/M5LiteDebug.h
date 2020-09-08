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
    M5LiteTouch *_Touch;

    void dispHelp(void) {
      Serial.println("M5Lite Debug Command List");
      Serial.println(" ?           : This print");
      Serial.println(" INFO        : Print Info");
      Serial.println(" AXP192      : AXP192 Info");
      Serial.println(" IMU         : IMU Info");
      Serial.println(" RTC         : RTC Info");
      Serial.println(" MEM         : Memory Info");
#ifdef WiFi_h
      Serial.println(" WIFI        : Connect Wi-Fi(Last SSID & Key)");
      Serial.println(" NTP         : Sync NTP Server");
#endif
      Serial.println(" RESET       : Reset ESP32");
    }

    void dispAxp192(void) {
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
    }

    void dispImu(void) {
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
    }

    void dispRtc(void) {
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

    void dispMemory() {
      Serial.printf("===============================================================\n");
      Serial.printf("Memory Info\n");
      Serial.printf("===============================================================\n");

      Serial.printf("esp_get_free_heap_size()                              : %6d\n", esp_get_free_heap_size() );
      Serial.printf("esp_get_minimum_free_heap_size()                      : %6d\n", esp_get_minimum_free_heap_size() );

      //xPortGetFreeHeapSize()（データメモリ）ヒープの空きバイト数を返すFreeRTOS関数です。これはを呼び出すのと同じheap_caps_get_free_size(MALLOC_CAP_8BIT)です。
      Serial.printf("xPortGetFreeHeapSize()                                : %6d\n", xPortGetFreeHeapSize() );

      //xPortGetMinimumEverFreeHeapSize()また、関連heap_caps_get_minimum_free_size()するものを使用して、ブート以降のヒープの「最低水準点」を追跡できます。
      Serial.printf("xPortGetMinimumEverFreeHeapSize()                     : %6d\n", xPortGetMinimumEverFreeHeapSize() );

      //heap_caps_get_free_size() さまざまなメモリ機能の現在の空きメモリを返すためにも使用できます。
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_EXEC)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_EXEC) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_32BIT)             : %6d\n", heap_caps_get_free_size(MALLOC_CAP_32BIT) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_8BIT)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_DMA)               : %6d\n", heap_caps_get_free_size(MALLOC_CAP_DMA) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID2)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID2) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID3)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID3)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID4) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID4)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID5) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID5)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID6) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID6)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID7) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_PID7)              : %6d\n", heap_caps_get_free_size(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_SPIRAM)            : %6d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_INTERNAL)          : %6d\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_DEFAULT)           : %6d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT) );
      Serial.printf("heap_caps_get_free_size(MALLOC_CAP_INVALID)           : %6d\n", heap_caps_get_free_size(MALLOC_CAP_INVALID) );

      //heap_caps_get_largest_free_block()ヒープ内の最大の空きブロックを返すために使用できます。これは、現在可能な最大の単一割り当てです。この値を追跡し、合計空きヒープと比較すると、ヒープの断片化を検出できます。
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_EXEC)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_EXEC) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_32BIT)    : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_32BIT) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_8BIT)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_DMA)      : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_DMA) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID2)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID2) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID3)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID3)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID4) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID4)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID5) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID5)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID6) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID6)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID7) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_PID7)     : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM)   : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL) : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT)  : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT) );
      Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_INVALID)  : %6d\n", heap_caps_get_largest_free_block(MALLOC_CAP_INVALID) );

      //heap_caps_get_minimum_free_size()指定された機能を持つすべての領域の合計最小空きメモリを取得します。
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_EXEC)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_EXEC) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_32BIT)     : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_32BIT) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_DMA)       : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DMA) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID2)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID2) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID3)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID3)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID4) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID4)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID5) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID5)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID6) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID6)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID7) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_PID7)      : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_PID3) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_SPIRAM)    : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_SPIRAM) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_INTERNAL)  : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_INTERNAL) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT)   : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT) );
      Serial.printf("heap_caps_get_minimum_free_size(MALLOC_CAP_INVALID)   : %6d\n", heap_caps_get_minimum_free_size(MALLOC_CAP_INVALID) );
    }

    void dispInfo(void) {
      Serial.println("M5Lite Info");

      // Mac Address
      uint8_t mac[6];
      esp_read_mac(mac, ESP_MAC_WIFI_STA);
      Serial.printf(" Mac Address : %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

#ifdef WiFi_h
      // IP Address
      Serial.printf(" IP Address  : ");
      Serial.println(WiFi.localIP());
#endif

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

      // RTC
      dispRtc();
    }

#ifdef WiFi_h
    void connectWiFi() {
      Serial.printf("===============================================================\n");
      Serial.printf("Wi-Fi Connect\n");
      Serial.printf("===============================================================\n");
      WiFi.begin();
      int i;
      for (i = 0; i < 100 ; i++) {
        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("Connect");
          Serial.printf(" IP Address  : ");
          Serial.println(WiFi.localIP());
          break;
        } else {
          Serial.print(".");
        }

        delay(100);
      }

      if (i == 100) {
        Serial.print("TimeOut");
      }
    }

    void syncNTP() {
      Serial.printf("===============================================================\n");
      Serial.printf("NTP Sync\n");
      Serial.printf("===============================================================\n");
      if (WiFi.status() == WL_CONNECTED) {
        const char* ntpServer =  "ntp.jst.mfeed.ad.jp";
        // Set ntp time to local
        configTime(9 * 3600, 0, ntpServer);

        Serial.print(" NTP         : ");
        Serial.println(ntpServer);

        // Get local time
        struct tm timeInfo;
        if (getLocalTime(&timeInfo)) {
          // Set RTC time
          RTC_TimeTypeDef TimeStruct;
          TimeStruct.Hours   = timeInfo.tm_hour;
          TimeStruct.Minutes = timeInfo.tm_min;
          TimeStruct.Seconds = timeInfo.tm_sec;
          _Rtc->SetTime(&TimeStruct);

          RTC_DateTypeDef DateStruct;
          DateStruct.WeekDay = timeInfo.tm_wday;
          DateStruct.Month = timeInfo.tm_mon + 1;
          DateStruct.Date = timeInfo.tm_mday;
          DateStruct.Year = timeInfo.tm_year + 1900;
          _Rtc->SetData(&DateStruct);

          Serial.print(" Local Time  : ");
          Serial.printf("%04d-%02d-%02d ", DateStruct.Year, DateStruct.Month, DateStruct.Date);
          Serial.printf("%02d:%02d:%02d\n", TimeStruct.Hours, TimeStruct.Minutes, TimeStruct.Seconds);

          if (_Rtc->enable) {
            dispRtc();
          }
        }
      } else {
        Serial.println("Not Wi-Fi Connection");
      }
    }
#endif

    void update() {
      while (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        if (command == "") {
          // Skip
        } else if (command == "?") {
          dispHelp();
        } else if (command == "RESET") {
          ESP.restart();
        } else if (command == "INFO") {
          dispInfo();
        } else if (command == "AXP192") {
          dispAxp192();
        } else if (command == "IMU") {
          dispImu();
        } else if (command == "RTC") {
          dispRtc();
        } else if (command == "MEM") {
          dispMemory();
#ifdef WiFi_h
        } else if (command == "WIFI") {
          connectWiFi();
        } else if (command == "NTP") {
          syncNTP();
#endif
        } else {
          dispHelp();
        }

        Serial.println(">");
      }
    }
};

#endif

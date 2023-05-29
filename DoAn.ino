#define BLYNK_TEMPLATE_ID "TMPL6-ATeIf1F"
#define BLYNK_TEMPLATE_NAME "4Relay"

#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD

#include "BlynkEdgent.h"
#include <TimeLib.h>
#include <DHT.h>

WidgetLED LedConnect(V0);
unsigned long timeUpdate = millis();

//DHT dht(D7, DHT11);

BlynkTimer timer;
long rtc_sec;
int startTime1;
int endTime1;
int startTime2;
int endTime2;
int startTime3;
int endTime3;
int startTime4;
int endTime4;

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);

  BlynkEdgent.begin();
  //dht.begin();
  timer.setInterval(1000L, checkTime);
}

void loop() {

  BlynkEdgent.run();
  timer.run();
  check();
  // c_update();
  blynk_update();
}
BLYNK_CONNECTED() {
  Blynk.syncAll();
  Blynk.sendInternal("rtc", "sync");
}
BLYNK_WRITE(V1) {
  int p = param.asInt();
  digitalWrite(D1, p);
}
BLYNK_WRITE(V2) {
  int p = param.asInt();
  digitalWrite(D2, p);
}
BLYNK_WRITE(V3) {
  int p = param.asInt();
  digitalWrite(D5, p);
}
BLYNK_WRITE(V4) {
  int p = param.asInt();
  digitalWrite(D6, p);
}

BLYNK_WRITE(V5) {
  TimeInputParam t(param);
  if (t.hasStartTime() && t.hasStopTime()) {
    startTime1 = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    endTime1 = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}

BLYNK_WRITE(V6) {
  TimeInputParam t(param);
  if (t.hasStartTime() && t.hasStopTime()) {
    startTime2 = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    endTime2 = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}

BLYNK_WRITE(V7) {
  TimeInputParam t(param);
  if (t.hasStartTime() && t.hasStopTime()) {
    startTime3 = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    endTime3 = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}

BLYNK_WRITE(V8) {
  TimeInputParam t(param);
  if (t.hasStartTime() && t.hasStopTime()) {
    startTime4 = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    endTime4 = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
  }
}

BLYNK_WRITE(InternalPinRTC) {  //check the value of InternalPinRTC
  long t = param.asLong();     //store time in t variable
  setTime(t);
  rtc_sec = (hour() * 60 * 60) + (minute() * 60) + second();
  //Serial.println(String("RTC Server: ") + hour() + ":" + minute() + ":" + second());
  //Serial.println(rtc_sec);
}

void checkTime() {
  Blynk.sendInternal("rtc", "sync");
}

void check() {
  // Time 1
  if (startTime1 <= rtc_sec && endTime1 > rtc_sec) {
    digitalWrite(D1, HIGH);
    Blynk.virtualWrite(V1, 1);
  }
  if (rtc_sec == endTime1) {
    digitalWrite(D1, LOW);
    Blynk.virtualWrite(V1, 0);
  }
  // Time 2
  if (startTime2 <= rtc_sec && endTime2 > rtc_sec) {
    digitalWrite(D2, HIGH);
    Blynk.virtualWrite(V2, 1);
  }
  if (rtc_sec == endTime2) {
    digitalWrite(D2, LOW);
    Blynk.virtualWrite(V2, 0);
  }
  // Time 3
  if (startTime3 <= rtc_sec && endTime3 > rtc_sec) {
    digitalWrite(D3, HIGH);
    Blynk.virtualWrite(V3, 1);
  }
  if (rtc_sec == endTime3) {
    digitalWrite(D3, LOW);
    Blynk.virtualWrite(V3, 0);
  }
  // Time 4
  if (startTime4 <= rtc_sec && endTime4 > rtc_sec) {
    digitalWrite(D4, HIGH);
    Blynk.virtualWrite(V4, 1);
  }
  if (rtc_sec == endTime4) {
    digitalWrite(D4, LOW);
    Blynk.virtualWrite(V4, 0);
  }
}

// void c_update() {
//   delay(5000);
//   float temperature = dht.readTemperature();  // Đọc nhiệt độ từ cảm biến DHT11
//   float humidity = dht.readHumidity();        // Đọc độ ẩm từ cảm biến DHT11
//   if (isnan(temperature) || isnan(humidity)) {
//     Serial.println("Failed to read from DHT");
//     return;
//   }

//   Blynk.virtualWrite(V9, temperature);  // Gửi giá trị nhiệt độ đến một cảm biến ảo có ID V5 trên Blynk
//   //Blynk.virtualWrite(V6, humidity);
//   Serial.print("Nhiệt độ: ");
//   Serial.print(temperature);
//   Serial.print("  -  Độ ẩm: ");
//   Serial.print(humidity);
//   Serial.println();
// }

void blynk_update() {
  if (millis() - timeUpdate > 1000) {
    if (LedConnect.getValue()) {
      LedConnect.off();
    } else {
      LedConnect.on();
    }
    timeUpdate = millis();
  }
}

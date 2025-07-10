#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <SinricPro.h>
#include <SinricProFanUS.h>

#define WIFI_SSID         "thakre_home"
#define WIFI_PASS         "rushi@7728"
#define APP_KEY           "7715d9e4-d2ca-42e0-aaed-ac9961737043"
#define APP_SECRET        "e7007719-5f70-4140-9afa-bb69ba32a0c5-bb76c4d2-fc4f-49a5-b628-414e9945303a"
#define DEVICE_ID         "6848836d929fca430250d6dd"

#define IR_LED_PIN        D1

IRsend irsend(IR_LED_PIN);

#define FAN_ON_CODE       0x00CF8976  // Example IR code for ON (replace with actual)
#define FAN_OFF_CODE      0x00CF8976  // Example IR code for OFF (replace with actual)
#define FAN_LOW_CODE      0x00CF09F6  // Example IR code for Low speed (1)
#define FAN_MEDIUM_CODE   0x00CFC936  // Example IR code for Medium speed (3)
#define FAN_HIGH_CODE     0x00CFF10E  // Example IR code for High speed (5)

bool onPowerState(const String &deviceId, bool &state) {
  if (deviceId != DEVICE_ID) return false;
  Serial.printf("Fan Power %s\n", state ? "ON" : "OFF");

  if (state) {
    irsend.sendNEC(FAN_ON_CODE, 32);  // Default speed when turned on
  } else {
    irsend.sendNEC(FAN_OFF_CODE, 32);
  }
  return true;
}

bool onRangeValue(const String &deviceId, int &rangeValue) {
  if (deviceId != DEVICE_ID) return false;
  Serial.printf("Fan speed set to %d\n", rangeValue);

  switch (rangeValue) {
    case 1:
      irsend.sendNEC(FAN_LOW_CODE, 32);
      break;
    case 2:
      irsend.sendNEC(FAN_MEDIUM_CODE, 32);
      break;
    case 3:
      irsend.sendNEC(FAN_HIGH_CODE, 32);
      break;
  }
  return true;
}

void setupWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println(" connected!");
}

void setupSinricPro() {
  SinricProFanUS &myFan = SinricPro[DEVICE_ID];
  myFan.onPowerState(onPowerState);
  myFan.onRangeValue(onRangeValue);

  SinricPro.onConnected([]() { Serial.println("Connected to SinricPro"); });
  SinricPro.onDisconnected([]() { Serial.println("Disconnected from SinricPro"); });

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

void setup() {
  Serial.begin(115200);
  irsend.begin();
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}

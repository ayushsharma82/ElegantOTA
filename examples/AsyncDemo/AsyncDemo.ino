/*
  -----------------------
  ElegantOTA - Async Demo Example
  -----------------------

  NOTE: Make sure you have enabled Async Mode in ElegantOTA before compiling this example!
  Guide: https://docs.elegantota.pro/async-mode/

  Skill Level: Beginner

  This example provides with a bare minimal app with ElegantOTA functionality which works
  with AsyncWebServer.

  Github: https://github.com/ayushsharma82/ElegantOTA
  WiKi: https://docs.elegantota.pro

  Works with:
  - ESP8266
  - ESP32
  - RP2040 (with WiFi) (Example: Raspberry Pi Pico W)
  - RP2350 (with WiFi) (Example: Raspberry Pi Pico 2W)

  Important note for RP2040/RP2350 users:
  - RP2040/RP2350 requires LittleFS partition for the OTA updates to work. Without LittleFS partition, OTA updates will fail.
    Make sure to select Tools > Flash Size > "2MB (Sketch 1MB, FS 1MB)" option.
  - If using bare RP2040/RP2350, it requires a WiFi chip like Pico W/Pico 2W for ElegantOTA to work.

  -------------------------------

  Upgrade to ElegantOTA Pro: https://elegantota.pro
*/

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#elif defined(TARGET_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2040) || defined(PICO_RP2350)
  #include <WiFi.h>
  #include <RPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

const char* ssid = "........";
const char* password = "........";

AsyncWebServer server(80);

unsigned long ota_progress_millis = 0;

void onOTAStart() {
  // Log when OTA has started
  Serial.println("OTA update started!");
  // <Add your own code here>
}

void onOTAProgress(size_t current, size_t final) {
  // Log every 1 second
  if (millis() - ota_progress_millis > 1000) {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
  }
}

void onOTAEnd(bool success) {
  // Log when OTA has finished
  if (success) {
    Serial.println("OTA update finished successfully!");
  } else {
    Serial.println("There was an error during OTA update!");
  }
  // <Add your own code here>
}

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi! This is ElegantOTA AsyncDemo.");
  });

  ElegantOTA.begin(&server);    // Start ElegantOTA
  // ElegantOTA callbacks
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  ElegantOTA.loop();
}

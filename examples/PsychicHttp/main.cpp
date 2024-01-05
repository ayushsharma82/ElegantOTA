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

  Works with both ESP8266 & ESP32

  -------------------------------

  Upgrade to ElegantOTA Pro: https://elegantota.pro

*/

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP32)
  #include <WiFi.h>
#endif

#include <ElegantOTA.h>
#include <PsychicHttp.h>

PsychicWebSocketHandler websocketHandler;
PsychicEventSource eventSource;
PsychicHttpServer server;


const char* ssid = "........";
const char* password = "........";

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

  server.listen(80); // NOTE: for PsychicHttp you MUST call listen() before registering any urls using .on()

  // Set Authentication Credentials
  ElegantOTA.setAuth("test", "test");

  //setup server config stuff here
  server.config.max_uri_handlers = 20; //maximum number of uri handlers (.on() calls)

  server.onOpen([](PsychicClient *client) {
    Serial.printf("[http] connection #%u connected from %s\n", client->socket(), client->remoteIP().toString());
  });

  //example callback everytime a connection is closed
  server.onClose([](PsychicClient *client) {
    Serial.printf("[http] connection #%u closed from %s\n", client->socket(), client->remoteIP().toString());
  });

  ElegantOTA.begin(&server);    // Start ElegantOTA
  // ElegantOTA callbacks
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  Serial.println("HTTP server started");
}

void loop(void) {
  ElegantOTA.loop();
}

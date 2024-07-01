---
title: Getting Started
sidebar_label: Getting Started
sidebar_position: 3
---

Getting started with ElegantOTA is pretty simple. This guide assumes that you already have a simple webserver code prepared and you just need to inject the following lines in your existing code:


### Include Dependency
At the very beginning of sketch include the ElegantOTA library.
```cpp
#include <ElegantOTA.h>
```

<br/>


### Add `begin` function
Now add the `begin` function of ElegantOTA in setup block of your sketch. This will inject ElegantOTA routes and logic into the web server.
```cpp
ElegantOTA.begin(&server);
```

<br/>

### Add `loop` function
Last part is to call the `loop` function of ElegantOTA in loop block of your sketch. This loop block is necessary for ElegantOTA to handle reboot after OTA update.
```cpp
ElegantOTA.loop();
```

<br/>

### Final Code
That's it! This is how a ready to use example will look like. After uploading the code to your platform, you can access ElegantOTA portal on `http://<YOUR_DEVICE_IP>/update`.

```cpp
/*
  -----------------------
  ElegantOTA - Demo Example
  -----------------------

  Skill Level: Beginner

  This example provides with a bare minimal app with ElegantOTA functionality.

  Github: https://github.com/ayushsharma82/ElegantOTA
  WiKi: https://docs.elegantota.pro

  Works with both ESP8266 & ESP32

  -------------------------------

  Upgrade to ElegantOTA Pro: https://elegantota.pro

*/


#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <WebServer.h>
#endif

#include <ElegantOTA.h>

const char* ssid = "........";
const char* password = "........";

#if defined(ESP8266)
  ESP8266WebServer server(80);
#elif defined(ESP32)
  WebServer server(80);
#endif

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

  server.on("/", []() {
    server.send(200, "text/plain", "Hi! This is ElegantOTA Demo.");
  });

  ElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  ElegantOTA.loop();
}
```
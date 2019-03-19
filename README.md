<p align="center"><img src="https://raw.githubusercontent.com/ayushsharma82/ElegantOTA/master/docs/logo.svg?sanitize=true" width="400"></p>

<hr/>
<p align="center">
<!-- <img src="https://img.shields.io/travis/com/ayushsharma82/ESP-DASH.svg?style=for-the-badge" />
&nbsp; -->
<img src="https://img.shields.io/github/last-commit/ayushsharma82/ElegantOTA.svg?style=for-the-badge" />
&nbsp;
<img src="https://img.shields.io/github/license/ayushsharma82/ElegantOTA.svg?style=for-the-badge" />
&nbsp;
<a href="https://www.patreon.com/asrocks5" target="_blank"><img src="https://img.shields.io/badge/patreon-donate-orange.svg?style=for-the-badge&logo=patreon" /></a>
</p>
<hr/>


<p align="center">Push OTAs to ESP8266 Elegantly!</p>

<br>
<br>

<h2 align="center">Preview</h2>
<p align="center"><img src="https://raw.githubusercontent.com/ayushsharma82/ElegantOTA/master/docs/elegantOtaDemo.gif"></p>

<br>
<br>

<h2>Documentation</h2>
<p>ElegantOTA is a dead simple library which does your work in just 1 Line. Honestly, It's just a wrapper library which injects it's own elegant webpage instead of the ugly upload page which comes by default in Arduino Library.</p>

 Include ElegantOTA Library `#include <ElegantOTA.h>` at top of your Arduino Code.
 
 Paste this - `ElegantOTA.begin(&server);`  line above your `server.begin();`
 
 That's all!
 
<br>
<h2>Example</h2>
 
```

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ElegantOTA.h>

const char* ssid = "........";
const char* password = "........";

ESP8266WebServer server(80);


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
    server.send(200, "text/plain", "Hi! I am ESP8266.");
  });

  ElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}

```

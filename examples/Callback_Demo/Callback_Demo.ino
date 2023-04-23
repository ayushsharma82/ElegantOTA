 /*
  ElegantOTA callback Demo Example - This example will work for both ESP8266 & ESP32 microcontrollers.
  -----
  Author: Ayush Sharma ( https://github.com/ayushsharma82 )
  
  Important Notice: Star the repository on Github if you like the library! :)
  Repository Link: https://github.com/ayushsharma82/ElegantOTA
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

int iCallBackCount = 0;
unsigned long lStartTime ;

void MyAction_onOTAStart() {
  iCallBackCount = 0;
  Serial.printf("OTA update started\n\r");
  lStartTime = millis();
}

void  MyAction_onOTAProgress() {
  iCallBackCount = iCallBackCount + 1;
  Serial.printf("OTA progress, %5.3fs elapsed\n\r", (float)(millis()-lStartTime)/1000.0);
}

void MyAction_onOTAEnd() {
  Serial.printf("OTA update ended, %5.3fs elapsed\n\r", (float)(millis()-lStartTime)/1000.0);
  iCallBackCount = 0 ;
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

  server.on("/", []() {
    server.send(200, "text/plain", "Hi! This is a sample response.");
  });

  ElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

// Add the AsyncElegantOTA callbacks
// Not all are required you can add each callback individually
//
// Watch the output on the serial monitor during OTA update.
  ElegantOTA.onOTAStart(MyAction_onOTAStart);
  ElegantOTA.onOTAProgress(MyAction_onOTAProgress);
  ElegantOTA.onOTAEnd(MyAction_onOTAEnd);
}

void loop(void) {
  server.handleClient();
}

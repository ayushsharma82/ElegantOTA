#ifndef ELEGANTOTA_ESP_SERVER_H
#define ELEGANTOTA_ESP_SERVER_H

#include "../common/ElegantCommon.h"

// Include Arduino Dependencies
#include <Arduino.h>
#include "stdlib_noniso.h"

#if defined(ESP8266)
    #include "ESP8266WiFi.h"
    #include "WiFiClient.h"
    #include "ESP8266WebServer.h"
#elif defined(ESP32)
    #include "WiFi.h"
    #include "WebServer.h"
#endif

#include "Update.h"


class ElegantESPServer: virtual public ElegantCommon {
    private:
        #if defined(ESP8266)
            ESP8266WebServer *_server;
        #elif defined(ESP32)
            WebServer *_server;
        #endif

        // Webserver authentication
        bool authenticate;
        char _username[64];
        char _password[64];

    public:
        ElegantESPServer();

        #if defined(ESP8266)
            void begin(ESP8266WebServer *server, const char * username = "", const char * password = "");
        #elif defined(ESP32)
            void begin(WebServer *server, const char * username = "", const char * password = "");
        #endif

        ~ElegantESPServer();
};

#endif
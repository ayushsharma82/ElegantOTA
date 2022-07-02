#ifndef ELEGANTOTA_ESP_ASYNC_SERVER_H
#define ELEGANTOTA_ESP_ASYNC_SERVER_H

#include "../common/ElegantCommon.h"

// Include Arduino Dependencies
#include <Arduino.h>
#include "stdlib_noniso.h"

#if defined(ESP8266)
    #include "ESP8266WiFi.h"
    #include "Hash.h"
    #include "ESPAsyncTCP.h"
#elif defined(ESP32)
    #include "WiFi.h"
    #include "Hash.h"
    #include "ESPAsyncTCP.h"
#endif

#include "ESPAsyncWebServer.h"
#include "Update.h"


class ElegantESPAsyncServer: virtual public ElegantCommon {
    private:
        ESPAsyncWebServer *_server;

        // Webserver authentication
        bool _authenticate;
        char _username[64];
        char _password[64];

    public:
        ElegantESPAsyncServer();
        void begin(ESPAsyncWebServer *server, const char * username = "", const char * password = "");
        ~ElegantESPAsyncServer();
};

#endif
#ifndef ELEGANTOTA_H
#define ELEGANTOTA_H


#ifndef ELEGANTOTA_USE_ASYNC_SERVER
    #define ELEGANTOTA_USE_ASYNC_SERVER 0
#endif

#include "./www/elegantWebpage.h"

#ifdef ARDUINO
    #include <Arduino.h>
    #if defined(ESP8266) || defined(ESP32)
        #if ELEGANTOTA_USE_ASYNC_SERVER == 1
            #include "./platforms/espressif/ElegantESPAsyncServer.h"
        #else
            #include "./platforms/espressif/ElegantESPServer.h"
        #endif
    #endif
#endif


class ElegantOTAClass
#ifdef ARDUINO
    #if defined(ESP8266) || defined(ESP32)
        #if ELEGANTOTA_USE_ASYNC_SERVER == 1
            : public ElegantESPAsyncServer
        #else
            : public ElegantESPServer
        #endif
    #endif
#endif
{
  public:
      ElegantOTAClass();
      ~ElegantOTAClass();
};

extern ElegantOTAClass ElegantOTA;
#endif

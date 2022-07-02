#ifndef ELEGANTOTA_H
#define ELEGANTOTA_H


#ifndef ELEGANTOTA_USE_ASYNC_SERVER
    #define ELEGANTOTA_USE_ASYNC_SERVER 0
#endif

#include <Arduino.h>
#if defined(ESP8266) || defined(ESP32)
    #if ELEGANTOTA_USE_ASYNC_SERVER == 1
        #include "ElegantESPAsyncServer.h"
        typedef ElegantESPAsyncServer ElegantOTAClass;
    #else
        #include "ElegantESPServer.h"
        typedef ElegantESPServer ElegantOTAClass;
    #endif
#endif


extern ElegantOTAClass ElegantOTA;
#endif

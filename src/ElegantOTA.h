#ifndef ElegantOTA_h
#define ElegantOTA_h

#include "Arduino.h"
#include "stdlib_noniso.h"
#include "elegantWebpage.h"
#include "DigitalSignatureVerifier.h"

#if defined(ESP8266)
    #define HARDWARE "ESP8266"
    #include "ESP8266WiFi.h"
    #include "WiFiClient.h"
    #include "ESP8266WebServer.h"
    #include "ESP8266HTTPUpdateServer.h"
#elif defined(ESP32)
    #define HARDWARE "ESP32"
    #include "WiFi.h"
    #include "WiFiClient.h"
    #include "WebServer.h"
    #include "Update.h"
#endif


class ElegantOtaClass{
  public:
    ElegantOtaClass();
    void setDigitalSignature(UpdaterHashClass* hash, DigitalSignatureVerifier* verifier);
    void setID(const char* id);
    void onOTAStart(void callable(void));
    void onOTAProgress(void callable(void));
    void onOTAEnd(void callable(void));
    #if defined(ESP8266)      
      void begin(ESP8266WebServer *server, const char * username = "", const char * password = "");
    #elif defined(ESP32)
      void begin(WebServer *server, const char * username = "", const char * password = "");
    #endif
    
  private:
    #if defined(ESP8266)
        ESP8266WebServer *_server;
        ESP8266HTTPUpdateServer _httpUpdater;
    #endif
    #if defined(ESP32)
        WebServer *_server;
    #endif

    char _username[64];
    char _password[64];
    char _id[128];
    bool authenticate;      
    bool _preUpdateRequired = false;
    bool _progressUpdateRequired = false;
    bool _postUpdateRequired = false;
	uint8_t * _updateData;
	size_t _updateDataLen;
    void (*preUpdateCallback)();
    void (*progressUpdateCallback)();
    void (*postUpdateCallback)();
	size_t _sig_len;
	uint8_t * signature;
	bool verify;
	UpdaterHashClass* _hash;
	DigitalSignatureVerifier* _verifier; 
};

extern ElegantOtaClass ElegantOTA;
#endif

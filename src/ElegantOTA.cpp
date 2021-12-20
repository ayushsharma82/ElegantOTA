#include "ElegantOTA.h"

ElegantOtaClass::ElegantOtaClass(){
  #if defined(ESP8266)
    this->setID(String((uint32_t)ESP.getChipId(), HEX).c_str());
  #elif defined(ESP32)
    this->setID(String((uint32_t)ESP.getEfuseMac(), HEX).c_str());
  #endif
}

void ElegantOtaClass::setID(const char* id){
  #if defined(ESP8266)
    snprintf(_id, sizeof(_id), "{ \"id\": \"%s\", \"hardware\": \"ESP8266\" }", id);
  #elif defined(ESP32)
    snprintf(_id, sizeof(_id), "{ \"id\": \"%s\", \"hardware\": \"ESP32\" }", id);
  #endif
}

#if defined(ESP8266)
  void ElegantOtaClass::begin(ESP8266WebServer *server, const char * username, const char * password){
#elif defined(ESP32)
  void ElegantOtaClass::begin(WebServer *server, const char * username, const char * password){
#endif
    _server = server;

    if (strlen(username) > 0) {
      strlcpy(_username, username, sizeof(_username));
      strlcpy(_password, password, sizeof(_password));
      authenticate = true;
    }

    _server->on("/update", HTTP_GET, [&](){
      if (authenticate && !_server->authenticate(_username, _password)) {
        return _server->requestAuthentication();
      }
      _server->sendHeader("Content-Encoding", "gzip");
      _server->send_P(200, "text/html", (const char*)ELEGANT_HTML, ELEGANT_HTML_SIZE);
    });

    _server->on("/update/identity", HTTP_GET, [&](){
      if (authenticate && !_server->authenticate(_username, _password)) {
        return _server->requestAuthentication();
      }
      _server->send(200, "application/json", _id);
    });

    #if defined(ESP8266)
      if (authenticate) {
        _httpUpdater.setup(server, "/update");
      } else {
        _httpUpdater.setup(server, "/update", _username, _password);
      }
    #elif defined(ESP32)
      _server->on("/update", HTTP_POST, [&](){
        if (authenticate && !_server->authenticate(_username, _password)) {
          return;
        }
        _server->sendHeader("Connection", "close");
        _server->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        #if defined(ESP32)
          // Needs some time for Core 0 to send response
          delay(100);
          yield();
          delay(100);
        #endif
        ESP.restart();
      }, [&](){
        // Actual OTA Download
        if (authenticate && !_server->authenticate(_username, _password)) {
          return;
        }

        HTTPUpload& upload = _server->upload();
        if (upload.status == UPLOAD_FILE_START) {
            Serial.setDebugOutput(true);
            Serial.printf("Update Received: %s\n", upload.filename.c_str());
            if (upload.name == "filesystem") {
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_SPIFFS)) { //start with max available size
                    Update.printError(Serial);
                }
            } else {
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_FLASH)) { //start with max available size
                    Update.printError(Serial);
                }
            }
        } else if (upload.status == UPLOAD_FILE_WRITE) {
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                Update.printError(Serial);
            }
        } else if (upload.status == UPLOAD_FILE_END) {
            if (Update.end(true)) { //true to set the size to the current progress
                Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
            } else {
                Update.printError(Serial);
            }
            Serial.setDebugOutput(false);
        } else {
            Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
        }
      });
    #endif
  }

ElegantOtaClass ElegantOTA;

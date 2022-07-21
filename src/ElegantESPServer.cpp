#if defined(ARDUINO) && (defined(ESP32) || defined(ESP8266)) && ELEGANTOTA_USE_ASYNC_SERVER == 0
#include "ElegantESPServer.h"

#if defined(ESP32)
#include "flashz.hpp"
#endif

ElegantESPServer::ElegantESPServer() {
}

#if defined(ESP8266)
  void ElegantESPServer::begin(ESP8266WebServer *server, const char * username, const char * password) {
#elif defined(ESP32)
  void ElegantESPServer::begin(WebServer *server, const char * username, const char * password) {
#endif
    _server = server;

    // Set MAC Address
    setMACAddress(WiFi.macAddress().c_str());

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

    _server->on("/update", HTTP_POST, [&](){
        if (authenticate && !_server->authenticate(_username, _password)) {
          return;
        }
        _server->sendHeader("Connection", "close");
        _server->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
        
        if (_state.auto_reboot) {
            // TODO: Create an RTOS Task for ESP32 only to reboot after some time for the response to reach the client.
            ESP.restart();
        }
      }, [&](){
        // Actual OTA Download
        if (authenticate && !_server->authenticate(_username, _password)) {
          return;
        }

        // Get & Set MD5
        #ifndef ESP32   // no way to process MD5 for esp32's compressed images
        if (_server->hasArg("MD5")) {
            if(!Update.setMD5(_server->arg("MD5").c_str())) {
                return _server->send(400, "text/plain", "MD5 parameter invalid");
            }
        }
        #endif

        // Handle File Upload
        HTTPUpload& upload = _server->upload();
        
        // Handle Upload Start
        if (upload.status == UPLOAD_FILE_START) {
            // Clear previous OTA update
            Update.end(false);

            // Start OTA Callback
            bool ok = _trigger_ota_start();
            if (!ok) {
                return _server->send(500, "text/plain", "Task aborted. Application is busy.");
            }

            #if ELEGANTOTA_DEBUG == 1
                Serial.setDebugOutput(true);
            #endif

            ELEGANTOTA_DEBUG_LOG("[ElegantOTA] OTA update received: %s\n", upload.filename.c_str());

            #if defined(ESP8266)
                int cmd = (upload.filename == "filesystem") ? U_FS : U_FLASH;
                Update.runAsync(true);
                size_t fsSize = ((size_t) &_FS_end - (size_t) &_FS_start);
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if (!Update.begin((cmd == U_FS)?fsSize:maxSketchSpace, cmd)){ // Start with max available size
                    #if ELEGANTOTA_DEBUG == 1
                        #ifdef ESP32
                            FlashZ::getInstance().printError(ELEGANTOTA_DEBUG_PORT);
                        #else
                            Update.printError(ELEGANTOTA_DEBUG_PORT);
                        #endif
                    #endif
                    _trigger_ota_fail();
                    return _server->send(500, "text/plain", "OTA update failed due to size constraints");
                }
                ELEGANTOTA_DEBUG_LOG("[ElegantOTA] OTA update Started: %s - %d bytes\n", upload.filename.c_str(), upload.totalSize);
            #endif

        } else if (upload.status == UPLOAD_FILE_WRITE) {
            // Handle Upload Write
            #if defined(ESP32)
            if (!upload.totalSize){
                int cmd = (upload.filename == "filesystem") ? U_SPIFFS : U_FLASH;
                bool mode_z = (upload.buf[0] == ZLIB_HEADER);    // check if we have a compressed image

                if (!(mode_z ? FlashZ::getInstance().beginz(UPDATE_SIZE_UNKNOWN, cmd) : FlashZ::getInstance().begin(UPDATE_SIZE_UNKNOWN, cmd))){
                    #if ELEGANTOTA_DEBUG == 1
                            FlashZ::getInstance().printError(ELEGANTOTA_DEBUG_PORT);
                    #endif
                    _trigger_ota_fail();
                    return _server->send(500, "text/plain", "OTA update failed due to size constraints");
                }
                ELEGANTOTA_DEBUG_LOG("[ElegantOTA] OTA update Started: %s; mode_z: %s\n", upload.filename.c_str(), mode_z ? "yes" : "no");
            }
            #endif  // defined(ESP32)

        #ifdef ESP32
            if(FlashZ::getInstance().writez(upload.buf, upload.currentSize, false) != upload.currentSize){
                FlashZ::getInstance().printError(ELEGANTOTA_DEBUG_PORT);
        #else
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                Update.printError(ELEGANTOTA_DEBUG_PORT);
        #endif
                _trigger_ota_fail();
                return _server->send(500, "text/plain", "OTA update failed due to error while writing to flash");
            }
            // Calculate progress
            uint32_t progress = (uint32_t)((float)upload.currentSize / (float)upload.totalSize * 100);
            _trigger_ota_progress(progress);
        } else if (upload.status == UPLOAD_FILE_END) {
            // Handle Upload End
        #ifdef ESP32
            if(FlashZ::getInstance().writez(upload.buf, upload.currentSize, true) != upload.currentSize){
                _trigger_ota_fail();
                ELEGANTOTA_DEBUG_LOG("[ElegantOTA] OTA Update failed unexpectedly (likely broken connection): status=%d\n", upload.status);
                return FlashZ::getInstance().abortz();
            }
            if(FlashZ::getInstance().endz()){
        #else
            if (Update.end(true)) { //true to set the size to the current progress
        #endif
                ELEGANTOTA_DEBUG_LOG("[ElegantOTA] OTA update Success: %u\n", upload.totalSize);
                _trigger_ota_success();
            } else {
                _trigger_ota_fail();
                #if ELEGANTOTA_DEBUG == 1
                    Update.printError(ELEGANTOTA_DEBUG_PORT);
                #endif
            }
            
            #if ELEGANTOTA_DEBUG == 1
                Serial.setDebugOutput(false);
            #endif

            _trigger_ota_end();
        } else {
            #ifdef ESP32
                FlashZ::getInstance().abortz();
            #endif

            ELEGANTOTA_DEBUG_LOG("[ElegantOTA] OTA Update failed unexpectedly (likely broken connection): status=%d\n", upload.status);
        }
    });
}

ElegantESPServer::~ElegantESPServer() {
}

#endif
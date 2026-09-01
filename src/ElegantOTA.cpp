#include "ElegantOTA.h"

/**
 * The portal talks to the device over a handful of small routes. Everything
 * below is written once and expanded for whichever webserver the sketch is
 * compiled against, so the two builds cannot drift apart.
 */
#if ELEGANTOTA_USE_ASYNC_WEBSERVER == 1
  #define EOTA_ROUTE(...)   [&](AsyncWebServerRequest *request) __VA_ARGS__
  #define EOTA_GUARD()      if (_authenticate && !request->authenticate(_username.c_str(), _password.c_str())) { request->requestAuthentication(); return; }
  #define EOTA_HAS(n)       request->hasParam(n)
  #define EOTA_ARG(n)       request->getParam(n)->value()
  #define EOTA_SEND(c,t,b)  request->send((c), (t), (b))
#else
  #define EOTA_ROUTE(...)   [&]() __VA_ARGS__
  #define EOTA_GUARD()      if (_authenticate && !_server->authenticate(_username.c_str(), _password.c_str())) { _server->requestAuthentication(); return; }
  #define EOTA_HAS(n)       _server->hasArg(n)
  #define EOTA_ARG(n)       _server->arg(n)
  #define EOTA_SEND(c,t,b)  _server->send((c), (t), (b))
#endif

ElegantOTAClass::ElegantOTAClass(){}

// ---------------------------------------------------------------------------
// Flash geometry + Update wrapper
// ---------------------------------------------------------------------------

/**
 * How many bytes the target region can hold. Reported to the portal so it can
 * tell you a build is too large before a single byte is written. Returns 0
 * where the platform cannot answer without side effects.
 */
size_t ElegantOTAClass::_partitionSize(OTA_Mode mode) {
  #if defined(ESP8266)
    if (mode == OTA_MODE_FILESYSTEM) return ((size_t)FS_end - (size_t)FS_start);
    return (size_t)((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000);
  #elif defined(ESP32)
    if (mode == OTA_MODE_FILESYSTEM) {
      const esp_partition_t * part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_SPIFFS, NULL);
      return part ? (size_t)part->size : 0;
    }
    return (size_t)ESP.getFreeSketchSpace();
  #elif defined(TARGET_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2040) || defined(PICO_RP2350)
    // Both modes are bounded by the filesystem region: a firmware image is
    // staged there as a file before the bootloader copies it into place, and
    // the core's own limit is exactly this span. Reported without mounting
    // anything, so answering a metadata request stays free of side effects.
    (void)mode;
    return ((size_t)&_FS_end - (size_t)&_FS_start);
  #else
    (void)mode;
    return 0;
  #endif
}

/** A digest we are willing to hand to Update: exactly 32 hex characters. */
bool ElegantOTAClass::_validMD5(const char * hash) {
  if (!hash) return false;
  size_t len = 0;
  for (; hash[len]; len++) {
    const char c = hash[len];
    const bool hex = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
    if (!hex) return false;
  }
  return len == 32;
}

/** Close a flash region we opened but are not going to write to. */
void ElegantOTAClass::_abortUpdate() {
  #if defined(ESP32)
    Update.abort();
  #else
    Update.end();
  #endif
}

void ElegantOTAClass::_captureUpdateError() {
  StreamString str;
  Update.printError(str);
  _update_error_str = str.c_str();
  _update_error_str.trim();
  ELEGANTOTA_DEBUG_MSG(_update_error_str.c_str());
}

bool ElegantOTAClass::_beginUpdate(OTA_Mode mode) {
  #if defined(ESP8266)
    uint32_t update_size = mode == OTA_MODE_FILESYSTEM ? ((size_t)FS_end - (size_t)FS_start) : ((ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000);
    if (mode == OTA_MODE_FILESYSTEM) {
      close_all_fs();
    }
    Update.runAsync(true);
    if (!Update.begin(update_size, mode == OTA_MODE_FILESYSTEM ? U_FS : U_FLASH)) {
      ELEGANTOTA_DEBUG_MSG("Failed to start update process\n");
      _captureUpdateError();
      return false;
    }
  #elif defined(ESP32)
    if (!Update.begin(UPDATE_SIZE_UNKNOWN, mode == OTA_MODE_FILESYSTEM ? U_SPIFFS : U_FLASH)) {
      ELEGANTOTA_DEBUG_MSG("Failed to start update process\n");
      _captureUpdateError();
      return false;
    }
  #elif defined(TARGET_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2040) || defined(PICO_RP2350)
    // Update.begin() takes the budget the write is allowed to use, not the
    // space that happens to be free right now. Passing free space meant a
    // second update was refused for want of room the moment a previously
    // staged image was still sitting in the filesystem — even though that
    // file is truncated before the new one is written.
    uint32_t update_size = _partitionSize(mode);
    if (mode == OTA_MODE_FILESYSTEM) {
      LittleFS.end();
    }
    if (!Update.begin(update_size, mode == OTA_MODE_FILESYSTEM ? U_FS : U_FLASH)) {
      ELEGANTOTA_DEBUG_MSG("Failed to start update process\n");
      _captureUpdateError();
      return false;
    }
  #else
    (void)mode;
    return false;
  #endif
  return true;
}

void ElegantOTAClass::_buildMetadata(char * out, size_t len) {
  // Keys are kept short because this JSON crosses a very small pipe:
  // hw  chip family        ar  reboots itself after a successful write
  // fwa firmware space     fsa filesystem space (bytes, 0 = unknown)
  // fwu size of the build currently running (bytes, 0 = unknown)
  #if defined(ESP8266) || defined(ESP32)
    unsigned long running_size = (unsigned long)ESP.getSketchSize();
  #else
    unsigned long running_size = 0;
  #endif

  snprintf(out, len,
    "{\"hw\":\"%s\",\"ar\":%s,\"fwa\":%lu,\"fsa\":%lu,\"fwu\":%lu}",
    HARDWARE,
    _auto_reboot ? "true" : "false",
    (unsigned long)_partitionSize(OTA_MODE_FIRMWARE),
    (unsigned long)_partitionSize(OTA_MODE_FILESYSTEM),
    running_size
  );
}

// ---------------------------------------------------------------------------
// Routes
// ---------------------------------------------------------------------------

void ElegantOTAClass::begin(ELEGANTOTA_WEBSERVER *server, const char * username, const char * password){
  _server = server;

  setAuth(username, password);

  #if defined(TARGET_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2040) || defined(PICO_RP2350)
    if (!__isPicoW) {
      ELEGANTOTA_DEBUG_MSG("RP2040: Not a Pico W, skipping OTA setup\n");
      return;
    }
  #endif

  _registerRoutes();
}

void ElegantOTAClass::_registerRoutes(){
  // Portal
  #if ELEGANTOTA_USE_ASYNC_WEBSERVER == 1
    _server->on("/update", HTTP_GET, [&](AsyncWebServerRequest *request){
      if(_authenticate && !request->authenticate(_username.c_str(), _password.c_str())){
        return request->requestAuthentication();
      }
      #if defined(ASYNCWEBSERVER_VERSION) && ASYNCWEBSERVER_VERSION_MAJOR > 2  // This means we are using recommended fork of AsyncWebServer
        AsyncWebServerResponse *response = request->beginResponse(200, "text/html", ELEGANT_HTML, sizeof(ELEGANT_HTML));
      #else
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", ELEGANT_HTML, sizeof(ELEGANT_HTML));
      #endif
      response->addHeader("Content-Encoding", "gzip");
      request->send(response);
    });
  #else
    _server->on("/update", HTTP_GET, [&](){
      if (_authenticate && !_server->authenticate(_username.c_str(), _password.c_str())) {
        return _server->requestAuthentication();
      }
      _server->sendHeader("Content-Encoding", "gzip");
      _server->send_P(200, "text/html", (const char*)ELEGANT_HTML, sizeof(ELEGANT_HTML));
    });
  #endif

  // What the portal needs to draw itself: chip family and flash geometry
  _server->on("/ota/metadata", HTTP_GET, EOTA_ROUTE({
    char json[192];
    _buildMetadata(json, sizeof(json));
    EOTA_SEND(200, "application/json", json);
  }));

  // Open the flash region ahead of an upload
  _server->on("/ota/start", HTTP_GET, EOTA_ROUTE({
    EOTA_GUARD();

    OTA_Mode mode = OTA_MODE_FIRMWARE;
    if (EOTA_HAS("mode") && EOTA_ARG("mode") == "fs") {
      ELEGANTOTA_DEBUG_MSG("OTA Mode: Filesystem\n");
      mode = OTA_MODE_FILESYSTEM;
    } else {
      ELEGANTOTA_DEBUG_MSG("OTA Mode: Firmware\n");
    }

    #if UPDATE_DEBUG == 1
      // Serial output must be active to see the callback serial prints
      Serial.setDebugOutput(true);
    #endif

    // Check the digest before opening anything. Rejecting it afterwards would
    // leave the flash region open, and every later update would be refused
    // because one is still running.
    String hash;
    if (EOTA_HAS("hash")) {
      hash = EOTA_ARG("hash");
      ELEGANTOTA_DEBUG_MSG(String("MD5: "+hash+"\n").c_str());
      if (!_validMD5(hash.c_str())) {
        ELEGANTOTA_DEBUG_MSG("ERROR: MD5 hash not valid\n");
        EOTA_SEND(400, "text/plain", "That MD5 digest is not valid");
        return;
      }
    }

    // Pre-OTA update callback
    if (preUpdateCallback != NULL) preUpdateCallback();

    if (!_beginUpdate(mode)) {
      EOTA_SEND(400, "text/plain", _update_error_str.c_str());
      return;
    }

    // Update.begin() clears any previously set digest, so the expected hash
    // has to be handed over afterwards to actually be checked.
    if (hash.length() && !Update.setMD5(hash.c_str())) {
      ELEGANTOTA_DEBUG_MSG("ERROR: MD5 hash rejected by Update\n");
      _abortUpdate();
      EOTA_SEND(400, "text/plain", "That MD5 digest is not valid");
      return;
    }

    EOTA_SEND(200, "text/plain", "OK");
  }));

  // Browser upload
  #if ELEGANTOTA_USE_ASYNC_WEBSERVER == 1
    _server->on("/ota/upload", HTTP_POST, [&](AsyncWebServerRequest *request) {
        if(_authenticate && !request->authenticate(_username.c_str(), _password.c_str())){
          return request->requestAuthentication();
        }
        // Post-OTA update callback
        if (postUpdateCallback != NULL) postUpdateCallback(!Update.hasError());
        AsyncWebServerResponse *response = request->beginResponse((Update.hasError()) ? 400 : 200, "text/plain", (Update.hasError()) ? _update_error_str.c_str() : "OK");
        response->addHeader("Connection", "close");
        response->addHeader("Access-Control-Allow-Origin", "*");
        request->send(response);
        // Set reboot flag
        if (!Update.hasError()) {
          if (_auto_reboot) {
            _reboot_request_millis = millis();
            _reboot = true;
          }
        }
    }, [&](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
        //Upload handler chunks in data
        if(_authenticate){
            if(!request->authenticate(_username.c_str(), _password.c_str())){
                return request->requestAuthentication();
            }
        }

        if (!index) {
          // Reset progress size on first frame
          _current_progress_size = 0;
        }

        // Write chunked data to the free sketch space
        if(len){
            if (Update.write(data, len) != len) {
                return request->send(400, "text/plain", "Failed to write chunked data to free space");
            }
            _current_progress_size += len;
            // Progress update callback
            if (progressUpdateCallback != NULL) progressUpdateCallback(_current_progress_size, request->contentLength());
        }

        if (final) { // if the final flag is set then this is the last frame of data
            if (!Update.end(true)) { //true to set the size to the current progress
                _captureUpdateError();
            }
        }else{
            return;
        }
    });
  #else
    _server->on("/ota/upload", HTTP_POST, [&](){
      if (_authenticate && !_server->authenticate(_username.c_str(), _password.c_str())) {
        return _server->requestAuthentication();
      }
      // Post-OTA update callback
      if (postUpdateCallback != NULL) postUpdateCallback(!Update.hasError());
      _server->sendHeader("Connection", "close");
      _server->send((Update.hasError()) ? 400 : 200, "text/plain", (Update.hasError()) ? _update_error_str.c_str() : "OK");
      // Set reboot flag
      if (!Update.hasError()) {
        if (_auto_reboot) {
          _reboot_request_millis = millis();
          _reboot = true;
        }
      }
    }, [&](){
      // Actual OTA Download
      HTTPUpload& upload = _server->upload();
      if (upload.status == UPLOAD_FILE_START) {
        // Check authentication
        if (_authenticate && !_server->authenticate(_username.c_str(), _password.c_str())) {
          ELEGANTOTA_DEBUG_MSG("Authentication Failed on UPLOAD_FILE_START\n");
          return;
        }
        ELEGANTOTA_DEBUG_MSG(String("Update Received: "+upload.filename+"\n").c_str());
        _current_progress_size = 0;
      } else if (upload.status == UPLOAD_FILE_WRITE) {
          if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
            #if UPDATE_DEBUG == 1
              Update.printError(Serial);
            #endif
          }

          _current_progress_size += upload.currentSize;
          // Progress update callback
          if (progressUpdateCallback != NULL) progressUpdateCallback(_current_progress_size, upload.totalSize);
      } else if (upload.status == UPLOAD_FILE_END) {
          if (Update.end(true)) {
              ELEGANTOTA_DEBUG_MSG(String("Update Success: "+String(upload.totalSize)+"\n").c_str());
          } else {
              ELEGANTOTA_DEBUG_MSG("[!] Update Failed\n");
              _captureUpdateError();
          }

          #if UPDATE_DEBUG == 1
            Serial.setDebugOutput(false);
          #endif
      } else {
        ELEGANTOTA_DEBUG_MSG(String("Update Failed Unexpectedly (likely broken connection): status="+String(upload.status)+"\n").c_str());
      }
    });
  #endif
}

// ---------------------------------------------------------------------------
// Configuration
// ---------------------------------------------------------------------------

void ElegantOTAClass::setAuth(const char * username, const char * password){
  _username = username;
  _password = password;
  _authenticate = _username.length() && _password.length();
}

void ElegantOTAClass::clearAuth(){
  _authenticate = false;
}

void ElegantOTAClass::setAutoReboot(bool enable){
  _auto_reboot = enable;
}

void ElegantOTAClass::loop() {
  // Check if 2 seconds have passed since _reboot_request_millis was set
  if (_reboot && millis() - _reboot_request_millis > 2000) {
    ELEGANTOTA_DEBUG_MSG("Rebooting...\n");
    #if defined(ESP8266) || defined(ESP32)
      ESP.restart();
    #elif defined(TARGET_RP2040) || defined(TARGET_RP2350) || defined(PICO_RP2040) || defined(PICO_RP2350)
      rp2040.reboot();
    #endif
    _reboot = false;
  }
}

void ElegantOTAClass::onStart(std::function<void()> callable){
    preUpdateCallback = callable;
}

void ElegantOTAClass::onProgress(std::function<void(size_t current, size_t final)> callable){
    progressUpdateCallback= callable;
}

void ElegantOTAClass::onEnd(std::function<void(bool success)> callable){
    postUpdateCallback = callable;
}

ElegantOTAClass ElegantOTA;

#include "ElegantESPAsyncServer.h"


void ElegantESPAsyncServer::begin(AsyncWebServer *server, const char* username, const char* password){
    _server = server;

    if(strlen(username) > 0){
        _authenticate = true;
        _username = username;
        _password = password;
    }else{
        _authenticate = false;
        _username = "";
        _password = "";
    }

    _server->on("/update/identity", HTTP_GET, [&](AsyncWebServerRequest *request){
        if(_authenticate){
            if(!request->authenticate(_username.c_str(), _password.c_str())){
                return request->requestAuthentication();
            }
        }
        #if defined(ESP8266)
            request->send(200, "application/json", "{\"id\": \""+_id+"\", \"hardware\": \"ESP8266\"}");
        #elif defined(ESP32)
            request->send(200, "application/json", "{\"id\": \""+_id+"\", \"hardware\": \"ESP32\"}");
        #endif
    });

    _server->on("/update", HTTP_GET, [&](AsyncWebServerRequest *request){
        if(_authenticate){
            if(!request->authenticate(_username.c_str(), _password.c_str())){
                return request->requestAuthentication();
            }
        }
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", ELEGANT_HTML, ELEGANT_HTML_SIZE);
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });

    _server->on("/update", HTTP_POST, [&](AsyncWebServerRequest *request) {
        if(_authenticate){
            if(!request->authenticate(_username.c_str(), _password.c_str())){
                return request->requestAuthentication();
            }
        }
        // the request handler is triggered after the upload has finished... 
        // create the response, add header, and send response
        AsyncWebServerResponse *response = request->beginResponse((Update.hasError())?500:200, "text/plain", (Update.hasError())?"FAIL":"OK");
        response->addHeader("Connection", "close");
        response->addHeader("Access-Control-Allow-Origin", "*");
        request->send(response);
        restart();
    }, [&](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
        //Upload handler chunks in data
        if(_authenticate){
            if(!request->authenticate(_username.c_str(), _password.c_str())){
                return request->requestAuthentication();
            }
        }

        // Start OTA Callback
        if (_on_ota_start_ptr != NULL) {
            bool ok = (*_on_ota_start_ptr)();
            if (!ok) {
                return _server->send(500, "text/plain", "Task aborted. Application is busy.");
            }
        }

        if (!index) {
            if(!request->hasParam("MD5", true)) {
                
                return request->send(400, "text/plain", "MD5 parameter missing");
            }

            if(!Update.setMD5(request->getParam("MD5", true)->value().c_str())) {
                if (_on_ota_fail_ptr != NULL) {
                    (*_on_ota_fail_ptr)();
                }
                return request->send(400, "text/plain", "MD5 parameter invalid");
            }

            #if defined(ESP8266)
                int cmd = (filename == "filesystem") ? U_FS : U_FLASH;
                Update.runAsync(true);
                size_t fsSize = ((size_t) &_FS_end - (size_t) &_FS_start);
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if (!Update.begin((cmd == U_FS)?fsSize:maxSketchSpace, cmd)){ // Start with max available size
            #elif defined(ESP32)
                int cmd = (filename == "filesystem") ? U_SPIFFS : U_FLASH;
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd)) { // Start with max available size
            #endif
                Update.printError(Serial);
                return request->send(400, "text/plain", "OTA could not begin");
            }
        }

        // Write chunked data to the free sketch space
        if(len){
            if (Update.write(data, len) != len) {
                if (_on_ota_fail_ptr != NULL) {
                    (*_on_ota_fail_ptr)();
                }
                return request->send(400, "text/plain", "OTA could not begin");
            }
        }
            
        if (final) { // if the final flag is set then this is the last frame of data
            if (!Update.end(true)) { //true to set the size to the current progress
                Update.printError(Serial);
                if (_on_ota_fail_ptr != NULL) {
                    (*_on_ota_fail_ptr)();
                }
                return request->send(400, "text/plain", "Could not end OTA");
            } else {
                ELEGANTOTA_DEBUG_LOG("[ElegantOTA] OTA update Success");
                if (_on_ota_success_ptr != NULL) {
                    (*_on_ota_success_ptr)();
                }
            }

            if (_on_ota_end_ptr != NULL) {
                (*_on_ota_end_ptr)();
            }
        }
    });
}
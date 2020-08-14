#ifndef ElegantOTA_h
#define ElegantOTA_h

#include "Arduino.h"
#include "stdlib_noniso.h"
#include "elegantWebpage.h"

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
        
        void setID(const char* id){
            _id = id;
        }

        // ESP8266 Codebase
        #if defined(ESP8266)
        
            void begin(ESP8266WebServer *server, const char * username = "", const char * password = ""){
                _server = server;

				if(strlen(username) > 0){

                    _username = username;
                    _password = password;

					_server->on("/update", HTTP_GET, [&](){
						if (!_server->authenticate(_username.c_str(), _password.c_str())) {
						  return _server->requestAuthentication();
						}
						_server->sendHeader("Content-Encoding", "gzip");
						_server->send_P(200, "text/html", (const char*)ELEGANT_HTML, ELEGANT_HTML_SIZE);
					});

                    _server->on("/update/identity", HTTP_GET, [&](){
                        if (!_server->authenticate(_username.c_str(), _password.c_str())) {
						  return _server->requestAuthentication();
						}

                        #if defined(ESP8266)
                            _server->send(200, "application/json", "{\"id\": "+_id+", \"hardware\": \"ESP8266\"}");
                        #elif defined(ESP32)
                            _server->send(200, "application/json", "{\"id\": "+_id+", \"hardware\": \"ESP32\"}");
                        #endif
					});
                    
                    _httpUpdater.setup(server, "/update", _username.c_str(), _password.c_str());

				} else {

					_server->on("/update", HTTP_GET, [&](){
						_server->sendHeader("Content-Encoding", "gzip");
						_server->send_P(200, "text/html", (const char*)ELEGANT_HTML, ELEGANT_HTML_SIZE);
					});

                    _server->on("/update/identity", HTTP_GET, [&](){
                        #if defined(ESP8266)
                            _server->send(200, "application/json", "{\"id\": "+_id+", \"hardware\": \"ESP8266\"}");
                        #elif defined(ESP32)
                            _server->send(200, "application/json", "{\"id\": "+_id+", \"hardware\": \"ESP32\"}");
                        #endif
					});

					//TODO: handle MD5 paramter
                    _httpUpdater.setup(server, "/update");
				
                }
            }
        
        // ESP32 Codebase
        #elif defined(ESP32)

            void begin(WebServer *server, const char * username = "", const char * password = ""){
                _server = server;

				if(strlen(username) > 0){

                    _username = username;
                    _password = password;

					_server->on("/update", HTTP_GET, [&](){
						if (!_server->authenticate(_username.c_str(), _password.c_str())) {
						  return _server->requestAuthentication();
						}
						_server->sendHeader("Content-Encoding", "gzip");
						_server->send_P(200, "text/html", (const char*)ELEGANT_HTML, ELEGANT_HTML_SIZE);
					});

                    _server->on("/update/identity", HTTP_GET, [&](){
                        if (!_server->authenticate(_username.c_str(), _password.c_str())) {
						  return _server->requestAuthentication();
						}
                        #if defined(ESP8266)
                            _server->send(200, "application/json", "{\"id\": \""+_id+"\", \"hardware\": \"ESP8266\"}");
                        #elif defined(ESP32)
                            _server->send(200, "application/json", "{\"id\": \""+_id+"\", \"hardware\": \"ESP32\"}");
                        #endif
					});

                    _server->on("/update", HTTP_POST, [&](){
                        // Check Authentication before processing request
                        if (!_server->authenticate(_username.c_str(), _password.c_str())) {
						  return;
						}
                        _server->sendHeader("Connection", "close");
                        _server->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
                        ESP.restart();
                    }, [&](){
                        // Check Authentication before processing request
                        if (!_server->authenticate(_username.c_str(), _password.c_str())) {
						  return;
						}
						//TODO: handle MD5 paramter

                        // Perform upload
                        HTTPUpload& upload = _server->upload();
                        if (upload.status == UPLOAD_FILE_START) {
                            Serial.setDebugOutput(true);
                            Serial.printf("Update: %s\n", upload.filename.c_str());
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

				} else {

					_server->on("/update", HTTP_GET, [&](){
						_server->sendHeader("Content-Encoding", "gzip");
						_server->send_P(200, "text/html", (const char*)ELEGANT_HTML, ELEGANT_HTML_SIZE);
					});

                    _server->on("/update/identity", HTTP_GET, [&](){
                        #if defined(ESP8266)
                            _server->send(200, "application/json", "{\"id\": \""+_id+"\", \"hardware\": \"ESP8266\"}");
                        #elif defined(ESP32)
                            _server->send(200, "application/json", "{\"id\": \""+_id+"\", \"hardware\": \"ESP32\"}");
                        #endif
					});

                    _server->on("/update", HTTP_POST, [&](){
                        _server->sendHeader("Connection", "close");
                        _server->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
                        ESP.restart();
                    }, [&](){
						//TODO: handle MD5 paramter

                        // Perform upload
                        HTTPUpload& upload = _server->upload();
                        if (upload.status == UPLOAD_FILE_START) {
                            Serial.setDebugOutput(true);
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
				
                }
            }
        #endif

    private:
        #if defined(ESP8266)
            ESP8266WebServer *_server;
            ESP8266HTTPUpdateServer _httpUpdater;
        #endif
        #if defined(ESP32)
            WebServer *_server;
        #endif

        String getID(){
            String id = "";
            #if defined(ESP8266)
                id = String(ESP.getChipId());
            #elif defined(ESP32)
                id = String((uint32_t)ESP.getEfuseMac(), HEX);
            #endif
            id.toUpperCase();
            return id;
        }

        String _username;
        String _password;
        String _id = getID();
        
};

ElegantOtaClass ElegantOTA;
#endif

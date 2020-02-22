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
#endif


class ElegantOtaClass{
    public:
        
        void setID(const char* id){
            _id = id;
        }

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

                    _httpUpdater.setup(server, "/update");
				
                }
            }
        #endif

    private:
        #if defined(ESP8266)
            ESP8266WebServer *_server;
            ESP8266HTTPUpdateServer _httpUpdater;
        #endif
        String _username;
        String _password;
        String _id = String(ESP.getChipId());
};

ElegantOtaClass ElegantOTA;
#endif
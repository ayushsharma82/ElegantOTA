#ifndef ElegantOTA_h
#define ElegantOTA_h

#if defined(ESP8266)
    #include "Arduino.h"
    #include "stdlib_noniso.h"
    #include "elegantWebpage.h"
#endif

#if defined(ESP8266)
    #define HARDWARE "ESP8266"
    #include "ESP8266WiFi.h"
    #include "WiFiClient.h"
    #include "ESP8266WebServer.h"
    #include "ESP8266HTTPUpdateServer.h"
#endif

class ElegantOtaClass{
    public:
        #if defined(ESP8266)
            void begin(ESP8266WebServer *server, const char * username = "", const char * password = ""){
                _server = server;

				// If a username is actually given use authentication
				if(0 < strlen(username)){
					_username = username;
					_password = password;
					_server->on("/update", HTTP_GET, [&](){
						if (!_server->authenticate(_username, _password)) {
						  return _server->requestAuthentication();
						}
						_server->sendHeader("Content-Encoding", "gzip");
						_server->send_P(200, "text/html", (const char*)ELEGANT_HTML, ELEGANT_HTML_SIZE);
					});
				} else {
					_server->on("/update", HTTP_GET, [&](){
						_server->sendHeader("Content-Encoding", "gzip");
						_server->send_P(200, "text/html", (const char*)ELEGANT_HTML, ELEGANT_HTML_SIZE);
					});
				}                

                _httpUpdater.setup(server);
            }
        #endif

    private:
        #if defined(ESP8266)
            ESP8266WebServer *_server;
            ESP8266HTTPUpdateServer _httpUpdater;
			const char * _username;
			const char * _password;
        #endif
};

ElegantOtaClass ElegantOTA;
#endif
#include "ElegantOTA.h"

ElegantOtaClass::ElegantOtaClass() {
#if defined(ESP8266)
  this->setID(String((uint32_t)ESP.getChipId(), HEX).c_str());
#elif defined(ESP32)
  this->setID(String((uint32_t)ESP.getEfuseMac(), HEX).c_str());
#endif
  verify = false;
}


void ElegantOtaClass::setDigitalSignature(UpdaterHashClass* hash, DigitalSignatureVerifier* verifier)
{
	_hash = hash;
	_verifier = verifier;
	verify = true;
}
	
void ElegantOtaClass::setID(const char* id) {
#if defined(ESP8266)
  snprintf(_id, sizeof(_id), "{ \"id\": \"%s\", \"hardware\": \"ESP8266\" }", id);
#elif defined(ESP32)
  snprintf(_id, sizeof(_id), "{ \"id\": \"%s\", \"hardware\": \"ESP32\" }", id);
#endif
}

#if defined(ESP8266)
void ElegantOtaClass::begin(ESP8266WebServer *server, const char * username, const char * password) {
#elif defined(ESP32)
void ElegantOtaClass::begin(WebServer * server, const char * username, const char * password) {
#endif
  _server = server;

  if (strlen(username) > 0) {
    strlcpy(_username, username, sizeof(_username));
    strlcpy(_password, password, sizeof(_password));
    authenticate = true;
  }

  _server->on("/update", HTTP_GET, [&]() {
    if (authenticate && !_server->authenticate(_username, _password)) {
      return _server->requestAuthentication();
    }
    _server->sendHeader("Content-Encoding", "gzip");
    _server->send_P(200, "text/html", (const char*)ELEGANT_HTML, ELEGANT_HTML_SIZE);
  });

  _server->on("/update/identity", HTTP_GET, [&]() {
    if (authenticate && !_server->authenticate(_username, _password)) {
      return _server->requestAuthentication();
    }
    _server->send(200, "application/json", _id);
  });

  _server->on("/update", HTTP_POST, [&]() {
    if (authenticate && !_server->authenticate(_username, _password)) {
      return;
    }
    _server->sendHeader("Connection", "close");
    _server->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
#if defined(ESP32)
    // Needs some time for Core 0 to send response
    delay(100);
    yield();
#endif
    delay(100);
    ESP.restart();
  }, [&]() {
    // Actual OTA Download
    if (authenticate && !_server->authenticate(_username, _password)) {
      return;
    }

    HTTPUpload& upload = _server->upload();
    if (upload.status == UPLOAD_FILE_START) {
      // Serial output must be active to see the callback serial prints
      //            Serial.setDebugOutput(true);
      //            Serial.printf("Update Received: %s\n", upload.filename.c_str());
      if (_preUpdateRequired) preUpdateCallback();
	  if(verify)
	  {
		_sig_len = 0;
		_hash->begin();
	  }
      if (upload.name == "filesystem") {
#if defined(ESP32)
        if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_SPIFFS)) { //start with max available size
          Update.printError(Serial);
        }
#elif defined(ESP8266)
        size_t fsSize = ((size_t)FS_end - (size_t)FS_start);
        close_all_fs();
        if (!Update.begin(fsSize, U_FS)) { //start with max available size
          Update.printError(Serial);
        }
#endif
      } else {
#if defined(ESP32)
        if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_FLASH)) { //start with max available size
          Update.printError(Serial);
        }
#elif defined(ESP8266)
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        if (!Update.begin(maxSketchSpace, U_FLASH)) { //start with max available size
          Update.printError(Serial);
        }
#endif
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      _updateData = upload.buf;
      _updateDataLen = upload.currentSize;
	  if (_sig_len < _verifier->getSigLen())
	  {
		if (_updateDataLen >= (_verifier->getSigLen() - _sig_len))
		{
			memcpy(&_verifier->signature[_sig_len], upload.buf, _verifier->getSigLen() - _sig_len);
			_updateDataLen = _updateDataLen - (_verifier->getSigLen() - _sig_len);
			_updateData = &upload.buf[_verifier->getSigLen() - _sig_len];
			_sig_len += (_verifier->getSigLen() - _sig_len);
		}
		else
		{
			memcpy(&_verifier->signature[_sig_len], upload.buf, _updateDataLen);
			_sig_len += _updateDataLen;
			_updateDataLen = 0;
			_updateData = NULL;
	    } 
      }
      if (_updateDataLen > 0)
      {
        if (Update.write(_updateData, _updateDataLen) != _updateDataLen) {
          Update.printError(Serial);
        }
		if(verify)
		{
			_hash->add(_updateData, _updateDataLen);
		}
        if (_progressUpdateRequired) progressUpdateCallback();
      }
    } else if (upload.status == UPLOAD_FILE_END) {
	  if(verify)
	  {
		bool signature_verification = true;
		_hash->end();
		signature_verification = _verifier->verify(_hash, _verifier->signature, _verifier->getSigLen());
		if (!signature_verification)
		{
			if (Update.end(true)) { //true to set the size to the current progress
			//                Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
			} else {
				Update.printError(Serial);
			}
		}
		else
		{
	#if defined(ESP32)
        Update.abort();
	#elif defined(ESP8266)
        Update.end();
	#endif
		}
	  }
	  else
	  {
		  if (Update.end(true)) { //true to set the size to the current progress
			//                Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
		  } else {
			Update.printError(Serial);
		  }
	  }
      if (_postUpdateRequired) postUpdateCallback();
      //            Serial.setDebugOutput(false);
    } else {
      //            Serial.printf("Update Failed Unexpectedly (likely broken connection): status=%d\n", upload.status);
    }
#if defined(ESP8266)
    esp_yield();
#endif
  });
}

void ElegantOtaClass::onOTAStart(void callable(void)) {
  preUpdateCallback = callable;
  _preUpdateRequired = true ;
}

void ElegantOtaClass::onOTAProgress(void callable(void)) {
  progressUpdateCallback = callable;
  _progressUpdateRequired = true ;
}

void ElegantOtaClass::onOTAEnd(void callable(void)) {
  postUpdateCallback = callable;
  _postUpdateRequired = true ;
}

ElegantOtaClass ElegantOTA;

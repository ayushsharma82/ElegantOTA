#ifndef elegantota_common_h
#define elegantota_common_h

#include <cstdint>
#include <string.h>

#include "elegantWebpage.h"

#ifndef ELEGANTOTA_DEBUG
    #define ELEGANTOTA_DEBUG 1
#endif

#ifdef ARDUINO
    #include <Arduino.h>

    #if defined(ESP8266)
        #define EOTA_HARDWARE "ESP8266"
    #elif defined(ESP32)
        #define EOTA_HARDWARE "ESP32"
    #endif

    #ifndef ELEGANTOTA_DEBUG_PORT
        #define ELEGANTOTA_DEBUG_PORT Serial
    #endif

    #if ELEGANTOTA_DEBUG == 1
        #define ELEGANTOTA_DEBUG_LOG(...) ELEGANTOTA_DEBUG_PORT.printf(__VA_ARGS__)
    #endif
#else
    #error "Unsupported ElegantOTA Platform! Please open an feature request on GitHub ( https://github.com/ayushsharma82/ElegantOTA ) for your platform support."
#endif

#if ELEGANTOTA_DEBUG == 0
    #define ELEGANTOTA_DEBUG_LOG(...)
#endif

#ifndef EOTA_HARDWARE
    #define EOTA_HARDWARE "Unknown"
#endif


enum ElegantOTACloudStatus {
    CL_OFFLINE = 0,
    CL_CONNECTING,
    CL_CONNECTED,
    CL_UPDATING,
};

struct ElegantOTAState {
    // Base variables
    bool show_identity = true;
    bool show_hardware = true;
    bool show_mac_address = true;
    bool disable_fw_upload = false;
    bool disable_fs_upload = false;
    bool auto_reboot = true;
    char id[32];
    char mac_address[18];
    char hardware[32] = EOTA_HARDWARE;
    uint16_t logo_width = 180;
    // Reserved Variables
    uint8_t cloud_status = CL_OFFLINE;
    uint8_t cloud_progress = 0;
    char firmware_id[32];
    char firmware_etag[32];
    unsigned long last_checked_at;
};

class ElegantCommon {
    protected:
        struct ElegantOTAState _state;

        // Callbacks
        bool (*_on_ota_start_ptr)() = NULL;
        void (*_on_ota_progress_ptr)(uint8_t) = NULL;
        void (*_on_ota_success_ptr)() = NULL;
        void (*_on_ota_fail_ptr)() = NULL;
        void (*_on_ota_end_ptr)() = NULL;

        bool _trigger_ota_start();
        void _trigger_ota_progress(uint8_t progress);
        void _trigger_ota_fail();
        void _trigger_ota_success();
        void _trigger_ota_end();

    public:
        ElegantCommon();
        void showID(bool show);
        void showHardware(bool hide);
        void showMACAddress(bool hide);
        void disableFirmwareUpload(bool disable);
        void disableFSUpload(bool disable);
        void setAutoReboot(bool reboot);

        void setID(const char* id);
        void setMACAddress(const char* mac_address);
        void setHardware(const char* hardware);

        // Register Callbacks
        void onOTAStart(bool (*callback)());
        void onOTAProgress(void (*callback)(uint8_t));
        void onOTASuccess(void (*callback)());
        void onOTAFail(void (*callback)());
        void onOTAEnd(void (*callback)());
        ~ElegantCommon();
};


#endif
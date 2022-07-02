#include "ElegantCommon.h"


ElegantCommon::ElegantCommon() {
}

bool ElegantCommon::_trigger_ota_start() {
    if (_on_ota_start_ptr != NULL) {
        return _on_ota_start_ptr();
    } else {
        return true;
    }
}

void ElegantCommon::_trigger_ota_progress(uint8_t progress) {
    if (_on_ota_progress_ptr != NULL) {
        _on_ota_progress_ptr(progress);
    }
}

void ElegantCommon::_trigger_ota_fail() {
    if (_on_ota_fail_ptr != NULL) {
        _on_ota_fail_ptr();
    }
}

void ElegantCommon::_trigger_ota_success() {
    if (_on_ota_success_ptr != NULL) {
        _on_ota_success_ptr();
    }
}

void ElegantCommon::_trigger_ota_end() {
    if (_on_ota_end_ptr != NULL) {
        _on_ota_end_ptr();
    }
}

void ElegantCommon::showID(bool show) {
    _state.show_identity = show;
}

void ElegantCommon::showHardware(bool hide) {
    _state.show_hardware = hide;
}

void ElegantCommon::showMACAddress(bool hide) {
    _state.show_mac_address = hide;
}

void ElegantCommon::disableFirmwareUpload(bool disable) {
    _state.disable_fw_upload = disable;
}

void ElegantCommon::disableFSUpload(bool disable) {
    _state.disable_fs_upload = disable;
}

void ElegantCommon::setAutoReboot(bool reboot) {
    _state.auto_reboot = reboot;
}

void ElegantCommon::setID(const char* id) {
    strncpy(_state.id, id, sizeof(_state.id));
}

void ElegantCommon::setMACAddress(const char* mac_address) {
    strncpy(_state.mac_address, mac_address, sizeof(_state.mac_address));
}

void ElegantCommon::setHardware(const char* hardware) {
    strncpy(_state.hardware, hardware, sizeof(_state.hardware));
}

void ElegantCommon::onOTAStart(bool (*callback)()) {
    _on_ota_start_ptr = callback;
}

void ElegantCommon::onOTAProgress(void (*callback)(uint8_t)) {
    _on_ota_progress_ptr = callback;
}

void ElegantCommon::onOTASuccess(void (*callback)()) {
    _on_ota_success_ptr = callback;
}

void ElegantCommon::onOTAFail(void (*callback)()) {
    _on_ota_fail_ptr = callback;
}

void ElegantCommon::onOTAEnd(void (*callback)()) {
    _on_ota_end_ptr = callback;
}

ElegantCommon::~ElegantCommon() {
}
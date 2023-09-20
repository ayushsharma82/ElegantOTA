---
title: Disable Firmware OTA
sidebar_label: Disable Firmware OTA (Pro)
sidebar_position: 8
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is only available in <a target="_blank" style={{ color: "red" }} href="https://elegantota.pro">ElegantOTA Pro</a>.
        </h4>
         
    </i>
</div>

<br/>
<br/>

<img src="/v3/img/ota-modes.png" alt="Modes" width="400px" />

<br/>
<br/>

ElegantOTA allows you to selective enable or disable OTA modes of your choice for security reasons or when you have a important task running where you don't want it to get interrupted by an OTA update. This will be represented in the portal (ElegantOTA webpage) too.

This function should be used very carefully as it blocks firmware update! If by mistake this is left disabled, your device will not be recoverable by an OTA update.


#### Disable Firmware OTA:
```cpp
// Pass 'false' to disable Firmware mode
ElegantOTA.setFirmwareMode(false);
```

#### Enable Firmware OTA:
```cpp
// Pass 'true' to enable Firmware mode
ElegantOTA.setFirmwareMode(true);
```

#### Get Firmware OTA mode status:
```cpp
// You can use this logic inside a function if neccessary
if(ElegantOTA.checkFirmwareMode() == true) {
    Serial.println("Firmware mode is enabled");
} else {
    Serial.println("Firmware mode is disabled");
}
```
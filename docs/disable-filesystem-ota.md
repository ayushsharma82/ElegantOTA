---
title: Disable Filesystem OTA
sidebar_label: Disable Filesystem OTA (Pro)
sidebar_position: 9
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

<!-- <img src="/img/v4/tabs.png" alt="Concept Diagram" width="300px" /> -->

<!-- <br/> -->
<!-- <br/> -->

ElegantOTA allows you to selective enable or disable OTA modes of your choice for security reasons or when you have a important task running where you don't want it to get interrupted by an OTA update. This will be represented in the portal (ElegantOTA webpage) too.

Using these functions you can enable or disable filesystem updates ( SPIFFS or LittleFS ).

#### Disable Filesystem OTA:
```cpp
// Pass 'false' to disable Filesystem mode
ElegantOTA.setFilesystemMode(true);
```

#### Enable Filesystem OTA:
```cpp
// Pass 'true' to enable Filesystem mode
ElegantOTA.setFilesystemMode(false);
```

#### Get Filesystem OTA mode status:
```cpp
// You can use this logic inside a function if neccessary
if(ElegantOTA.checkFilesystemMode() == true) {
    Serial.println("Filesystem mode is enabled");
} else {
    Serial.println("Filesystem mode is disabled");
}
```

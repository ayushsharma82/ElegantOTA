---
title: Firmware Version
sidebar_label: Firmware Version (Pro)
sidebar_position: 10
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is only available in <a target="_blank" style={{ color: "red" }} href="https://elegantota.pro">ElegantOTA Pro</a>.
        </h4>
         
    </i>
</div>

<!-- <br/> -->
<!-- <br/> -->

<!-- <img src="/img/v4/tabs.png" alt="Concept Diagram" width="300px" /> -->

<!-- <br/> -->
<!-- <br/> -->

## Introduction

The Firmware Version feature in ElegantOTA allows you to specify and manage the version of the firmware running on your Internet of Things (IoT) devices. By setting a firmware version, you can easily track and control the software running on your devices, making it simpler to perform updates, monitor compatibility, and manage your IoT ecosystem effectively.

You can set the Firmware Version for your device using the `ElegantOTA.setFWVersion("version");` function.

### Example Usage:

```cpp
#include <ElegantOTA.h>

void setup() {
  // Initialize your hardware and other configurations here

  // Set the Firmware Version
  ElegantOTA.setFWVersion("v1.0.0");

  // Additional setup code
}

void loop() {
  // Your main loop code here
}
```

In the above example, the `ElegantOTA.setFWVersion("v1.0.0");` function call assigns the firmware version "v1.0.0" to the device.

## Use Cases

The Firmware Version feature can be beneficial in various scenarios:

1. **Firmware Updates**: When new firmware versions become available, the Firmware Version identifier helps you check if an update is necessary. It also allows you to verify that devices have received the correct update.

2. **Compatibility**: By knowing the firmware version of each device, you can ensure that all components of your IoT network are compatible. This is especially important when devices communicate or interact with each other.

3. **Historical Tracking**: You can maintain a history of firmware versions installed on each device, which can be useful for troubleshooting issues or understanding the evolution of your firmware.

4. **Remote Diagnostics**: When diagnosing issues remotely, having access to the firmware version can help you identify potential problems related to specific software releases.

## Best Practices

To make the most of the Firmware Version feature, consider the following best practices:

- Follow a consistent versioning scheme for your firmware, such as Semantic Versioning (SemVer), to ensure clarity and compatibility tracking.

- Set the firmware version during the device's initialization phase, such as in the `setup()` function, to guarantee that it accurately reflects the installed firmware.

- When updating firmware, always ensure that the new version is correctly set using `ElegantOTA.setFWVersion()` to maintain accurate version information.

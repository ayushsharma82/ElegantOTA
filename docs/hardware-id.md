---
title: Hardware ID
sidebar_label: Hardware ID (Pro)
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

The Hardware ID feature in ElegantOTA is shown on the ElegantOTA Pro portal. This ID should be a unique string that helps you easily identify the specific hardware device among others in your network.

### Example Usage:

```cpp
#include <ElegantOTA.h>

void setup() {
  // Initialize your hardware and other configurations here

  // Set the Hardware ID
  ElegantOTA.setID("my_device_001");

  // Additional setup code
}

void loop() {
  // Your main loop code here
}
```

In the above example, the `ElegantOTA.setID("my_device_001");` function call assigns the Hardware ID "my_device_001" to the device.


## Best Practices

To make the most of the Hardware ID feature, consider the following best practices:

- Choose a Hardware ID that is unique to each device to avoid conflicts.

- Avoid using special characters or spaces in the Hardware ID, as these might cause issues when used in network communication or file naming.

- Document and keep track of the Hardware IDs for all your devices to ensure proper management.

- Ensure that the Hardware ID is set during the device's initialization phase, such as in the `setup()` function, to guarantee that it is properly configured before any network or communication activities.

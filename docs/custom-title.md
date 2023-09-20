---
title: Custom Title
sidebar_label: Custom Title (Pro)
sidebar_position: 12
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is only available in <a target="_blank" style={{ color: "red" }} href="https://elegantota.pro">ElegantOTA Pro</a>.
        </h4>
         
    </i>
</div>

<br/>

<img src="/v3/img/custom-title.png" alt="Custom Title" width="400px" />

<br/>


## Overview 

The `setTitle()` function is a method provided by the ElegantOTA Pro library. It is used to set the title of the OTA (Over-The-Air) update portal. This title is displayed at the top of the update portal web page, providing a user-friendly and customizable interface for managing firmware updates.

## Syntax

```cpp
void setTitle(const char* title);
```

## Example

```cpp
#include <ElegantOTA.h>

void setup() {
  // Initialize the ElegantOTA library
  ElegantOTA.begin();

  // Set the title of the OTA update portal
  ElegantOTA.setTitle("OTA Update - XYZ Inc");
}

void loop() {
  // Your main program loop
}
```

## Usage

1. Include the ElegantOTA library in your Arduino sketch.
2. In the `setup()` function of your sketch, initialize the ElegantOTA library using `ElegantOTA.begin()`.
3. Use the `setTitle()` function to set a meaningful title for your OTA update portal. This title will be displayed at the top of the update portal web page when users access it.
4. Continue with the rest of your sketch's setup and loop functions.

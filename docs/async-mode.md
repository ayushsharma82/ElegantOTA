---
title: Async Mode
sidebar_label: Async Mode
sidebar_position: 7
---

## Introduction

One of the features of ElegantOTA is the async mode, which provides asynchronous web server functionality for handling OTA updates. This mode should only be enabled if you are using ESPAsyncWebServer library in your project/firmware.

## Enabling Async Mode

To enable async mode for ElegantOTA, follow these steps:

1. Locate the `ELEGANTOTA_USE_ASYNC_WEBSERVER` macro in the `ElegantOTA.h` file, and set it to `1`:

   ```cpp
   #define ELEGANTOTA_USE_ASYNC_WEBSERVER 1
   ```

2. Save the changes to the `ElegantOTA.h` file.

3. You are now ready to use ElegantOTA in async mode for your OTA updates, utilizing the ESPAsyncWebServer library.

## Benefits of Async Mode

Enabling async mode for ElegantOTA offers several advantages:

1. **Non-blocking Operation:** In async mode, ElegantOTA leverages the asynchronous web server capabilities of ESPAsyncWebServer. This means that OTA updates won't block your device's main loop. It allows your device to continue executing other tasks while handling OTA updates in the background.

2. **Improved Responsiveness:** Your device can remain responsive to user interactions or other processes during OTA updates, ensuring a smoother user experience.

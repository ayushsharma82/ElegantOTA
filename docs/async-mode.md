---
title: Async Mode
sidebar_label: Async Mode
sidebar_position: 7
---

## Introduction

One of the features of ElegantOTA is the async mode, which provides asynchronous web server functionality for handling OTA updates. This mode should only be enabled if you are using ESPAsyncWebServer library in your project/firmware.


### Dependencies

#### For ESP8266

- (mathieucarbou) [esphome-ESPAsyncTCP](https://github.com/mathieucarbou/esphome-ESPAsyncTCP#v2.0.0) - **v2.0.0**
- (mathieucarbou) [ESPAsyncWebServer](https://github.com/mathieucarbou/ESPAsyncWebServer#v3.0.3) - **v3.0.3**

#### For ESP32

- (mathieucarbou) [AsyncTCP](https://github.com/mathieucarbou/AsyncTCP#v3.1.4) @ **v3.1.4**
- (mathieucarbou) [ESPAsyncWebServer](https://github.com/mathieucarbou/ESPAsyncWebServer#v3.0.3) - **v3.0.3**

#### For RP2040+W

- (khoih-prog) [AsyncTCP_RP2040W](https://github.com/khoih-prog/AsyncTCP_RP2040W#v1.2.0) @ **v1.2.0**
- (mathieucarbou) [ESPAsyncWebServer](https://github.com/mathieucarbou/ESPAsyncWebServer#v3.0.3) - **v3.0.3**

### Enabling Async Mode

#### For Arduino IDE

1. Go to your Arduino libraries directory
2. Open `ElegantOTA` folder and then open `src` folder
3. Locate the `ELEGANTOTA_USE_ASYNC_WEBSERVER` macro in the `ElegantOTA.h` file, and set it to `1`:

   ```cpp
   #define ELEGANTOTA_USE_ASYNC_WEBSERVER 1
   ```

4. Save the changes to the `ElegantOTA.h` file.

5. You are now ready to use ElegantOTA in async mode for your OTA updates, utilizing the ESPAsyncWebServer library.

#### For PlatformIO

If you use PlatformIO then we can use a neat trick! You can set `build_flags` in your `platformio.ini` file that enables Async Mode of ElegantOTA.

1. Open `platformio.ini` file of your project
2. Paste this line `build_flags=-DELEGANTOTA_USE_ASYNC_WEBSERVER=1` at bottom
3. Done!

PlatformIO will now compile ElegantOTA in Async Mode!

### Benefits of Async Mode

Enabling async mode for ElegantOTA offers several advantages:

1. **Non-blocking Operation:** In async mode, ElegantOTA leverages the asynchronous web server capabilities of ESPAsyncWebServer. This means that OTA updates won't block your device's main loop. It allows your device to continue executing other tasks while handling OTA updates in the background.

2. **Improved Responsiveness:** Your device can remain responsive to user interactions or other processes during OTA updates, ensuring a smoother user experience.

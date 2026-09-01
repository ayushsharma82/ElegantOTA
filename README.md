<p align="center">
  <a href="https://store.softt.io/products/elegantota-pro?ref=ghfeature" target="_blank">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="https://raw.githubusercontent.com/ayushsharma82/ElegantOTA/master/docs/banner-dark.jpg">
      <source media="(prefers-color-scheme: light)" srcset="https://raw.githubusercontent.com/ayushsharma82/ElegantOTA/master/docs/banner-light.jpg">
      <img alt="ElegantOTA Banner" src="https://raw.githubusercontent.com/ayushsharma82/ElegantOTA/master/docs/banner-dark.jpg">
    </picture>
  </a>
</p>

<p align="center">
  <img src="https://img.shields.io/github/v/release/ayushsharma82/ElegantOTA.svg?style=for-the-badge" alt="Latest release" />
  &nbsp;
  <img src="https://img.shields.io/github/actions/workflow/status/ayushsharma82/ElegantOTA/ci.yml?branch=master&style=for-the-badge" alt="Build status" />
  &nbsp;
  <img src="https://img.shields.io/github/last-commit/ayushsharma82/ElegantOTA.svg?style=for-the-badge" alt="Last commit" />
  &nbsp;
  <img src="https://img.shields.io/github/license/ayushsharma82/ElegantOTA.svg?style=for-the-badge" alt="License" />
</p>

<p align="center"><i>The original over-the-air update library for wireless microcontrollers (since 2019).</i></p>

ElegantOTA gives your microcontroller a polished web portal for over-the-air firmware and filesystem updates. Point a browser at `/update`, drop in a `.bin`, and watch it land - with live progress, transfer rate, and a capacity check that catches an oversized image before a single byte is written.

No HTML, no CSS, no JavaScript. Three lines of code.

<p align="center">
  <img src="https://raw.githubusercontent.com/ayushsharma82/ElegantOTA/master/docs/demo.gif" width="600" alt="ElegantOTA in action">
</p>

## Features

- 🔥 Quick & simple OTA procedure - firmware *and* filesystem images
- 📊 Live progress, transfer rate, and byte counts as the flash is written
- 🛟 Capacity check up front, so an oversized build is rejected before it half-writes
- 🔒 MD5 integrity verification and optional HTTP Basic auth
- 🌗 Light & dark portal themes, keyboard reachable, readable down to 320px
- 🎷 No need to learn HTML/CSS/JS
- 🛫 Ready to use within 3 lines of code

<br/>

## Supported MCUs

| Platform | Notes |
| --- | --- |
| **ESP32** | Including S2, S3, C3 and C6 variants |
| **RP2040 (+WiFi)** | e.g. Raspberry Pi Pico W - requires a LittleFS partition |
| **RP2350 (+WiFi)** | e.g. Raspberry Pi Pico 2 W - requires a LittleFS partition |
| **ESP8266** | Legacy - maintained, but new projects should prefer ESP32 or RP2350 |

> [!IMPORTANT]
> **RP2040 / RP2350 users:** these boards stage the incoming image inside the filesystem region, so a LittleFS partition is mandatory. In the Arduino IDE, pick `Tools > Flash Size > 2MB (Sketch 1MB, FS 1MB)` or similar. A bare RP2040/RP2350 without a WiFi chip cannot run ElegantOTA.

<br/>

## Installation

### Arduino IDE

`Sketch > Include Library > Manage Libraries…` → search for **ElegantOTA** → Install.

### PlatformIO

```ini
lib_deps =
  ayushsharma82/ElegantOTA@^4.0.0

; ElegantOTA supports several architectures, and PlatformIO will otherwise try
; to resolve dependencies for all of them. Without this you will hit build errors.
lib_compat_mode = strict
```

If you already have a `.pio/libdeps` folder, delete it before rebuilding.

<br/>

## Quick start

The whole integration is three lines - an include, a `begin()`, and a `loop()`:

```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <ElegantOTA.h>          // 1

WebServer server(80);

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin("ssid", "password");
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.on("/", []() {
    server.send(200, "text/plain", "Hi! This is ElegantOTA Demo.");
  });

  ElegantOTA.begin(&server);     // 2
  server.begin();
}

void loop() {
  server.handleClient();
  ElegantOTA.loop();             // 3
}
```

Open `http://<device-ip>/update` in a browser and you have the portal.

Full sketches live in [`examples/`](examples) - [`Demo`](examples/Demo/Demo.ino) for the synchronous webserver, [`AsyncDemo`](examples/AsyncDemo/AsyncDemo.ino) for `ESPAsyncWebServer`.

### Async mode

ElegantOTA can serve its routes through `ESPAsyncWebServer` instead of the built-in synchronous server. Enable it with a build flag:

```ini
build_flags = -D ELEGANTOTA_USE_ASYNC_WEBSERVER=1
```

The Arduino IDE has no way to set build flags, so there you edit `ELEGANTOTA_USE_ASYNC_WEBSERVER` in `src/ElegantOTA.h` directly. You cannot run the synchronous `WebServer` and `ESPAsyncWebServer` in the same firmware - pick one. See the [async mode guide](https://docs.elegantota.pro/getting-started/async-mode) for the per-platform TCP dependencies.

<!-- 
## What's new in 4.0.0

A rebuilt portal and an integrity check that finally does what it always claimed to. **The C++ API is unchanged - existing sketches compile and run untouched.**

- **Redesigned portal**, built around a capacity strip that draws the target flash region to scale and refuses an oversized image up front. Despite larger logo artwork it *shrank*: 10,214 → 8,839 bytes gzipped (−13.5%), after dropping Tailwind and the `md5` npm package for hand-written CSS and a compact MD5 implementation.
- **MD5 verification was silently doing nothing.** `Update.setMD5()` was called *before* `Update.begin()`, which clears the expected digest - so every upload since the feature landed went unverified. Corrupted and truncated uploads are now rejected.
- **Repeated OTA updates failed on RP2040/RP2350** with `ERROR[4]: Not Enough Space`. The update budget was the space that happened to be free rather than the filesystem region itself, so the second update after a cold boot was refused. Fixed, and these boards now report firmware capacity correctly.
- **New `/ota/metadata` endpoint** reporting chip family, both partition capacities, and the running build's size. No new configuration and no new public methods.

> [!WARNING]
> If your tooling was sending an MD5 digest that did not match the bytes it uploaded, those uploads used to succeed and will now be rejected. That is the intended behaviour - but worth knowing before rolling this out to a fleet.

Verified on ESP32, ESP8266, RP2040 (Pico W) and RP2350 (Pico 2 W), each with both the sync and async webservers. -->

<br/>

## Documentation

Installation, integration, security and feature guides: **[docs.elegantota.pro](https://docs.elegantota.pro)**

<br/>

## Looking for more? Upgrade to Pro.

ElegantOTA Lite covers a solid project end to end. ElegantOTA Pro adds the pieces a shipped product tends to need:

- Two extra OTA modes - **Direct Download** (the device fetches firmware from a URL itself) and **Auto Update** (update channels)
- Toggle OTA modes at runtime
- Hardware ID & firmware version on the UI
- Whitelabel / branding
- Commercial license

It is also a fantastic way to support the time that goes into building and maintaining the library.

<a href="https://store.softt.io/products/elegantota-pro" target="_blank">
  <img src="https://raw.githubusercontent.com/ayushsharma82/ElegantOTA/master/docs/pro-preview.png" alt="ElegantOTA Pro" width="600">
</a>

**Available at the [official store (store.softt.io)](https://store.softt.io/products/elegantota-pro).**

<br/>

## Contributing

Every contribution is highly appreciated. Spotted a bug? Open an issue or a pull request so it can be fixed for everyone.

**Feature requests:** open an issue and I'll look at adding it in a future release.

Contributors are asked to sign the [CLA](CLA.md), and participation is governed by the [Code of Conduct](CODE_OF_CONDUCT.md).

<br/>

## License

ElegantOTA open-source edition is licensed under the **GNU Affero General Public License v3.0 (AGPL-3.0)**.

If you are planning to use ElegantOTA in a commercial project, please consider purchasing [ElegantOTA Pro](https://store.softt.io/products/elegantota-pro), which comes with the less restrictive SOFTT Commercial License 1.3.

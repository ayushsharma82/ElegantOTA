# ESP32-SOLO-1 单核芯片 + ElegantOTA 完整方案
# ESP32-SOLO-1 Single-Core + ElegantOTA Complete Guide

> 作者 / Authors：董大爷 & 巴迪 | 日期 / Date：2026-06-19 | 芯片 / Chip：ESP32-SOLO-1 (Single-Core Xtensa LX6)

---

## 摘要 / Abstract

**中文**：ESP32-SOLO-1 是单核 ESP32 变体。默认的 arduino-esp32 SDK 以双核模式编译 FreeRTOS，会在启动时尝试初始化不存在的 Core0，导致 Guru Meditation 崩溃。本文记录了使用 **PlatformIO + pioarduino** 平台，通过 `custom_sdkconfig` 注入 `CONFIG_FREERTOS_UNICORE=y` 从根本上解决单核问题的完整过程。方案已实测验证：编译、OTA 上传（v1→v2→v3）、Web 上传全部通过。

**English**: The ESP32-SOLO-1 is a single-core ESP32 variant. The default arduino-esp32 SDK compiles FreeRTOS in dual-core mode, which attempts to initialize non-existent Core0 at startup, causing a Guru Meditation crash. This guide documents the complete solution using **PlatformIO + pioarduino**, injecting `CONFIG_FREERTOS_UNICORE=y` via `custom_sdkconfig` to fundamentally solve the single-core problem. The solution has been verified: compilation, OTA upload (v1→v2→v3), and web upload all pass.

---

## 一、问题诊断 / Problem Diagnosis

### 现象 / Symptoms

- 使用 Arduino IDE 或 PlatformIO 默认设置编译 → 烧录后设备反复重启
- Using Arduino IDE or PlatformIO default settings → device reboots repeatedly after flashing
- 串口输出 `Guru Meditation Error: Core 0 panic'ed`
- Serial output: `Guru Meditation Error: Core 0 panic'ed`
- 即使最简单的 Blink 程序也会崩溃
- Even the simplest Blink program crashes

### 根因 / Root Cause

**中文**：ESP32-SOLO-1 只有一个物理核心（Core1 / PRO_CPU），不存在 Core0（APP_CPU）。但 ESP-IDF FreeRTOS 默认以双核模式编译，启动时会调用 `vPortCPUInitializeMutex()` 等函数尝试初始化 Core0，导致访问不存在的硬件寄存器而崩溃。

**English**: The ESP32-SOLO-1 has only one physical core (Core1 / PRO_CPU); Core0 (APP_CPU) does not exist. However, ESP-IDF FreeRTOS is compiled in dual-core mode by default. During startup, it calls functions like `vPortCPUInitializeMutex()` to initialize Core0, which accesses non-existent hardware registers and triggers a crash.

```
FreeRTOS dual-core initialization:
  xPortStartScheduler()
    → prvStartFirstTask()
      → Attempts to start Core0 idle task
        → Accesses Core0 registers (non-existent)
          → Guru Meditation ❌
```

### 为什么 `-DCONFIG_FREERTOS_UNICORE=1` 无效？
### Why `-DCONFIG_FREERTOS_UNICORE=1` Doesn't Work

**中文**：`CONFIG_FREERTOS_UNICORE` 是 ESP-IDF 的 Kconfig 选项，必须在**编译 SDK 库时**生效，而不是在编译用户代码时。`build_flags = -DCONFIG_FREERTOS_UNICORE=1` 只影响用户代码的宏定义，不会改变已编译的 FreeRTOS 库行为。

**English**: `CONFIG_FREERTOS_UNICORE` is an ESP-IDF Kconfig option that must take effect **when compiling the SDK libraries**, not when compiling user code. `build_flags = -DCONFIG_FREERTOS_UNICORE=1` only affects user-code macros and does not change the behavior of pre-compiled FreeRTOS libraries.

---

## 二、解决方案：pioarduino + custom_sdkconfig
## Solution: pioarduino + custom_sdkconfig

### 核心机制 / Core Mechanism

**中文**：pioarduino（`pioarduino/platform-espressif32`）是 arduino-esp32 的 PlatformIO 适配分支，支持 `custom_sdkconfig` 指令，可以在编译前将配置写入 `sdkconfig`，从而让 FreeRTOS 以单核模式编译。

**English**: pioarduino (`pioarduino/platform-espressif32`) is a PlatformIO-adapted fork of arduino-esp32 that supports the `custom_sdkconfig` directive. This writes the configuration into `sdkconfig` before compilation, allowing FreeRTOS to be compiled in single-core mode.

### platformio.ini

```ini
[env:esp32-solo1]
; === Platform: use pioarduino fork (supports custom_sdkconfig) ===
; === 平台：使用 pioarduino fork（支持 custom_sdkconfig）===
platform = https://github.com/pioarduino/platform-espressif32.git
framework = arduino
board = esp32-solo1

; === KEY: Force single-core mode ===
; === 核心：强制单核模式 ===
; This line is critical — tells FreeRTOS at compile time that there's only one core
; 这行是关键——让 FreeRTOS 编译时就知道只有一个核
custom_sdkconfig =
    CONFIG_FREERTOS_UNICORE=y

; === ElegantOTA async mode ===
; === ElegantOTA 异步模式 ===
; Single-core MUST use async webserver or the device will be unresponsive during OTA
; 单核必须用异步 WebServer，否则 OTA 上传时设备无响应
build_flags =
    -DELEGANTOTA_USE_ASYNC_WEBSERVER=1

; === ElegantOTA dependencies ===
; === ElegantOTA 依赖 ===
lib_deps =
    ayushsharma82/ElegantOTA@^3.1.7
    ESP32Async/ESPAsyncWebServer@^3.7.3
    ESP32Async/AsyncTCP@^3.4.10

; === Upload settings ===
; === 上传参数 ===
upload_speed = 921600
monitor_speed = 115200

; OTA upload (for firmware with ArduinoOTA service)
; OTA 上传（适用于有 ArduinoOTA 服务的固件）
; upload_protocol = espota
; upload_port = 192.168.x.x
; upload_flags = --auth=admin
```

### 关键依赖版本 / Dependency Versions

| Library / 库 | Version / 版本 | Notes / 说明 |
|--------------|---------------|-------------|
| ElegantOTA | ^3.1.7 | Async mode requires `ELEGANTOTA_USE_ASYNC_WEBSERVER=1` |
| ESPAsyncWebServer | ^3.7.3 | ESP32Async fork, compatible with ESP32 arduino 3.x |
| AsyncTCP | ^3.4.10 | Use 3.x for ESP32 (2.x is for ESP8266) |

---

## 三、代码 / Code (main.cpp)

```cpp
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

AsyncWebServer server(80);

unsigned long ota_progress_millis = 0;

void onOTAStart() {
  Serial.println("OTA update started!");
}

void onOTAProgress(size_t current, size_t final) {
  if (millis() - ota_progress_millis > 1000) {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress: %u / %u bytes\n", current, final);
  }
}

void onOTAEnd(bool success) {
  if (success) {
    Serial.println("OTA update finished successfully!");
  } else {
    Serial.println("OTA update failed!");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n=== ESP32-SOLO-1 ElegantOTA Async ===");

  // Connect WiFi / 连接 WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Home page / 首页
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain",
      "ESP32-SOLO-1 ElegantOTA Async Mode\n"
      "Upload firmware at /update");
  });

  // Start ElegantOTA (async mode) / 启动 ElegantOTA（异步模式）
  ElegantOTA.begin(&server);
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  server.begin();
  Serial.print("OTA page: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/update");
}

void loop() {
  ElegantOTA.loop();
}
```

---

## 四、上传固件 / Upload Methods

### Method 1: Web Upload (Recommended ✅) / Web 上传（推荐 ✅）

1. Open browser → `http://<device-IP>/update`
2. Select `.pio/build/esp32-solo1/firmware.bin`
3. Click Upload

### Method 2: PlatformIO espota (Requires ArduinoOTA) / PlatformIO espota（需添加 ArduinoOTA 服务）

**中文**：ElegantOTA 只提供 HTTP Web 上传，不兼容 `espota` 协议。如需在 PlatformIO 中直接上传，需在代码中同时添加 `ArduinoOTA`：

**English**: ElegantOTA only provides HTTP web upload and is not compatible with the `espota` protocol. To upload directly from PlatformIO, add `ArduinoOTA` alongside ElegantOTA:

```cpp
#include <ArduinoOTA.h>
// ... in setup():
ArduinoOTA.setHostname("esp32-solo1");
ArduinoOTA.setPassword("admin");
ArduinoOTA.begin();
// ... in loop():
ArduinoOTA.handle();
```

Then in `platformio.ini`:
```ini
upload_protocol = espota
upload_port = 192.168.x.x
upload_flags = --auth=admin
```

### Method 3: USB Wired / USB 有线烧录

```ini
upload_protocol = esptool
upload_port = COM17  ; Windows COM port
```

---

## 五、踩坑记录 / Lessons Learned

| Pitfall / 坑 | Symptom / 现象 | Solution / 解法 |
|-------------|---------------|----------------|
| Single-core crash / 单核崩溃 | `Guru Meditation Core 0 panic` | `custom_sdkconfig: CONFIG_FREERTOS_UNICORE=y` |
| `-D` macro ineffective / `-D` 宏无效 | Still crashes after adding `-DCONFIG_FREERTOS_UNICORE` | Kconfig options must be written to sdkconfig at build time, not via `-D` macro |
| espota timeout / espota 超时 | `No response from the ESP` | ElegantOTA doesn't support espota; use web upload or add ArduinoOTA |
| Wrong AsyncTCP version / AsyncTCP 版本选错 | Compilation error | ESP32 uses AsyncTCP@^3.x, not ^2.x |
| Missing OTA partition / OTA 分区未选 | `Image length XXXX doesn't fit in partition length XXXX` | Select `Minimal SPIFFS (1.9MB APP with OTA)` partition scheme |

---

## 六、Arduino IDE 移植 / Arduino IDE Migration (Unverified / 未验证)

**中文**：以下方案来自社区，用 `platform.local.txt` + `boards.local.txt` 在 Arduino IDE 3.x 中实现锁核，**但未经实测验证**。

**English**: The following approach from the community uses `platform.local.txt` + `boards.local.txt` to implement core pinning in Arduino IDE 3.x, **but has not been tested**.

1. Uninstall old ESP32 packages → install official 3.x core
2. Create `platform.local.txt` in the 3.x core directory:
   ```
   build.extra_flags=-DARDUINO_RUNNING_CORE=1 -DCONFIG_ESP32_WIFI_TASK_PINNED_TO_CORE_1=1
   ```
3. Create `boards.local.txt` defining a custom `ESP32-SOLO Custom Board`

**⚠️ Warning / 注意**：`ARDUINO_RUNNING_CORE=1` only pins tasks to Core1 — it does NOT change FreeRTOS's scheduler awareness. If 3.x FreeRTOS still attempts to initialize Core0 at startup, this approach will fail.

---

## 七、致谢 / Acknowledgments

感谢 [ayushsharma82/ElegantOTA](https://github.com/ayushsharma82/ElegantOTA) 提供优秀的 OTA 解决方案，让单核 ESP32 也能享受便捷的无线固件更新。

Thanks to [ayushsharma82/ElegantOTA](https://github.com/ayushsharma82/ElegantOTA) for providing an excellent OTA solution that enables single-core ESP32 devices to enjoy convenient wireless firmware updates.

---

## 许可 / License

This document follows the same MIT license as the original project.
本文档遵循与原项目相同的 MIT 许可。

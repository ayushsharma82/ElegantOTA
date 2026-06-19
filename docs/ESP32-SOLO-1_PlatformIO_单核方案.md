# ESP32-SOLO-1 单核芯片 + ElegantOTA 完整方案

> 作者：董大爷 & 巴迪 | 日期：2026-06-19 | 芯片：ESP32-SOLO-1（单核 Xtensa LX6）

## 摘要

ESP32-SOLO-1 是单核 ESP32 变体。默认的 arduino-esp32 SDK 以双核模式编译 FreeRTOS，会在启动时尝试初始化不存在的 Core0，导致 Guru Meditation 崩溃。

本文记录了使用 **PlatformIO + pioarduino** 平台，通过 `custom_sdkconfig` 注入 `CONFIG_FREERTOS_UNICORE=y` 从根本上解决单核问题的完整过程。方案已实测验证：编译、OTA 上传（v1→v2→v3）、Web 上传全部通过。

---

## 一、问题诊断

### 现象

- 使用 Arduino IDE 或 PlatformIO 默认设置编译 → 烧录后设备反复重启
- 串口输出 `Guru Meditation Error: Core 0 panic'ed`
- 即使最简单的 Blink 程序也会崩溃

### 根因

ESP32-SOLO-1 只有一个物理核心（Core1 / PRO_CPU），不存在 Core0（APP_CPU）。但 ESP-IDF FreeRTOS 默认以双核模式编译，启动时会调用 `vPortCPUInitializeMutex()` 等函数尝试初始化 Core0，导致访问不存在的硬件寄存器而崩溃。

```
FreeRTOS 双核初始化:
  xPortStartScheduler()
    → prvStartFirstTask()
      → 尝试启动 Core0 的 idle task
        → 访问 Core0 寄存器（不存在）
          → Guru Meditation ❌
```

### 为什么 `-DCONFIG_FREERTOS_UNICORE=1` 无效

`CONFIG_FREERTOS_UNICORE` 是 ESP-IDF 的 Kconfig 选项，必须在**编译 SDK 库时**生效，而不是在编译用户代码时。`build_flags = -DCONFIG_FREERTOS_UNICORE=1` 只影响用户代码的宏定义，不会改变已编译的 FreeRTOS 库行为。

---

## 二、解决方案：pioarduino + custom_sdkconfig

### 核心机制

pioarduino（`pioarduino/platform-espressif32`）是 arduino-esp32 的 PlatformIO 适配分支，支持 `custom_sdkconfig` 指令，可以在编译前将配置写入 `sdkconfig`，从而让 FreeRTOS 以单核模式编译。

### platformio.ini

```ini
[env:esp32-solo1]
; === 平台：使用 pioarduino fork（支持 custom_sdkconfig）===
platform = https://github.com/pioarduino/platform-espressif32.git
framework = arduino
board = esp32-solo1

; === 核心：强制单核模式 ===
; 这行是关键——让 FreeRTOS 编译时就知道只有一个核
custom_sdkconfig =
    CONFIG_FREERTOS_UNICORE=y

; === ElegantOTA 异步模式 ===
; 单核必须用异步 WebServer，否则 OTA 上传时设备无响应
build_flags =
    -DELEGANTOTA_USE_ASYNC_WEBSERVER=1

; === ElegantOTA 依赖 ===
lib_deps =
    ayushsharma82/ElegantOTA@^3.1.7
    ESP32Async/ESPAsyncWebServer@^3.7.3
    ESP32Async/AsyncTCP@^3.4.10

; === 上传参数 ===
upload_speed = 921600
monitor_speed = 115200

; OTA 上传（适用于有 ArduinoOTA 服务的固件）
; upload_protocol = espota
; upload_port = 192.168.x.x
; upload_flags = --auth=admin
```

### 关键依赖版本说明

| 库 | 版本 | 说明 |
|----|------|------|
| ElegantOTA | ^3.1.7 | 异步模式需要 `ELEGANTOTA_USE_ASYNC_WEBSERVER=1` |
| ESPAsyncWebServer | ^3.7.3 | ESP32Async 维护版，兼容 ESP32 arduino 3.x |
| AsyncTCP | ^3.4.10 | ESP32 用 3.x（ESP8266 用 2.x） |

---

## 三、代码（main.cpp）

```cpp
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

const char* ssid = "你的WiFi名";
const char* password = "你的WiFi密码";

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

  // 连接 WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // 首页
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain",
      "ESP32-SOLO-1 ElegantOTA Async Mode\n"
      "Upload firmware at /update");
  });

  // 启动 ElegantOTA（异步模式）
  ElegantOTA.begin(&server);
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  server.begin();
  Serial.print("OTA 页面: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/update");
}

void loop() {
  ElegantOTA.loop();
}
```

---

## 四、上传固件

### 方法 1：Web 上传（推荐，已验证 ✅）

1. 打开浏览器访问 `http://<设备IP>/update`
2. 选择 `.pio/build/esp32-solo1/firmware.bin`
3. 点 Upload

### 方法 2：PlatformIO espota（需添加 ArduinoOTA 服务）

ElegantOTA 只提供 HTTP Web 上传，不兼容 `espota` 协议。如需在 PlatformIO 中直接上传，需在代码中同时添加 `ArduinoOTA`：

```cpp
#include <ArduinoOTA.h>
// ... 在 setup() 中添加:
ArduinoOTA.setHostname("esp32-solo1");
ArduinoOTA.setPassword("admin");
ArduinoOTA.begin();
// ... 在 loop() 中添加:
ArduinoOTA.handle();
```

然后在 `platformio.ini` 中设置：
```ini
upload_protocol = espota
upload_port = 192.168.x.x
upload_flags = --auth=admin
```

### 方法 3：USB 有线烧录

```ini
upload_protocol = esptool
upload_port = COM17  ; Windows 串口号
```

---

## 五、踩坑记录

| 坑 | 现象 | 解法 |
|----|------|------|
| 单核崩溃 | Guru Meditation Core 0 panic | `custom_sdkconfig: CONFIG_FREERTOS_UNICORE=y` |
| `-D` 宏无效 | 加了 `-DCONFIG_FREERTOS_UNICORE` 仍然崩溃 | Kconfig 选项必须编译时写入 sdkconfig，不能用 -D 宏 |
| espota 超时 | `No response from the ESP` | ElegantOTA 不支持 espota 协议，用 Web 上传或加 ArduinoOTA |
| AsyncTCP 版本选错 | 编译失败 | ESP32 用 AsyncTCP@^3.x，不是 ^2.x |
| OTA 分区未选 | `E (656) esp_image: Image length XXXX doesn't fit in partition length XXXX` | 分区表选 `Minimal SPIFFS (1.9MB APP with OTA)` |

---

## 六、Arduino IDE 移植（未验证，存档）

以下方案来自社区，用 `platform.local.txt` + `boards.local.txt` 在 Arduino IDE 3.x 中实现锁核，**但未经实测验证**：

1. 卸载旧 ESP32 包 → 装官方 3.x 核心
2. 在 3.x 核心目录创建 `platform.local.txt`：
   ```
   build.extra_flags=-DARDUINO_RUNNING_CORE=1 -DCONFIG_ESP32_WIFI_TASK_PINNED_TO_CORE_1=1
   ```
3. 创建 `boards.local.txt` 自定义 `ESP32-SOLO Custom Board`

**⚠️ 注意**：`ARDUINO_RUNNING_CORE=1` 只是把任务绑到 Core1，不改变 FreeRTOS 的调度器认知。如果 3.x 的 FreeRTOS 启动时仍然尝试初始化 Core0，此方案会失败。

---

## 七、致谢

感谢 [ayushsharma82/ElegantOTA](https://github.com/ayushsharma82/ElegantOTA) 提供优秀的 OTA 解决方案，让单核 ESP32 也能享受便捷的无线固件更新。

---

## 许可

本文档遵循与原项目相同的 MIT 许可。

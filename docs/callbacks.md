---
title: Callbacks
sidebar_label: Callbacks
sidebar_position: 6
---

## Overview

The ElegantOTA library offers three callbacks that allow you to customize the behavior of your OTA update process. These callbacks enable you to execute specific functions at different stages of the update process, giving you control over the update flow. Here are the available callbacks:

1. `void onStart(void callable(void));`
2. `void onProgress(void callable(size_t current, size_t final));`
3. `void onEnd(void callable(bool success));`

Let's delve into the details of each callback and how to use them effectively.

## 1. `onStart` Callback

The `onStart` callback is triggered when the OTA update process begins. It's a convenient way to perform any setup or initialization tasks before the update process starts. You can use this callback to prepare your device for the update, such as saving important data, configuring pins, or setting up any required resources.

**Example:**

```cpp
ElegantOTA.onStart([]() {
  Serial.println("OTA update process started.");
  // Add your initialization tasks here.
});
```

## 2. `onProgress` Callback

The `onProgress` callback is called periodically during the OTA update to provide information about the progress of the update. It's useful for tracking the percentage of completion or displaying progress information to the user. This callback passes two parameters: `current` (the number of bytes transferred so far) and `final` (the total number of bytes to be transferred).

**Note:** onProgress callback can be called very frequently while the update is getting downloaded. It's neccessary to defer any tasks or logging so that core is not overloaded. Please refer to 'demo' example where progress is logged after every second.

**Example:**

```cpp
ElegantOTA.onProgress([](size_t current, size_t final) {
  Serial.printf("Progress: %u%%\n", (current * 100) / final);
});
```

## 3. `onEnd` Callback

The `onEnd` callback is invoked when the OTA update process completes, whether it succeeds or fails. It passes a boolean parameter `success` indicating the outcome of the update. You can use this callback to perform cleanup tasks or take action based on whether the update was successful or not.

**Example:**

```cpp
ElegantOTA.onEnd([](bool success) {
  if (success) {
    Serial.println("OTA update completed successfully.");
    // Add success handling here.
  } else {
    Serial.println("OTA update failed.");
    // Add failure handling here.
  }
});
```

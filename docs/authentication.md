---
title: Authentication
sidebar_label: Authentication
sidebar_position: 5
---

## Introduction

The Authentication feature in ElegantOTA enhances the security of your Internet of Things (IoT) devices by requiring authentication before allowing firmware updates or configuration changes. This feature ensures that only authorized individuals or systems can access and modify your devices, adding an extra layer of protection to your IoT ecosystem.

## Setting Authentication

You can set up authentication for your device using the `ElegantOTA.setAuth("username", "password");` function. This function requires two parameters: a username and a password. These credentials act as a gatekeeper, preventing unauthorized access to the device's OTA (Over-The-Air) update and configuration interfaces.

### Example Usage

```cpp
#include <ElegantOTA.h>

void setup() {
  // Initialize your hardware and other configurations here

  // Set Authentication Credentials
  ElegantOTA.setAuth("myUsername", "myPassword");

  // Additional setup code
}

void loop() {
  // Your main loop code here
}
```

In the above example, the `ElegantOTA.setAuth("myUsername", "myPassword");` function call sets the username to "myUsername" and the password to "myPassword" for device authentication.

## Clearing Authentication

Authentication once set can also be cleared by calling:
```cpp
ElegantOTA.clearAuth();
```

## Use Cases

The Authentication feature is crucial in various scenarios:

1. **Security**: It safeguards your IoT devices against unauthorized access, reducing the risk of malicious updates or configuration changes.

2. **Access Control**: By setting unique credentials for each device, you can control access to individual devices, ensuring that only authorized personnel or systems can modify them.

3. **Compliance**: Some security and compliance standards require authentication mechanisms for IoT devices. ElegantOTA's Authentication feature helps you meet these requirements.

## Best Practices

To ensure the effectiveness of the Authentication feature, consider these best practices:

- Choose strong and unique usernames and passwords for each device.

- Avoid using default or easily guessable credentials to enhance security.

- Keep the credentials in a secure location and avoid hardcoding them directly into your code to prevent accidental exposure.

- Regularly update and rotate the authentication credentials to maintain security.

- Test the authentication setup thoroughly to ensure that only authorized users can access the device.

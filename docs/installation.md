---
title: Installation
sidebar_label: Installation
sidebar_position: 2
---

ElegantOTA requires no dependencies and runs out of the box with existing libraries provided in Arduino core. You can install ElegantOTA through one of the following methods:

---

## For Arduino IDE

### 1. Library Manager

Go to Sketch > Include Library > Library Manager > Search for "ElegantOTA" > Install

### 2. Manual Installation

#### For Windows

- Download the [Repository](https://github.com/ayushsharma82/ElegantOTA/archive/master.zip)
- Extract the .zip in `Documents > Arduino > Libraries > {Place "ElegantOTA" folder Here}`

#### For Linux

- Download the [Repository](https://github.com/ayushsharma82/ElegantOTA/archive/master.zip)
- Extract the .zip in `Sketchbook > Libraries > {Place "ElegantOTA" folder Here}`

#### 3. Import through Arduino IDE

- Download the [Repository](https://github.com/ayushsharma82/ElegantOTA/archive/master.zip)
- Go to `Sketch > Include Library > Add .zip Library > Select the Downloaded .zip File.`

## For PlatformIO

### Required changes for PlatformIO

As ElegantOTA supports multiple architectures, PlatformIO will try to include all the dependencies automatically which will often result in compilation errors. To mitigate this issue, please follow these steps:

1. Delete `.pio/libdeps` folder (if it exists) in your project before proceeding.
2. Open `platformio.ini` file of your project.
3. Add the following line inside your `platformio.ini` file:

    ```ini
    lib_compat_mode = strict
    ```

4. Save the changes to the `platformio.ini` file.

### 1. Library Manager

Go to PlatformIO Menu > Libraries > Search for "ElegantOTA" > Install in your project.

### 2. Manual Installation

- Download the [Repository](https://github.com/ayushsharma82/ElegantOTA/archive/master.zip)
- Extract the .zip in `lib` folder of your project

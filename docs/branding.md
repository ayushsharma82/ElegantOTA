---
title: Branding
sidebar_label: Branding (Pro)
sidebar_position: 11
---

<div className="pro-label">
    <i>
        <h4 style={{ fontWeight: '500', marginBottom: 5 }}>
             This feature is only available in <a target="_blank" style={{ color: "red" }} href="https://elegantota.pro">ElegantOTA Pro</a>.
        </h4>
         
    </i>
</div>

<br/>
<br/>

<!-- <img src="/img/v4/tabs.png" alt="Concept Diagram" width="300px" /> -->

<!-- <br/> -->
<!-- <br/> -->

# Overview

Branding in this context refers to the custom logo that is displayed on the ElegantOTA portal during the OTA update process. You can customize the logo by defining the logo image as a byte array in the `logo.h` and `logo.cpp` files of the library's source code.

To add your custom logo on the ElegantOTA portal, follow these steps:

### Step 1: Prepare Your Logo

First, you need to create or obtain the logo image you want to display on the ElegantOTA portal during OTA updates. Ensure that the logo image is in a suitable format, such as a SVG (recommended) / PNG or JPG file and make sure your image is optimized & small in file size.

### Step 2: Convert Logo Image to a Byte Array

To include the logo in your library, you'll need to convert the image into a byte array.

1. Go to [File2Raw utility](https://file2raw.labrat.one/) ( I created this utility a few years back for the purpose of converting files into byte array for C++ applications ).
2. Select your logo.
3. Select "Gzip Compress" & "Use PROGMEM (Arduino)".
4. Click "Convert".

### Step 3: Modify `logo.h`

1. Open the `logo.h` file in your ElegantOTA library source code.

2. Locate the `ELEGANTOTA_LOGO` byte array declaration, which should look like this:

   ```cpp
   extern const uint8_t ELEGANTOTA_LOGO[];
   ```

3. Replace the length of the `ELEGANTOTA_LOGO` array with your custom logo's byte array length.

4. Locate the `ELEGANTOTA_LOGO_MIME` variable, which defines the MIME type of your logo image. By default, it is set to `image/png`. If your logo is in a different format (e.g., JPEG), update the `ELEGANTOTA_LOGO_MIME` variable to the appropriate MIME type.

5. Set `ELEGANTOTA_LOGO_WIDTH` & `ELEGANTOTA_LOGO_HEIGHT` according to your desired size which will be displayed on the webpage.

### Step 4: Modify `logo.cpp`

1. Open the `logo.cpp` file in your ElegantOTA library source code.

2. Replace the contents of the `ELEGANTOTA_LOGO` array with your custom logo's byte array generated in File2Raw utility.


### Step 5: Upload the Modified Library

After making these changes, compile and upload the modified ElegantOTA library to your device.

## Using the Custom Logo

Once you have uploaded the modified ElegantOTA library to your device, the custom logo will be displayed on the ElegantOTA Portal webpage during OTA updates.

That's it! You have successfully added custom branding to the ElegantOTA portal by defining the logo as a byte array in the `logo.h` and `logo.cpp` files. Your logo will now be displayed on the ElegantOTA portal.

Please note that branding, including logos and images, may be subject to copyright and trademark laws. Ensure you have the necessary rights or permissions to use any branding elements in your project.
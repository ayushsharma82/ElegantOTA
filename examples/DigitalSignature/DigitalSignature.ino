/*
  ElegantOTA Digital Signature Example - This example will work for both ESP8266 & ESP32 microcontrollers.
  Enables OTA updates with digital signature verification by verifying the digital signature of the firmware file using a public key.
  -----
  Author: gb88 (https://github.com/gb88)
  Perform the Update with a signed file, include in the code the public key for the signing process follow the instruction:

  generate the private key (keep this secret):
    - openssl genrsa -out priv_key.pem 2048

  and the corresponding public key:
    - openssl rsa -in priv_key_2048.pem -pubout > rsa_key_2048.pub

  export the compiled sketch to get the bin file
    
  sign the file with SHA256 hash with the private key:
    - openssl dgst -sign priv_key_2048.pem -keyform PEM -sha256 -out firmware.sign -binary DigitalSignature.ino.bin

  throw it all in one file
    - cat firmware.sign DigitalSignature.ino.bin > ota.bin

  After the update you will see in the serial log the version update from 1.00 to 1.01

*/
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#endif

#include <ElegantOTA.h>


#define FW_VERSION 100

HashSHA256 Hash256;
RSADigitalSignatureVerifier RSAVerifier;

const char* ssid = "-----";
const char* password = "-----";

#if defined(ESP32)
const char pub_key[] = "-----BEGIN PUBLIC KEY-----\nMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAso/F7lALGgdK8FhvLzM+\n3+L+o7zvpMCjJubWtBO44106fISLa8FE9kRsgkFxD2Av0oFqJC+Ts8ryXF+z9SKY\nj+3+HUv1dmMtvkI7aVeH6ahytXOazhs2DXaYDSXBreaud0/q+r+NBQAzen0IGxDY\n6+Z5XiGDiIUgPTj4Bnrlush+2XcK9kt+LPOeUbxmETj3KsR4FTW6eWWEyeouLoWt\nBt5jh6VcD5VqFsNOpN4DPN7ocjnPAgvX3a9quEekx2Ex4/E7ITz/N7xntU3fKhcm\noNbGvgaNZZCDDZieaQJLZ+kviGZ2IhMDAqEm8tMUPbTiCDSC31awMXBDB/cEebt8\nxQIDAQAB\n-----END PUBLIC KEY-----";
#else
const char pub_key[] PROGMEM = R"EOF(
-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAso/F7lALGgdK8FhvLzM+
3+L+o7zvpMCjJubWtBO44106fISLa8FE9kRsgkFxD2Av0oFqJC+Ts8ryXF+z9SKY
j+3+HUv1dmMtvkI7aVeH6ahytXOazhs2DXaYDSXBreaud0/q+r+NBQAzen0IGxDY
6+Z5XiGDiIUgPTj4Bnrlush+2XcK9kt+LPOeUbxmETj3KsR4FTW6eWWEyeouLoWt
Bt5jh6VcD5VqFsNOpN4DPN7ocjnPAgvX3a9quEekx2Ex4/E7ITz/N7xntU3fKhcm
oNbGvgaNZZCDDZieaQJLZ+kviGZ2IhMDAqEm8tMUPbTiCDSC31awMXBDB/cEebt8
xQIDAQAB
-----END PUBLIC KEY-----
)EOF";
#endif

#if defined(ESP8266)
ESP8266WebServer server(80);
#elif defined(ESP32)
WebServer server(80);
#endif



void setup(void) {
  Serial.begin(115200); // Initialize the serial communication

  // Set the RSAVerifier key based on the microcontroller type
  #if defined(ESP32)
  RSAVerifier.setKey(pub_key, strlen(pub_key));
  #elif defined(ESP8266)
  RSAVerifier.setKey(pub_key, strlen_P(pub_key));
  #endif

  // Print the firmware version
  Serial.printf("Firmware Version %d.%.2d\n", FW_VERSION / 100, FW_VERSION - 100 * (FW_VERSION / 100));

  // Configure WiFi in station mode and connect to the network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up a handler for the root URL ("/") that sends a response
  server.on("/", []() {
    server.send(200, "text/plain", "Hi! I am ESP8266.");
  });

  // Start ElegantOTA for OTA updates
  ElegantOTA.begin(&server);

  // Set the digital signature for ElegantOTA
  ElegantOTA.setDigitalSignature(&Hash256, &RSAVerifier);

  // Start the HTTP server
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  // Handle incoming client requests
  server.handleClient();
}

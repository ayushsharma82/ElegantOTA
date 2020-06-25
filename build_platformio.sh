#!/bin/bash

set -euo pipefail

pio ci --lib=. --board esp12e "examples/ESP8266_Demo"
pio ci --lib=. --board esp32dev "examples/ESP32_Demo"

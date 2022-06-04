
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <ArduinoJson.h>

// TODO: create a webserver to handle API REST HTTP 
//       requests

/*
    REFS:
    https://randomnerdtutorials.com/esp32-flash-memory/
    https://wirandle.com/how-to-implement-an-esp32-api-server-using-platformio/
    https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
    https://randomnerdtutorials.com/esp32-access-point-ap-web-server/
    https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/README.rst
    https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/src/ESP8266WebServer.h
*/

// ESP32 and the EEPROM library you can use up to 512 bytes in the flash memory
#ifndef EEPROM_SIZE
#define EEPROM_SIZE 512
#endif

#ifndef EEPROM_DEFAULT_VALUE
#define EEPROM_DEFAULT_VALUE 255
#endif

#ifndef DEFAULT_AP_SSID
#define DEFAULT_AP_SSID "esp32_plc_ap"
#endif

#ifndef DEFAULT_AP_PASS
#define DEFAULT_AP_PASS NULL
#endif

#ifndef DEFAULT_AP_STATUS
#define DEFAULT_AP_STATUS false
#endif

#ifndef JSON_BUFFER
#define JSON_BUFFER 250
#endif

#ifndef _APIFLASH_H
#define _APIFLASH_H

// api
void setup_apiflash();
void handle_api();
void get_api_eeprom_byte();
void put_api_eeprom_byte();
void api_not_found();

// wifi
bool enable_wifi(bool en);

// eeprom
void erase_flash(); // Set every byte to default values (zero)
void update_flash_byte(uint16_t address, uint8_t value);

#endif

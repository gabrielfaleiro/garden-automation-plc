# garden-automation-plc

## References
- Datasheet: https://www.industrialshields.com/es_ES/shop/product/013002000100-modulo-digital-de-10-e-s-cpu-esp32-2196
- Programming: https://www.industrialshields.com/es_ES/technical-features-industrial-plc-arduino-10-ios-digital-module-cpu-esp32

## Arduino IDE Libraries
- ArduinoJson 6.19.4
- WiFi 1.2.7

## HW PLC Configuration

- Inputs 5V
  - I0.0
  - I0.1
  - I0.2
  - I0.3
  - I0.4
- Outputs 24V
  - Q0.5
  - Q0.6
  - Q0.7
  - Q0.8
  - Q0.9


## TODO
- Implement API: https://www.industrialshields.com/es_ES/blog/blog-industrial-open-source-1/post/servidor-http-en-un-m-duino-154
  - Tutorial: https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
- RS232 (GPS): https://www.industrialshields.com/es_ES/blog/blog-industrial-open-source-1/post/aprender-los-conceptos-basicos-sobre-rs232-de-un-plc-industrial-183
- Use EEPROM: https://www.industrialshields.com/es_ES/blog/blog-industrial-open-source-1/post/como-almacenar-el-mac-de-tu-plc-arduino-en-el-eeprom-memoria-no-volatil-174
  - Tutorial: https://pijaeducation.com/eeprom-in-arduino-and-esp/#:~:text=The%20maximum%20EEPROM%20size%20on,only%20use%20512%20Bytes%20here.
- OTA through webserver: https://lastminuteengineers.com/esp32-ota-web-updater-arduino-ide/
- Sleep modes: https://lastminuteengineers.com/esp32-sleep-modes-power-consumption/
  - Deep sleep: https://lastminuteengineers.com/esp32-deep-sleep-wakeup-sources/
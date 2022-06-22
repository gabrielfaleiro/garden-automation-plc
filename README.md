# garden-automation-plc

## References
- Datasheet: https://www.industrialshields.com/es_ES/shop/product/013002000100-modulo-digital-de-10-e-s-cpu-esp32-2196
- Programming: https://www.industrialshields.com/es_ES/technical-features-industrial-plc-arduino-10-ios-digital-module-cpu-esp32
- Logging: https://github.com/thijse/Arduino-Log/blob/master/README.md

## Arduino IDE Libraries
- ArduinoJson 6.19.4
- WiFi 1.2.7
- ArduinoLog 1.1.1

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

```
Q0_9: 13
Q0_8: 12
Q0_7: 14
Q0_6: 27
Q0_5: 26
Q0_4: 25
Q0_3: 32
Q0_2: 15
Q0_1: 2
Q0_0: 4

I0_9: 13
I0_8: 12
I0_7: 14
I0_6: 27
I0_5: 26
I0_4: 25
I0_3: 32
I0_2: 15
I0_1: 2
I0_0: 4
```


## TODO
- Implement API: https://www.industrialshields.com/es_ES/blog/blog-industrial-open-source-1/post/servidor-http-en-un-m-duino-154
  - Tutorial: https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
- RS232 (GPS): https://www.industrialshields.com/es_ES/blog/blog-industrial-open-source-1/post/aprender-los-conceptos-basicos-sobre-rs232-de-un-plc-industrial-183
- Use EEPROM: https://www.industrialshields.com/es_ES/blog/blog-industrial-open-source-1/post/como-almacenar-el-mac-de-tu-plc-arduino-en-el-eeprom-memoria-no-volatil-174
  - Tutorial: https://pijaeducation.com/eeprom-in-arduino-and-esp/#:~:text=The%20maximum%20EEPROM%20size%20on,only%20use%20512%20Bytes%20here.
- OTA through webserver: https://lastminuteengineers.com/esp32-ota-web-updater-arduino-ide/
- Sleep modes: https://lastminuteengineers.com/esp32-sleep-modes-power-consumption/
  - Deep sleep: https://lastminuteengineers.com/esp32-deep-sleep-wakeup-sources/
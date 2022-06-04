
#include "ApiFlash.h"

// TODO: secure with certifications
WiFiServer server(80);

StaticJsonDocument<JSON_BUFFER> jsonDocument;
char buffer[JSON_BUFFER];

void setup_apiflash(){

    // TODO: add station mode compatibility
    WiFi.mode(WIFI_AP);
    enable_wifi(DEFAULT_AP_STATUS);

    EEPROM.begin(EEPROM_SIZE);

    // TODO: add server authentication

    server.on("/eeprom/byte", HTTP_GET, get_api_eeprom_byte);
    server.on("/eeprom/byte", HTTP_PUT, put_api_eeprom_byte);
    server.onNotFound(api_not_found);

}

void handle_api(){
    server.handleClient();
}

void get_api_eeprom_byte(){
    uint16_t address = 0;
    uint8_t value = 0;
    if (hasArg("address")){
        address = arg("address");
        if (address >= EEPROM_SIZE){
            // invalid data
            jsonDocument.clear();
            jsonDocument["message"] = "Parameter address has invalid data";
            serializeJson(jsonDocument, buffer);
            server.send(400, "application/json", buffer);
        }
    }
    else{
        // no parameter
        jsonDocument.clear();
        jsonDocument["message"] = "Parameter address not found";
        serializeJson(jsonDocument, buffer);
        server.send(400, "application/json", buffer);
    }

    jsonDocument.clear();
    value = EEPROM.read(address);
    jsonDocument["address"] = address;
    jsonDocument["value"] = value;
    serializeJson(jsonDocument, buffer);
    server.send(200, "application/json", buffer);
}

void put_api_eeprom_byte(){
    jsonDocument.clear();
    // TODO
    jsonDocument["message"] = "Under construction";
    serializeJson(jsonDocument, buffer);
    server.send(200, "application/json", buffer);
}

void api_not_found(){
    jsonDocument.clear();
    jsonDocument["message"] = "Not found";
    serializeJson(jsonDocument, buffer);
    server.send(404, "application/json", buffer);
}

bool enable_wifi(bool en){
    static bool internal_en = !DEFAULT_AP_STATUS;
    bool ret_val = false;

    // Avoid running this function repeatedly
    if (en != internal_en){
        Serial.print("setting up wifi: ");
        Serial.println(en);
        internal_en = en;
        if (en){
            ret_val = WiFi.softAP(DEFAULT_AP_SSID, DEFAULT_AP_PASS);
            server.begin();
        }
        else {
            ret_val = WiFi.softAPdisconnect(true); // true for switching off
            server.stop();
        }
    }
    else{
        ret_val = true;
    }

    return ret_val;
}

void erase_flash(){
    int i = 0;
    for(i=0; i < EEPROM_SIZE ; i++){
        update_flash_byte(i, EEPROM_DEFAULT_VALUE);
    }
}

void update_flash_byte(uint16_t address, uint8_t value){
    uint8_t int_value = 0;
    int_value = EEPROM.read(address);
    if (value != int_value){
        EEPROM.write(address, value);  
    }
}


#include "ApiFlash.h"

#define DEBUG

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  // Initialize with log level and log output. 
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);

  setup_apiflash();

  enable_wifi(true);
  
}

void loop() {

  handle_apiflash();

  
}

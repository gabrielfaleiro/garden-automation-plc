
#include <ArduinoLog.h>
#include "Time.h"
#include "DigitalSignalFilters.h"
#include "Process.h"
#include "Step.h"
#include "ApiFlash.h"
#include "proj_home_lab.h"


void setup() {
  Serial.begin(9600);
  while(!Serial);

  // Initialize with log level and log output. 
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);

  setup_apiflash();
  
  proj_setup();

}

void loop() {
  handle_apiflash();

  proj_loop();

}

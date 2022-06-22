
#include <ArduinoLog.h>
#include "Time.h"
#include "DigitalSignalFilters.h"
#include "Process.h"
#include "Step.h"
#include "ApiFlash.h"
#include "proj_pezuela.h"


void setup() {
  Serial.begin(9600);
  while(!Serial);

  // Initialize with log level and log output. 
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);

  setup_apiflash();
  
  proj_setup();

  pinMode(I0_0, INPUT);

}

void loop() {
  handle_apiflash();

  //proj_loop();

  Log.verboseln("value: %d", analogRead(I0_0));

}

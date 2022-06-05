
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
  Log.verboseln("Q0_9: %d", Q0_9);
  Log.verboseln("Q0_8: %d", Q0_8);
  Log.verboseln("Q0_7: %d", Q0_7);
  Log.verboseln("Q0_6: %d", Q0_6);
  Log.verboseln("Q0_5: %d", Q0_5);
  Log.verboseln("Q0_4: %d", Q0_4);
  Log.verboseln("Q0_3: %d", Q0_3);
  Log.verboseln("Q0_2: %d", Q0_2);
  Log.verboseln("Q0_1: %d", Q0_1);
  Log.verboseln("Q0_0: %d", Q0_0);

  Log.verboseln("I0_9: %d", I0_9);
  Log.verboseln("I0_8: %d", I0_8);
  Log.verboseln("I0_7: %d", I0_7);
  Log.verboseln("I0_6: %d", I0_6);
  Log.verboseln("I0_5: %d", I0_5);
  Log.verboseln("I0_4: %d", I0_4);
  Log.verboseln("I0_3: %d", I0_3);
  Log.verboseln("I0_2: %d", I0_2);
  Log.verboseln("I0_1: %d", I0_1);
  Log.verboseln("I0_0: %d", I0_0);
}

void loop() {
  handle_apiflash();

  proj_loop();
  
}

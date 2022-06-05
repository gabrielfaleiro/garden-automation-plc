
#include "ApiFlash.h"
#include "Time.h"

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  setup_apiflash();
  pinMode(Q0_5, OUTPUT);
  
}

void loop() {
  static bool en = true;
  static unsigned long timer = now();

  if (lapse(timer) > 20000){
    timer = now();
    digitalWrite(Q0_5, en);
    enable_wifi(en);
    en = ! en;
  }
}

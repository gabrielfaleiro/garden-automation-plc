
#include "ApiFlash.h"

void setup() {
  Serial.begin(9600);
  while(!Serial);
  
  setup_apiflash();
  pinMode(Q0_5, OUTPUT);
  
}

void loop() {
  static bool en = true;
  digitalWrite(Q0_5, en);
  enable_wifi(en);

}

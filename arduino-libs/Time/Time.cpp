
#include "Time.h"

unsigned long now(bool micros_value){
  unsigned long now = 0;
  if(micros_value) now = micros();
  else             now = millis();
  return now;
}

unsigned long lapse(unsigned long old_now, bool micros_value){
  unsigned long _max_unsigned_long = 0xffffffff;
  unsigned long lapse = 0;
  unsigned long now = 0;
  if(micros_value) now = micros();
  else             now = millis();

  if (now >= old_now){
    lapse = now - old_now;
  }
  else{
    lapse = now + (_max_unsigned_long - old_now);
  }
  
  return lapse;
}

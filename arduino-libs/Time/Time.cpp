
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

Timer::Timer(){
    this->_timer = 0;
    this->_timeout = 0;
}

void Timer::update_timer_ref(){
    this->_timer = now();
}

void Timer::config(unsigned long timeout){
    this->_timeout = timeout;
}

bool Timer::timeout(){
    bool ret_val = false;
    if (lapse(this->_timer) > this->_timeout) ret_val = true;
    return ret_val;
}

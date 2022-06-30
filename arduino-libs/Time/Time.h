
#include <Arduino.h>

#ifndef _TIME_H
#define _TIME_H

unsigned long now(bool micros_value = false);

unsigned long lapse(unsigned long old_now, bool micros_value = false);

#endif

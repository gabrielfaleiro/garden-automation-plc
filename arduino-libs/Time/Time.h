
#include <Arduino.h>

#ifndef _TIME_H
#define _TIME_H

unsigned long now(bool micros_value = false);

unsigned long lapse(unsigned long old_now, bool micros_value = false);

class Timer{
    public:
        Timer();

        void update_timer_ref(); // update timer time
        void config(unsigned long timeout); // config timeout
        bool timeout(); // transit function

    private:
        unsigned long _timer;   // reference
        unsigned long _timeout; // timeout to count
};

#endif

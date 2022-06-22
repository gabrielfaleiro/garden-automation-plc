
#include <Arduino.h>
#include <ArduinoLog.h>
#include "Step.h"

#ifndef PROCESS_MAX_STATES
#define PROCESS_MAX_STATES 50
#endif

#ifndef _PROCESS_H
#define _PROCESS_H

class Process{
    public:        
        Process();
        
        void reset();
        uint get_state();
        void process();

        void set_step(uint state, Step step);
        void enable_autoreset(bool en);

        bool process_finished();
        
    private:
        uint state;
        Step steps[PROCESS_MAX_STATES];
        bool autoreset;

        void _change_state(uint state);

};

#endif

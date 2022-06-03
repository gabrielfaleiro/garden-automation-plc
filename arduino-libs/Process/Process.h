
#include <Arduino.h>
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
        
    private:
        uint state;
        Step steps[PROCESS_MAX_STATES];

        void _change_state(uint state);

};

#endif

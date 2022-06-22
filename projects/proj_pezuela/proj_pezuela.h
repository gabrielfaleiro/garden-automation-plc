#include <Arduino.h>
#include <EEPROM.h>
#include "Process.h"
#include "Step.h"
#include "DigitalSignalFilters.h"
#include "ApiFlash.h"

#ifndef _PROJECT_H
#define _PROJECT_H

struct app_data_struct;

class EvHandler{
    public:        
        EvHandler();
        
        void config(int pin_open, int pin_close);

        void opening();
        void closing();
        void idle();

    private:
        int pin_open;
        int pin_close; 
};

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

void turn_on_pump();
void turn_off_pump();

void proj_setup();
void proj_loop();

void init_struct(app_data_struct* app_data);

#endif
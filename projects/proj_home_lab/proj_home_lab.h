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

// Pump
void turn_on_pump();
void turn_off_pump();

// Timers
void ev_update_timer_ref();
void pump_update_timer_ref();
void irrigation_area_update_timer_ref();
bool ev_timeout();
bool pump_timeout();
bool irrigation_area_timeout();

// ElectroValves
void ev1_opening();
void ev2_opening();
void ev3_opening();
void ev1_closing();
void ev2_closing();
void ev3_closing();
void ev1_idle();
void ev2_idle();
void ev3_idle();

void proj_setup();
void proj_loop();

void init_struct(app_data_struct* app_data);

#endif
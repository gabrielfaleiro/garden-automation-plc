#include <Arduino.h>
#include <EEPROM.h>
#include "Process.h"
#include "Step.h"
#include "DigitalSignalFilters.h"
#include "ApiFlash.h"
#include "Actions.h"
#include "SerialCommands.h"

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

// Timers
void ev_update_timer_ref();
void irrigation_area_update_timer_ref();
bool ev_timeout();
bool irrigation_area_timeout();

// ElectroValves
void ev1_opening();
void ev1_closing();
void ev1_idle();

void proj_setup();
void proj_loop();

void init_struct(app_data_struct* app_data);

#endif
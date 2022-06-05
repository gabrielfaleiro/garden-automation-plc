
/*
    This template shall be used to build new projects based on the same basic drivers.
    Application logic and finite state machines are coded in this template file.

    The following functions are necessary to assure integration.
    Their content can be modified and any other functions, class or variables can be added within this scope.

    Please, enjoy ;)

*/

#include <Arduino.h>
#include <EEPROM.h>
#include "Process.h"
#include "Step.h"
#include "proj_pezuela.h"


// Struct containing main application data
struct app_data_struct {
    // outputs
    int ev1_relay_pin_a = Q0_9;
    int ev1_relay_pin_b = Q0_8;
    int ev2_relay_pin_a = Q0_7;
    int ev2_relay_pin_b = Q0_6;
    int ev3_relay_pin_a = Q0_5;
    int ev3_relay_pin_b = Q0_4;
    int pump_relay_pin  = Q0_3;
    // inputs
    int tank_level_pin       = I0_2; // HIGH with water
    int emergency_stop_pin   = I0_1; // HIGH on not activated
    int pv_panel_voltage_pin = I0_0;
    
    // digital filter cooldowns
    unsigned long tank_level_cooldown       =   60000;
    unsigned long emergency_stop_cooldown   =    5000;
    unsigned long pv_panel_voltage_cooldown = 3600000;

    // operation times
    unsigned long relay_activation_ms = 5000;
    
} app_data;

EvHandler::EvHandler(){
    this->pin_open = 0;
    this->pin_close = 0;
}

void EvHandler::config(int pin_open, int pin_close){
    this->pin_open = pin_open;
    this->pin_close = pin_close;
}

void EvHandler::opening(){
    digitalWrite(this->pin_open, HIGH);
    digitalWrite(this->pin_close, LOW);
}

void EvHandler::closing(){
    digitalWrite(this->pin_open, LOW);
    digitalWrite(this->pin_close, HIGH);
}

void EvHandler::idle(){
    digitalWrite(this->pin_open, LOW);
    digitalWrite(this->pin_close, LOW);
}

Timer::Timer(){
    this->timer = 0;
    this->timeout = 0;
}

void Timer::update_timer_ref(){
    this->timer = now();
}

void Timer::config(unsigned long timeout){
    this->timeout = timeout;
}

bool Timer::timeout(){
    if (lapse(this->timer) > this->timeout) return true;
    else return false;
}

void init_struct(app_data_struct* app_data){
    // app_data
    ;
}

// application logic code

ev1_handler = EvHandler();
ev2_handler = EvHandler();
ev3_handler = EvHandler();

ev1_timer = Timer();
ev2_timer = Timer();
ev3_timer = Timer();
pump_timer = Timer();

irrigation = Process();

void turn_on_pump(){
    digitalWrite(app_data.pump_relay_pin, HIGH);
}

void turn_off_pump(){
    digitalWrite(app_data.pump_relay_pin, LOW);
}


// setup function
void proj_setup(){
    init_struct(&app_data);

    // irrigation

    return;
}

// loop function
void proj_loop(){
    // Get variables


    // High level state machine

        // Processes
    
    return;
}
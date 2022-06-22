
/*
    This template shall be used to build new projects based on the same basic drivers.
    Application logic and finite state machines are coded in this template file.

    The following functions are necessary to assure integration.
    Their content can be modified and any other functions, class or variables can be added within this scope.

    Please, enjoy ;)

*/


#include "proj_pezuela.h"


// Struct containing main application data
struct app_data_struct {
    // outputs
    int ev1_relay_pin_a      = Q0_9;
    int ev1_relay_pin_b      = Q0_8;
    int ev2_relay_pin_a      = Q0_7;
    int ev2_relay_pin_b      = Q0_6;
    int ev3_relay_pin_a      = Q0_5;
    int ev3_relay_pin_b      = Q0_4;
    int pump_relay_pin       = Q0_3;
    // inputs
    int tank_level_pin       = I0_2; // HIGH with water
    int emergency_stop_pin   = I0_1; // HIGH on not activated
    int pv_panel_voltage_pin = I0_0;
    
    // digital filter cooldowns
    unsigned long tank_level_cooldown       =   60000;
    unsigned long emergency_stop_cooldown   =    5000;
    unsigned long pv_panel_voltage_cooldown = 3600000;

    // operation times
    unsigned long relay_activation_ms       = 5000;
    
} app_data;

EvHandler::EvHandler(){
    this->pin_open  = 0;
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

void init_struct(app_data_struct* app_data){
    // TODO: retrieve data from flash
    // app_data
    ;
}

// application logic code

EvHandler ev1_handler = EvHandler();
EvHandler ev2_handler = EvHandler();
EvHandler ev3_handler = EvHandler();

Timer ev1_timer  = Timer();
Timer ev2_timer  = Timer();
Timer ev3_timer  = Timer();
Timer pump_timer = Timer();

Process irrigation = Process();
Process protection = Process();

void turn_on_pump(){
    digitalWrite(app_data.pump_relay_pin, HIGH);
}

void turn_off_pump(){
    digitalWrite(app_data.pump_relay_pin, LOW);
}


// setup function
void proj_setup(){
    init_struct(&app_data);

    //irrigation.set_step()

    // TODO: processes
    // irrigation
        /*
        0 - 
        */
    // protection
        /*
        0 - 
        */

    return;
}

// loop function
void proj_loop(){
    // Get variables
    static DigitalFilter emergency_stop = DigitalFilter(app_data.emergency_stop_cooldown,
                                                        LOW); // secure by default
        // LOW:  enabled - protection
        // HIGH: nominal
    static DigitalFilter tank_level = DigitalFilter(app_data.tank_level_cooldown,
                                                    LOW); // secure by default
        // LOW:  no water - protection
        // HIGH: water detected - safe operation    
    static DigitalFilter pv_panel_voltage = DigitalFilter(app_data.pv_panel_voltage_cooldown,
                                                          HIGH); // secure by default
        // LOW:  night - irrigation process
        // HIGH: day
    
    bool emergency_stop_value = emergency_stop.get_filtered_value(digitalRead(app_data.emergency_stop_pin));
    bool tank_level_value = tank_level.get_filtered_value(digitalRead(app_data.tank_level_pin));
    bool pv_panel_voltage_value = pv_panel_voltage.get_filtered_value(digitalRead(app_data.pv_panel_voltage_pin));

    bool en_wifi_value = false;

    // Process irrigation reset happens even though system is in protection mode
    if (pv_panel_voltage_value){ // day
        // Reset process: irrigation
        irrigation.reset();
    }

    if (emergency_stop_value || !tank_level_value){
        // Process: protection
        protection.process();
        if (emergency_stop_value){
            // Turn on wifi and handle configuration through API
            en_wifi_value = true;
        }
    }
    else{
        // Reset process: protection
        protection.reset();
        if (!pv_panel_voltage_value){ // night
            // Process: irrigation
            irrigation.process();
        }
    }

    enable_wifi(en_wifi_value);

    // TODO: FFR do state machine to support manual tests
    
    return;
}
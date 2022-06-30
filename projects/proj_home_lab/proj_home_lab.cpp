
/*
    This template shall be used to build new projects based on the same basic drivers.
    Application logic and finite state machines are coded in this template file.

    The following functions are necessary to assure integration.
    Their content can be modified and any other functions, class or variables can be added within this scope.

    Please, enjoy ;)

*/


#include "proj_home_lab.h"


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
    unsigned long tank_level_cooldown               =   60000;
    unsigned long emergency_stop_cooldown           =    5000;
    unsigned long pv_panel_voltage_cooldown         = 3600000;
        
    // operation times      
    unsigned long relay_activation_ms               = 10000;
    unsigned long irrigation_area_ms                = 30*1000;
    unsigned long pump_protection_ms                = 10000;
        
    unsigned long irrigation_period_ms              = 60*1000;
    unsigned long irrigation_period_init_sync_ms    = 30*1000; // init time for synchronisation of first iteration
    
} app_data;

EvHandler ev1_handler = EvHandler();

Timer ev_timer                  = Timer();
Timer irrigation_area_timer     = Timer();
Timer irrigation_period_timer   = Timer();

Process irrigation = Process();

Actions proj_actions = Actions();
SerialCommands serial_commands = SerialCommands(&proj_actions);

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

void init_struct(app_data_struct* app_data){
    // TODO: retrieve data from flash
    // app_data
    ;
}

// Pump
void turn_on_pump(){
    digitalWrite(app_data.pump_relay_pin, HIGH);
}

void turn_off_pump(){
    digitalWrite(app_data.pump_relay_pin, LOW);
}

// Timers
void ev_update_timer_ref(){
    ev_timer.update_timer_ref();
}
void irrigation_area_update_timer_ref(){
    irrigation_area_timer.update_timer_ref();
}
bool ev_timeout(){
    return ev_timer.timeout();
}
bool irrigation_area_timeout(){
    return irrigation_area_timer.timeout();
}


// ElectroValves
void ev1_opening(){
    Log.verboseln("ev1: opening");
    ev1_handler.opening();
}
void ev1_closing(){
    Log.verboseln("ev1: closing");
    ev1_handler.closing();
}
void ev1_idle(){
    Log.verboseln("ev1: idle");
    ev1_handler.idle();
}

// setup function
void proj_setup(){
    init_struct(&app_data);

    pinMode(app_data.ev1_relay_pin_a, OUTPUT);
    pinMode(app_data.ev1_relay_pin_b, OUTPUT);
    pinMode(app_data.ev2_relay_pin_a, OUTPUT);
    pinMode(app_data.ev2_relay_pin_b, OUTPUT);
    pinMode(app_data.ev3_relay_pin_a, OUTPUT);
    pinMode(app_data.ev3_relay_pin_b, OUTPUT);
    pinMode(app_data.pump_relay_pin, OUTPUT);

    digitalWrite(app_data.ev1_relay_pin_a, LOW);
    digitalWrite(app_data.ev1_relay_pin_b, LOW);
    digitalWrite(app_data.ev2_relay_pin_a, LOW);
    digitalWrite(app_data.ev2_relay_pin_b, LOW);
    digitalWrite(app_data.ev3_relay_pin_a, LOW);
    digitalWrite(app_data.ev3_relay_pin_b, LOW);
    digitalWrite(app_data.pump_relay_pin,  LOW);

    pinMode(app_data.tank_level_pin, INPUT);
    pinMode(app_data.emergency_stop_pin, INPUT);
    pinMode(app_data.pv_panel_voltage_pin, INPUT);

    // setup steps
    ev1_handler.config(app_data.ev1_relay_pin_a, app_data.ev1_relay_pin_b);

    ev_timer.config(app_data.relay_activation_ms);
    irrigation_area_timer.config(app_data.irrigation_area_ms);
    irrigation_period_timer.config(app_data.irrigation_period_init_sync_ms);

    irrigation_period_timer.update_timer_ref();

    Step* aux_step;

    proj_actions.add_action("ev1_opening", ev1_opening);
    proj_actions.add_action("ev1_closing", ev1_closing);
    proj_actions.add_action("ev1_idle", ev1_idle);

    //// process irrigation
    // 0  - open ev1 during relay_activation_ms end with idle
    aux_step = irrigation.get_step(0);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev1_opening);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev1_idle);
    // 1  - wait during irrigation_area_ms
    aux_step = irrigation.get_step(1);
    aux_step->set_pre_op(irrigation_area_update_timer_ref);
    aux_step->set_op();
    aux_step->set_transit(irrigation_area_timeout);
    aux_step->set_post_op();
    // 2  - close ev1 during relay_activation_ms end with idle
    aux_step = irrigation.get_step(2);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev1_closing);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev1_idle);
    ////////////////////

    return;
}

// loop function
void proj_loop(){

    static bool irrigation_completed = true;

    bool en_wifi_value = true;
    uint irrigation_state = 0;

    serial_commands.handle_serial();

    // // clock based control
    // if(irrigation_period_timer.timeout() && irrigation_completed){
    //     irrigation_period_timer.config(app_data.irrigation_period_ms);
    //     irrigation_period_timer.update_timer_ref();
    //     irrigation.reset();
    //     irrigation_completed = false;
    // }

    // if(irrigation_completed || irrigation.process_finished()){
    //     irrigation_completed = true;
    // }
    // else{
    //     irrigation.process();
    // }
    //
    // irrigation_state = irrigation.get_state();
    // Log.verboseln("irrigation state: %d", irrigation_state);

    enable_wifi(en_wifi_value);

    // TODO: FFR do state machine to support manual tests
    
    return;
}

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
    // outputs                       // relays
    int ev1_relay_pin_a      = Q0_9; // K1
    int ev1_relay_pin_b      = Q0_8; // K2
    int ev2_relay_pin_a      = Q0_7; // K3
    int ev2_relay_pin_b      = Q0_6; // K4
    int ev3_relay_pin_a      = Q0_5; // K5
    int ev3_relay_pin_b      = Q0_4; // K6
    int pump_relay_pin       = Q0_3; // K7
    // inputs
    int tank_level_pin       = I0_2; // HIGH with water
    int emergency_stop_pin   = I0_1; // HIGH on not activated
    int pv_panel_voltage_pin = I0_0;
    
    // digital filter cooldowns
    unsigned long tank_level_cooldown               =   60000;
    unsigned long emergency_stop_cooldown           =    5000;
    unsigned long pv_panel_voltage_cooldown         = 3600000;
        
    // operation times      
    unsigned long relay_activation_ms               = 5000;
    unsigned long irrigation_area_ms                = 60*1000; // 20*60*1000;
    unsigned long pump_protection_ms                = 10000;
        
    unsigned long irrigation_period_ms              = 24*60*60*1000;
    unsigned long irrigation_period_init_sync_ms    = 1*60*60*1000; // init time for synchronisation of first iteration
    
} app_data;

EvHandler ev1_handler = EvHandler();
EvHandler ev2_handler = EvHandler();
EvHandler ev3_handler = EvHandler();

Timer ev_timer                  = Timer();
Timer pump_timer                = Timer();
Timer irrigation_area_timer     = Timer();
Timer irrigation_period_timer   = Timer();

Process irrigation = Process();
Process protection = Process();

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
void pump_update_timer_ref(){
    pump_timer.update_timer_ref();
}
void irrigation_area_update_timer_ref(){
    irrigation_area_timer.update_timer_ref();
}
bool ev_timeout(){
    return ev_timer.timeout();
}
bool pump_timeout(){
    return pump_timer.timeout();
}
bool irrigation_area_timeout(){
    return irrigation_area_timer.timeout();
}


// ElectroValves
void ev1_opening(){
    ev1_handler.opening();
}
void ev2_opening(){
    ev2_handler.opening();
}
void ev3_opening(){
    ev3_handler.opening();
}
void ev1_closing(){
    ev1_handler.closing();
}
void ev2_closing(){
    ev2_handler.closing();
}
void ev3_closing(){
    ev3_handler.closing();
}
void ev1_idle(){
    ev1_handler.idle();
}
void ev2_idle(){
    ev2_handler.idle();
}
void ev3_idle(){
    ev3_handler.idle();
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
    pinMode(app_data.pump_relay_pin,  OUTPUT);

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
    ev2_handler.config(app_data.ev2_relay_pin_a, app_data.ev2_relay_pin_b);
    ev3_handler.config(app_data.ev3_relay_pin_a, app_data.ev3_relay_pin_b);

    ev_timer.config(app_data.relay_activation_ms);
    pump_timer.config(app_data.pump_protection_ms);
    irrigation_area_timer.config(app_data.irrigation_area_ms);
    irrigation_period_timer.config(app_data.irrigation_period_init_sync_ms);

    irrigation_period_timer.update_timer_ref();

    proj_actions.add_action("turn_on_pump", turn_on_pump);
    proj_actions.add_action("turn_off_pump", turn_off_pump);
    proj_actions.add_action("ev1_opening", ev1_opening);
    proj_actions.add_action("ev2_opening", ev2_opening);
    proj_actions.add_action("ev3_opening", ev3_opening);
    proj_actions.add_action("ev1_closing", ev1_closing);
    proj_actions.add_action("ev2_closing", ev2_closing);
    proj_actions.add_action("ev3_closing", ev3_closing);
    proj_actions.add_action("ev1_idle", ev1_idle);
    proj_actions.add_action("ev2_idle", ev2_idle);
    proj_actions.add_action("ev2_idle", ev2_idle);

    Step* aux_step;
    Step* aux_step_2;

    //// process protection
    // 0 - turn off pump
    aux_step = protection.get_step(0);
    aux_step->set_pre_op();
    aux_step->set_op(turn_off_pump);
    aux_step->set_transit();
    aux_step->set_post_op();
    // 1 - wait during pump_protection_ms
    aux_step = protection.get_step(1);
    aux_step->set_pre_op(pump_update_timer_ref);
    aux_step->set_op();
    aux_step->set_transit(pump_timeout);
    aux_step->set_post_op();
    // 2 - close ev1 during relay_activation_ms end with idle
    aux_step = protection.get_step(2);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev1_closing);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev1_idle);
    // 3 - close ev2 during relay_activation_ms end with idle
    aux_step = protection.get_step(3);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev2_closing);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev2_idle);
    // 4 - close ev3 during relay_activation_ms end with idle
    aux_step = protection.get_step(4);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev3_closing);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev3_idle);
    ////////////////////


    //// process irrigation
    // First section of protection for initialisation
    // 0 - turn off pump
    aux_step = protection.get_step(0);
    aux_step_2 = irrigation.get_step(0);
    aux_step_2 = aux_step;
    // 1 - wait during pump_protection_ms
    aux_step = protection.get_step(1);
    aux_step_2 = irrigation.get_step(1);
    aux_step_2 = aux_step;
    // 2 - close ev1 during relay_activation_ms end with idle
    aux_step = protection.get_step(2);
    aux_step_2 = irrigation.get_step(2);
    aux_step_2 = aux_step;
    // 3 - close ev2 during relay_activation_ms end with idle
    aux_step = protection.get_step(3);
    aux_step_2 = irrigation.get_step(3);
    aux_step_2 = aux_step;
    // 4 - close ev3 during relay_activation_ms end with idle
    aux_step = protection.get_step(4);
    aux_step_2 = irrigation.get_step(4);
    aux_step_2 = aux_step;

    // 5  - open ev1 during relay_activation_ms end with idle
    aux_step = irrigation.get_step(5);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev1_opening);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev1_idle);
    // 6  - turn on pump
    aux_step = irrigation.get_step(6);
    aux_step->set_pre_op();
    aux_step->set_op(turn_on_pump);
    aux_step->set_transit();
    aux_step->set_post_op();
    // 7  - wait during irrigation_area_ms
    aux_step = irrigation.get_step(7);
    aux_step->set_pre_op(irrigation_area_update_timer_ref);
    aux_step->set_op();
    aux_step->set_transit(irrigation_area_timeout);
    aux_step->set_post_op();
    // 8  - open ev2 during relay_activation_ms end with idle
    aux_step = irrigation.get_step(8);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev2_opening);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev2_idle);
    // 9  - close ev1 during relay_activation_ms end with idle
    aux_step = irrigation.get_step(9);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev1_closing);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev1_idle);
    // 10 - wait during irrigation_area_ms
    aux_step = irrigation.get_step(10);
    aux_step->set_pre_op(irrigation_area_update_timer_ref);
    aux_step->set_op();
    aux_step->set_transit(irrigation_area_timeout);
    aux_step->set_post_op();
    // 11 - open ev3 during relay_activation_ms end with idle
    aux_step = irrigation.get_step(11);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev3_opening);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev3_idle);
    // 12 - close ev2 during relay_activation_ms end with idle
    aux_step = irrigation.get_step(12);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev2_closing);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev2_idle);
    // 13 - wait during irrigation_area_ms
    aux_step = irrigation.get_step(13);
    aux_step->set_pre_op(irrigation_area_update_timer_ref);
    aux_step->set_op();
    aux_step->set_transit(irrigation_area_timeout);
    aux_step->set_post_op();
    // 14 - turn off pump
    aux_step = irrigation.get_step(14);
    aux_step->set_pre_op();
    aux_step->set_op(turn_off_pump);
    aux_step->set_transit();
    aux_step->set_post_op();
    // 15 - wait during pump_protection_ms
    aux_step = irrigation.get_step(15);
    aux_step->set_pre_op(pump_update_timer_ref);
    aux_step->set_op();
    aux_step->set_transit(pump_timeout);
    aux_step->set_post_op();
    // 16 - close ev3 during relay_activation_ms end with idle
    aux_step = irrigation.get_step(16);
    aux_step->set_pre_op(ev_update_timer_ref);
    aux_step->set_op(ev3_closing);
    aux_step->set_transit(ev_timeout);
    aux_step->set_post_op(ev3_idle);
    ////////////////////

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

    static bool irrigation_completed = true;

    bool emergency_stop_value = emergency_stop.get_filtered_value(digitalRead(app_data.emergency_stop_pin));
    bool tank_level_value = tank_level.get_filtered_value(digitalRead(app_data.tank_level_pin));
    bool pv_panel_voltage_value = pv_panel_voltage.get_filtered_value(digitalRead(app_data.pv_panel_voltage_pin));

    Log.verboseln("emergency_stop_value: %T", emergency_stop_value);
    Log.verboseln("tank_level_value: %T", tank_level_value);

    bool en_wifi_value = false;

    // clock based control
    if(irrigation_period_timer.timeout() && irrigation_completed){
        irrigation_period_timer.config(app_data.irrigation_period_ms);
        irrigation_period_timer.update_timer_ref();
        irrigation.reset();
        irrigation_completed = false;
    }

    // // Process irrigation reset happens even though system is in protection mode
    // if (pv_panel_voltage_value){ // day
    //     // Reset process: irrigation
    //     irrigation.reset();
    // }

    if (emergency_stop_value || !tank_level_value){
        irrigation.reset(); // security, avoid pump working with ev(s) closed
        // Process: protection
        protection.process();
        if (emergency_stop_value){
            // Turn on wifi and handle configuration through API
            en_wifi_value = true;
            serial_commands.handle_serial();
        }
    }
    else{
        // Reset process: protection
        protection.reset();

        if(irrigation_completed || irrigation.process_finished()){
            irrigation_completed = true;
        }
        else{
            irrigation.process();
        }

        // if (!pv_panel_voltage_value){ // night
        //     // Process: irrigation
        //     irrigation.process();
        // }
    }

    enable_wifi(en_wifi_value);

    // TODO: FFR do state machine to support manual tests
    
    return;
}
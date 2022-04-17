
#include <DigitalSignalFilters.h>

DigitalFilter::DigitalFilter(int pin, unsigned long cool_down){
    this->set_cool_down(cool_down);
    this->set_pin(pin);
}

DigitalFilter::DigitalFilter(int pin, unsigned long cool_down, bool init_value){
    this->set_cool_down(cool_down);
    this->set_pin(pin);

    this->force_value(init_value);
}

bool DigitalFilter::force_value(bool forced_value){
    this->_set_last_value(forced_value);
    this->_filtered_value = forced_value;
    this->_initialised = true;
    return this->_filtered_value;
}

unsigned long DigitalFilter::set_cool_down(unsigned long cool_down){
    this->_cool_down = cool_down;
    
    return this->_cool_down;
}

int DigitalFilter::set_pin(int pin){
    this->_pin = pin;
    pinMode(this->_pin, INPUT);

    return this->_pin;
}

int DigitalFilter::get_pin(){
    return this->_pin;
}

bool DigitalFilter::get_raw_value(){
    return digitalRead(this->_pin);
}

bool DigitalFilter::get_filtered_value(){
    bool current_value = digitalRead(this->_pin);

    // Initialisation: Get first value
    if (!this->_initialised){
        this->force_value(current_value);
    }
    // Filter operations
    else{
        // Update value change
        if( this->_last_value != current_value ){
            this->_set_last_value(current_value);
        }

        else{
            // Filter value
            if ( lapse(this->_last_value_time) > this->_cool_down ){
                this->_filtered_value = current_value;
            }
        }
    }

    return this->_filtered_value;
}

void DigitalFilter::_set_last_value(bool value){
    this->_last_value = value;
    this->_last_value_time = now();
}
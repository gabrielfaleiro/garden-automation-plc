
#include <Irrigation.h>

Irrigation::Irrigation(int relayPin, int pumpPin){
    // pin configuration
    this->_relayPin = relayPin;
    this->_pumpPin = pumpPin;

    // states
    this->_completed = false;
    this->_state = 0;
}

bool Irrigation::get_enable(){
    return this->_enable;
}

bool Irrigation::get_reset(){
    return this->_reset;
}

bool Irrigation::get_completed(){
    return this->_completed;
}

int Irrigation::get_state(){
    return this->_state;
}

void Irrigation::execute(bool enable, bool reset){
    this->_enable = enable;
    this->_reset = reset;

    switch (this->_state){
        case 0: // Init
            this->_completed = false;
            digitalWrite(this->_relayPin, LOW);
            digitalWrite(this->_pumpPin,  LOW);

            if (this->_enable && !this->_reset){
                this->_state = 1;
                this->_timerState1 = now();
            }
            break;

        case 1: // Open relay
            digitalWrite(this->_relayPin, HIGH);
            digitalWrite(this->_pumpPin,  LOW);

            if(lapse(this->_timerState1) >= this->_relayOpenOperationDelay){
                this->_state = 2;
                this->_timerState2 = now();
            }
            break;

        case 2: // Pumping
            digitalWrite(this->_relayPin, HIGH);
            digitalWrite(this->_pumpPin,  HIGH);

            if(lapse(this->_timerState2) >= this->_pumpingOperationTime){
                this->_state = 3;
                this->_timerState3 = now();
            }
            break;
        
        case 3: // Turning off pump
            digitalWrite(this->_relayPin, HIGH);
            digitalWrite(this->_pumpPin,  LOW);

            if(lapse(this->_timerState3) >= this->_pumpingOffOperationDelay){
                this->_state = 4;
                this->_timerState4 = now();
            }
            break;
        
        case 4: // Close relay
            digitalWrite(this->_relayPin, LOW);
            digitalWrite(this->_pumpPin,  LOW);

            if(lapse(this->_timerState4) >= this->_relayCloseOperationDelay){
                this->_state = 5;
            }
            break;
        
        case 5: // Completed
            this->_completed = true;
            digitalWrite(this->_relayPin, LOW);
            digitalWrite(this->_pumpPin,  LOW);

            if(this->_reset){
                this->_state = 0;
            }
            break;
    }

}

void Irrigation::set_relay_open_operation_delay(unsigned long value){
    this->_relayOpenOperationDelay = value;
}

void Irrigation::set_relay_close_operation_delay(unsigned long value){
    this->_relayCloseOperationDelay = value;
}

void Irrigation::set_pumping_off_operation_delay(unsigned long value){
    this->_pumpingOffOperationDelay = value;
}

void Irrigation::set_pumping_operation_time(unsigned long value){
    this->_pumpingOperationTime = value;
}

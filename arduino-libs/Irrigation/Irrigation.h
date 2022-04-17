
#include <Arduino.h>
#include <Time.h>

#ifndef _IRRIGATION_H
#define _IRRIGATION_H

class Irrigation{
    public:        
        Irrigation(int relayPin, int pumpPin);
        
        bool get_enable();
        bool get_reset();

        bool get_completed();

        int get_state();

        void execute(bool enable, bool reset);

        void set_relay_open_operation_delay(unsigned long value);
        void set_relay_close_operation_delay(unsigned long value);
        void set_pumping_off_operation_delay(unsigned long value);
        void set_pumping_operation_time(unsigned long value);
        
    private:
        // inputs
        bool _enable = false;
        bool _reset  = false;

        // states
        bool _completed = false;
        int  _state = 0;

        // pin configuration
        int _relayPin = 0;
        int _pumpPin = 0;

        // time configuration
        unsigned long _relayOpenOperationDelay = 0;
        unsigned long _relayCloseOperationDelay = 0;
        unsigned long _pumpingOffOperationDelay = 0;
        unsigned long _pumpingOperationTime = 0;

        // internal variables
        unsigned long _timerState1 = 0;
        unsigned long _timerState2 = 0;
        unsigned long _timerState3 = 0;
        unsigned long _timerState4 = 0;
        unsigned long _pumpingOperationTime = 0;

};

#endif

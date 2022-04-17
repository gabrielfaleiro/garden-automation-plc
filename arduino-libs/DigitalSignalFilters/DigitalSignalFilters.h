
#include <Arduino.h>
#include <Time.h>

#ifndef _DIGITALSIGNALFILTERS_H
#define _DIGITALSIGNALFILTERS_H

class DigitalFilter{
    public:        
        DigitalFilter(int pin, unsigned long cool_down);
        // Force init value if it is critial for the application 
        DigitalFilter(int pin, unsigned long cool_down, bool init_value);
        bool force_value(bool forced_value);

        unsigned long set_cool_down(unsigned long cool_down);
        int set_pin(int pin);
        int get_pin();

        bool get_raw_value();
        bool get_filtered_value();
        
    private:
        // Update value internally. Lighter function than force_value
        void _set_last_value(bool value);
        // Time in millis to filter signal
        // That's the amount of time the signal must be without changes to 
        // propagate the value
        unsigned long _cool_down = 0;
        // pin to read digital signals
        int _pin = 0;
        
        // Last filtered value
        bool _filtered_value = false;

        // Latest value change
        bool _last_value = false;
        unsigned long _last_value_time = 0;
        // true when first value is set
        bool _initialised = false;
};

#endif

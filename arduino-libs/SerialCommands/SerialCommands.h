
#include <Arduino.h>
#include <ArduinoLog.h>
#include "Actions.h"

#ifndef _SERIAL_COMMANDS_H
#define _SERIAL_COMMANDS_H

class SerialCommands{
    public:
        SerialCommands(Actions* actions_ref);

        void handle_serial();
    
    private:
        Actions* actions_ref;
};
    

#endif

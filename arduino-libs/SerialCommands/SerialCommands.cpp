
#include "SerialCommands.h"

SerialCommands::SerialCommands(Actions* actions_ref){
    this->actions_ref = actions_ref;
}

void SerialCommands::handle_serial(){
    String command;

    if (Serial.available()){
        command = Serial.readStringUntil('\n');
        command.trim();
        this->actions_ref->exec_action(command);
    }
}
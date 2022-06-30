
#include "Actions.h"

Actions::Actions(){
    uint i = 0;

    this->action_index = 0;

    for (i=0; i<MAX_ACTIONS; i++){
        this->action_list[i].command_name = "";
        this->action_list[i].func_action = _empty_void_method;
    }
}

String Actions::list_actions(){
    uint i = 0;
    String ret_val = "List of actions:\n";

    for (i=0; i<this->action_index; i++){
        ret_val += this->action_list[i].command_name + "\n";
    }

    return ret_val;
}

void Actions::add_action(String str_val, void (*func)()){
    if (this->action_index >= MAX_ACTIONS){
        Log.verboseln("action cannot be added, list is full");
    }
    else {
        this->action_list[this->action_index].command_name = str_val;
        this->action_list[this->action_index].func_action = func;
        this->action_index += 1;
    }
}

void Actions::exec_action(String str_val){
    uint i = 0;
    bool action_found = false;

    for (i=0; i<this->action_index; i++){
        if(this->action_list[i].command_name.equals(str_val)){
            this->action_list[i].func_action();
            action_found = true;
            break;
        }
    }
    if (! action_found){
        Log.verboseln("action not recognised");
    }
}
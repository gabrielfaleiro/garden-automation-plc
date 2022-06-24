
#include "Process.h"

Process::Process(){
    this->state = 0;
    this->autoreset = false;
}

void Process::_change_state(uint state){
    if (state >= PROCESS_MAX_STATES){
        if(this->autoreset){
            state = 0;
            Log.verboseln("Process: autoreseted");
        }
        else {
            // No state change
            Log.verboseln("Process: no state change");
            return;
        }
    }

    this->steps[this->state].post_op();
    this->state = state;
    this->steps[this->state].pre_op();
}

void Process::reset(){
    this->_change_state(0);
}

uint Process::get_state(){
    return this->state;
}

void Process::process(){
    // Do state operation
    this->steps[this->state].op();
    // Evaluate transition
    if (this->steps[this->state].transit()){
        this->_change_state(this->state + 1);
    }
}

Step* Process::get_step(uint state){
    Step* ret_val;
    if (state < PROCESS_MAX_STATES){
        ret_val = &(this->steps[state]);
    }
    else {
        ret_val = NULL;
    }

    return ret_val;
}

void Process::enable_autoreset(bool en){
    this->autoreset = en;
}

bool Process::process_finished(){
    bool ret_val = false;
    if (this->state >= PROCESS_MAX_STATES) ret_val = true;
    return ret_val;
}
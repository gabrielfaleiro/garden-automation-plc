
#include "Process.h"

Process::Process(){
    this->state = 0;
}

void Process::_change_state(uint state){
    // Default transition when not valid state: reset
    if (state >= PROCESS_MAX_STATES){
        state = 0;
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

void Process::set_step(uint state, Step step){
    this->steps[state] = step;
}
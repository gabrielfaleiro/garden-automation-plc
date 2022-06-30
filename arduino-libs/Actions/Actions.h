
#include <Arduino.h>
#include <ArduinoLog.h>
#include "Step.h"

#ifndef MAX_ACTIONS
#define MAX_ACTIONS 50
#endif

#ifndef _ACTIONS_H
#define _ACTIONS_H

struct action_struct {
    String command_name;
    void (*func_action)();
};

class Actions{
    public:        
        Actions();
        
        String list_actions();

        // action* get_action(String command_name);
        // action* get_action(uint position);

        void add_action(String str_val, void (*func)());
        void exec_action(String str_val);
        
    private:
        uint action_index;
        action_struct action_list[MAX_ACTIONS];
};

#endif

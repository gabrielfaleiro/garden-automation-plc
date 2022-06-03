
#include <Arduino.h>

#ifndef _STEP_H
#define _STEP_H

void _empty_void_method();
bool _empty_bool_method();

class Step{
    public:        
        Step();
        
        void pre_op();
        void op();
        void post_op();
        bool transit();

        void set_pre_op(void (*func)());
        void set_op(void (*func)());
        void set_post_op(void (*func)());
        void set_transit(bool (*func)());
        
    private:
        void (*_func_pre_op)();
        void (*_func_op)();
        void (*_func_post_op)();
        bool (*_func_transit)();
};

#endif

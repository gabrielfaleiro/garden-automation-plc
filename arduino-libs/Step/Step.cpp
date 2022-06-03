
#include "Step.h"

// REF: http://www.newty.de/fpt/fpt.html

void _empty_void_method(){
  return;
}

bool _empty_bool_method(){
  return true;
}

Step::Step(){
  this->_func_pre_op = _empty_void_method;
  this->_func_op = _empty_void_method;
  this->_func_post_op = _empty_void_method;
  this->_func_transit = _empty_bool_method;
}

void Step::pre_op(){
  return this->_func_pre_op();
}

void Step::set_pre_op(void (*func)()){
  this->_func_pre_op = func;
}

void Step::op(){
  return this->_func_op();
}

void Step::set_op(void (*func)()){
  this->_func_op = func;
}

void Step::post_op(){
  return this->_func_post_op();
}

void Step::set_post_op(void (*func)()){
  this->_func_post_op = func;
}

bool Step::transit(){
  return this->_func_transit();
}

void Step::set_transit(bool (*func)()){
  this->_func_transit = func;
}
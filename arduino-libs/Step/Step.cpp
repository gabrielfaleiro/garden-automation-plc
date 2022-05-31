
#include "Step.h"

// REF: http://www.newty.de/fpt/fpt.html

void _empty_void_method2(){
  return;
}

Step::Step(){
  this->_func_pre_op = _empty_void_method2;
  // this->_func_op = &this->_empty_void_method;
  // this->_func_post_op = &this->_empty_void_method;
  // this->_func_transit = &this->_empty_bool_method;
}

void Step::_empty_void_method(){
  return;
}

// bool Step::_empty_bool_method(){
//   return true;
// }

void Step::pre_op(){
  return this->_func_pre_op();
}

void Step::set_pre_op(void (*func)()){
  this->_func_pre_op = func;
}
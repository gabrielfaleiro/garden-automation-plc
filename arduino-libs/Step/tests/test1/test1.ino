////////////////////////////////////////////////////////
// test1: Step.h
// Test with functions
////////////////////////////////////////////////////////

#include <Step.h>

void custom_pre_op(){
  Serial.println("custom_pre_op");
}

void custom_op(){
  Serial.println("custom_op");
}

void custom_post_op(){
  Serial.println("custom_post_op");
}

bool false_transit(){
  Serial.println("false_transit");
  return false;
}

bool true_transit(){
  Serial.println("true_transit");
  return true;
}


void setup() {
  Serial.begin(9600);
  while(!Serial);

}


void loop() {
  
  Step step_f = Step();
  step_f.set_pre_op(custom_pre_op);
  step_f.set_op(custom_op);
  step_f.set_post_op(custom_post_op);
  step_f.set_transit(false_transit);
  step_f.pre_op();
  step_f.op();
  step_f.post_op();
  step_f.transit();
  
  Step step_t = Step();
  step_f.set_pre_op(custom_pre_op);
  step_f.set_op(custom_op);
  step_f.set_post_op(custom_post_op);
  step_f.set_transit(true_transit);
  step_f.pre_op();
  step_f.op();
  step_f.post_op();
  step_f.transit();

  
  delay(5000);
  
}
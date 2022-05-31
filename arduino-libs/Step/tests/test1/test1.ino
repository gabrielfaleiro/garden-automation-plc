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
  step_f.pre_op();
  Step step_t = Step();

  
  delay(5000);
  
}
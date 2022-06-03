#include "Process.h"
#include "Time.h"

Process proc = Process();
Step step1 = Step();
Step step2 = Step();

unsigned long timestamp = now();


void custom_pre_op(){
  Serial.println("custom_pre_op");
  timestamp = now();
}

void custom_op(){
  Serial.println("custom_op");
}

void custom_post_op(){
  Serial.println("custom_post_op");
}

bool test_transit(){
  Serial.println("test_transit");
  if(lapse(timestamp) > 5000) return true;
  else return false;
}

void setup() {
  // put your setup code here, to run once:
  step1.set_pre_op(custom_pre_op);
  step1.set_op(custom_op);
  step1.set_post_op(custom_post_op);
  step1.set_transit(test_transit);

  step2.set_pre_op(custom_pre_op);
  step2.set_op(custom_op);
  step2.set_post_op(custom_post_op);
  step2.set_transit(test_transit);

  proc.set_step(0, step1);
  proc.set_step(1, step2);

  proc.reset();
  
  Serial.begin(9600);
  while(!Serial);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  proc.process();
  Serial.print(proc.get_state());
  Serial.print(" - ");
  Serial.println(now());

  delay(1000);

}
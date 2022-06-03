////////////////////////////////////////////////////////
// test2: Step.h
// Test with class methods: only static methods.
// Otherwise, they are attached to the class namespace
// and must be specified.
////////////////////////////////////////////////////////

#include <Step.h>

class TestClass{
  public:
  TestClass(){
    return;
  }

  static void pre_op(){
    Serial.println("TestClass::pre_op()");
  }
};

void setup() {
  Serial.begin(9600);
  while(!Serial);

}

void loop() {

  Step step_f = Step();
  step_f.set_pre_op(&TestClass::pre_op);
  step_f.pre_op();
  Step step_t = Step();

  
  delay(5000);
  
}
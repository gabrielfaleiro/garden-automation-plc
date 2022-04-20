////////////////////////////////////////////////////////
// test1: DigitalSignalFilters.h
////////////////////////////////////////////////////////

#include <DigitalSignalFilters.h>

#define COOL_DOWN  1000


void setup() {
  Serial.begin(9600);
  while(!Serial);

}


void loop() {
  bool init_val = false;
  bool last_val = false;
  int i = 0;
  DigitalFilter filter = DigitalFilter(COOL_DOWN);

  delay(5000);

  // Test 1: constructor and check filter value equal to firstly introduced one. false
  init_val = false;
  filter = DigitalFilter(COOL_DOWN);
  filter.get_filtered_value(init_val);

  if (init_val == filter.get_filtered_value(!init_val)) Serial.println("Test 1: pass");
  else                                                  Serial.println("Test 1: fail");

  // Test 2: constructor and check filter value equal to firstly introduced one. true
  init_val = true;
  filter = DigitalFilter(COOL_DOWN);
  filter.get_filtered_value(init_val);

  if (init_val == filter.get_filtered_value(!init_val)) Serial.println("Test 2: pass");
  else                                                  Serial.println("Test 2: fail");
  
  // Test 3: constructor with init value and check filter value equal to init one after introducing the oposite one. false
  init_val = false;
  filter = DigitalFilter(COOL_DOWN, init_val);

  if (init_val == filter.get_filtered_value(!init_val)) Serial.println("Test 3: pass");
  else                                                  Serial.println("Test 3: fail");

  // Test 4: constructor with init value and check filter value equal to init one after introducing the oposite one. true
  init_val = true;
  filter = DigitalFilter(COOL_DOWN, init_val);

  if (init_val == filter.get_filtered_value(!init_val)) Serial.println("Test 4: pass");
  else                                                  Serial.println("Test 4: fail");

  // Test 5: constructor with init value and check filter value equal to forced. false -> true
  init_val = false;
  filter = DigitalFilter(COOL_DOWN, init_val);
  filter.force_value(!init_val);

  if (!init_val == filter.get_filtered_value(init_val)) Serial.println("Test 5: pass");
  else                                                  Serial.println("Test 5: fail");

  // Test 6: constructor with init value and check filter value equal to forced. true  -> false
  init_val = true;
  filter = DigitalFilter(COOL_DOWN, init_val);
  filter.force_value(!init_val);

  if (!init_val == filter.get_filtered_value(init_val)) Serial.println("Test 6: pass");
  else                                                  Serial.println("Test 6: fail");

  // Test 7: check filtered value is forced by forcing a shorter cooldown.
  init_val = false;
  filter = DigitalFilter(COOL_DOWN, init_val);
  filter.get_filtered_value(!init_val);
  delay(COOL_DOWN/2);
  filter.set_cool_down(COOL_DOWN/4);

  if (init_val == !filter.get_filtered_value(!init_val)) Serial.println("Test 7: pass");
  else                                                   Serial.println("Test 7: fail");

  // Test 8: check filtered value does not change when input value changes faster than the cooldown. false -> true
  init_val = false;
  filter = DigitalFilter(COOL_DOWN, init_val);
  last_val = init_val;
  for (i=0; i<20; i++){
    last_val = !last_val;
    filter.get_filtered_value(last_val);
    delay(COOL_DOWN/10);  
  }

  if (init_val == filter.get_filtered_value(!init_val)) Serial.println("Test 8: pass");
  else                                                  Serial.println("Test 8: fail");

  // Test 9: check filtered value does not change when input value changes faster than the cooldown. true  -> false
  init_val = true;
  filter = DigitalFilter(COOL_DOWN, init_val);
  last_val = init_val;
  for (i=0; i<20; i++){
    last_val = !last_val;
    filter.get_filtered_value(last_val);
    delay(COOL_DOWN/10);  
  }

  if (init_val == filter.get_filtered_value(!init_val)) Serial.println("Test 9: pass");
  else                                                  Serial.println("Test 9: fail");

  // Test 10: check filtered value does change when input value changes slower than the cooldown. false -> true
  init_val = false;
  filter = DigitalFilter(COOL_DOWN, init_val);
  filter.get_filtered_value(!init_val);
  delay(COOL_DOWN + 10);
  filter.get_filtered_value(!init_val);

  if (!init_val == filter.get_filtered_value(init_val)) Serial.println("Test 10: pass");
  else                                                  Serial.println("Test 10: fail");

  // Test 11: check filtered value does change when input value changes slower than the cooldown. true  -> false
  init_val = true;
  filter = DigitalFilter(COOL_DOWN, init_val);
  filter.get_filtered_value(!init_val);
  delay(COOL_DOWN + 10);
  filter.get_filtered_value(!init_val);

  if (!init_val == filter.get_filtered_value(init_val)) Serial.println("Test 11: pass");
  else                                                  Serial.println("Test 11: fail");
  

  delay(5000);
  
}

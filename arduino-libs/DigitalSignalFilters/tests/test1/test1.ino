////////////////////////////////////////////////////////
// test1: Time.h
////////////////////////////////////////////////////////

#include <Time.h>

#define FIRST_MILLIS_LAPSE  5
#define SECOND_MILLIS_LAPSE 400000

#define MILLIS_MARGIN       0

#define FIRST_MICROS_LAPSE  500
#define SECOND_MICROS_LAPSE 40000000

#define MICROS_MARGIN       3

#define MAX_UINT_LONG_VALUE 0xffffffff


unsigned long diff(unsigned long a, unsigned long b) {
  unsigned long ret = 0;
  if (a>b) ret = a-b;
  else     ret = b-a;

  return ret;
}


void setup() {
  Serial.begin(9600);
  while(!Serial);

}


void loop() {
  unsigned long timer = 0;
  unsigned long t1_lapse = 0;
  unsigned long t2_lapse = 0;
  unsigned long t2_calculated_lapse = 0;
  unsigned long t3_lapse = 0;
  unsigned long t4_lapse = 0;
  unsigned long t4_calculated_lapse = 0;

  delay(5000);


  timer = now();
  delay(FIRST_MILLIS_LAPSE);
  t1_lapse = lapse(timer);

  // Test 1: first lapse ms
  if (diff(t1_lapse, FIRST_MILLIS_LAPSE) <= MILLIS_MARGIN) Serial.println("Test 1: pass");
  else                                                     Serial.println("Test 1: fail");


  timer = now();
  t2_calculated_lapse = MAX_UINT_LONG_VALUE - SECOND_MILLIS_LAPSE;
  t2_lapse = lapse(timer + SECOND_MILLIS_LAPSE);
  
  // Test 2: second lapse ms, overflow test
  if (diff(t2_calculated_lapse, t2_lapse) <= MILLIS_MARGIN) Serial.println("Test 2: pass");
  else                                                      Serial.println("Test 2: fail");


  timer = now(true);
  delayMicroseconds(FIRST_MICROS_LAPSE);
  t3_lapse = lapse(timer, true);
  
  // Test 3: first lapse us
  if (diff(t3_lapse, FIRST_MICROS_LAPSE) <= MICROS_MARGIN ) Serial.println("Test 3: pass");
  else                                                      Serial.println("Test 3: fail");


  timer = now(true);
  t4_calculated_lapse = MAX_UINT_LONG_VALUE - SECOND_MICROS_LAPSE;
  t4_lapse = lapse(timer + SECOND_MICROS_LAPSE, true);

  // Test 4: second lapse us, overflow test
  if (diff(t4_calculated_lapse, t4_lapse) <= MICROS_MARGIN ) Serial.println("Test 4: pass");
  else                                                       Serial.println("Test 4: fail");


  delay(5000);
  
}

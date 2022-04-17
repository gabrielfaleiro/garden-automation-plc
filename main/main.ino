// /home/<user>/Arduino/libraries
#include <Time.h>
#include <DigitalSignalFilters.h>
// #include <AnalogSignalFilters.h> // TODO
#include <Irrigation.h>

// bool: (1) day, (0) night
#define SUN_LIGHT_IRRIGATION_TIME         0

// ms
#define LIGHT_COOLDOWN              1800000

#define RELAY_OPEN_OPERATION_DELAY     5000
#define RELAY_CLOSE_OPERATION_DELAY    5000
#define PUMPING_OFF_OPERATION_DELAY    5000
#define PUMPING_OPERATION_TIME      1805000


#define DEBUG

//// Global variables
unsigned long timerSolarFeedback  = now();
unsigned long timerIrrigation     = now();
DigitalFilter sunLight = DigitalFilter( I0_3, LIGHT_COOLDOWN, (bool) !SUN_LIGHT_IRRIGATION_TIME );
short unsigned int irrigationControl = 0;
Irrigation irrigation1 = Irrigation(Q0_6, Q0_7);


void setup() {
  #ifdef DEBUG
  //Debugging
  Serial.begin(9600);
  while(!Serial);
  #endif

  /*
  // PINOUT (voltage configuration)
  - I0.0 ( 5V)
  - I0.1 ( 5V)
  - I0.2 ( 5V)
  - I0.3 (24V): solar panel output
  - I0.4 (24V)

  - Q0.5 ( 5V): 5V power supply up to 300mA
  - Q0.6 ( 5V): relay control
  - Q0.7 ( 5V)
  - Q0.8 (24V): feedback solar panel digital read true
  - Q0.9 (24V)
  */

  // solar panel output (24V)
  // sunLight (global): I0_3
  
  // 5V output. Up to 300mA
  pinMode(Q0_5, OUTPUT);
  digitalWrite(Q0_5, HIGH);
  
  // Relay control
  pinMode(Q0_6, OUTPUT);
  digitalWrite(Q0_6, LOW);

  // Pump control
  pinMode(Q0_7, OUTPUT);
  digitalWrite(Q0_7, LOW);

  // feedback solar panel digital read true
  pinMode(Q0_8, OUTPUT);
  digitalWrite(Q0_8, LOW);

  timerSolarFeedback = now();
  timerIrrigation    = now();
}

void loop() {
  // TODO: use arrays to handle multiple relay configurations
  bool enIrrig1   = false;  // enable
  // bool enIrrig2   = false;  // enable
  bool rst        = false;   // reset
  

  // Irrigation control
  if(lapse(timerIrrigation) >= 100){

    timerIrrigation = now();

    if( sunLight.get_filtered_value() == (bool) SUN_LIGHT_IRRIGATION_TIME ){ 
      // Irrigation
      rst = false;
    }
    else{           
      // Reseting
      rst = true;
      irrigationControl = 0;
    }
  
    switch(irrigationControl){
      case 0:
        // Init
        if ( !rst ) irrigationControl = 1;
        break;
      case 1:
        enIrrig1 = true;
        if ( irrigation1.get_completed() ) irrigationControl = 2;
        break;
//      case 2:
//        // enIrrig2 = true;
//        // if ( irrigation2.get_completed() ) irrigationControl = 3;
//        break;
      case 2:
        // Waiting
        break;
    }

    irrigation1.execute( enIrrig1, rst );
    // irrigation2.execute( enIrrig2, rst );
    
  }
  
  
  // Solar panel reading feedback
  if(lapse(timerSolarFeedback) >= 1000){
    
    timerSolarFeedback = now();
    
    digitalWrite(Q0_8, sunLight.get_raw_value());
    
  }

//  Serial.print(now());
//  Serial.print(" - ");
//  Serial.print(now(true));
//  Serial.println();    
  
}

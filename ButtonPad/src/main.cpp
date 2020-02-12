
#include <Arduino.h>
#include "ButtonPad.h"


#include "step/Step.h"
#include "step/StepPeriod.h"
#include "step/MultiStep.h"
#include "SpeedPush.h"

void pressButton(unsigned int col, unsigned int row, ButtonPad &pad){
  pad.LED_outputs[col][row]++; 
}

typedef Step* StepPP;
ButtonPad pad = ButtonPad();//(pressButton);//*btnselpins, *ledselpins, *btnreadpins, **colorpins);
StepPeriod s1  = StepPeriod();
StepPeriod s2  = StepPeriod();
MultiStep ms = MultiStep();
StepPP steps[2] = {&s1,&s2};
SpeedPush sp = SpeedPush(&pad);

bool lightOn(int i) {
  pad.LED_outputs[i%NUM_LED_COLUMNS][(i/NUM_LED_COLUMNS)%NUM_LED_ROWS]++;
  return i >= (NUM_LED_COLUMNS * NUM_LED_ROWS * NUM_COLORS)-1;
}
bool random(int i) {
  unsigned int j = random();
  pad.LED_outputs[j%NUM_LED_COLUMNS][(j/NUM_LED_COLUMNS)%NUM_LED_ROWS] = random(1,4);
  return false;
}
void initRandom() {
  for(int i = 0; i < NUM_LED_COLUMNS * NUM_LED_ROWS * NUM_COLORS; i++){
    pad.LED_outputs[i%NUM_LED_COLUMNS][(i/NUM_LED_COLUMNS)%NUM_LED_ROWS] = random(1,4);
  }
}

void setup() 
{
  



  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("Starting Setup...");


  pad.setup();

  s2.customInit = initRandom;
  s2.customPeriodicAction = random;
  s1.customPeriodicAction = lightOn;
  
  ms.steps=steps;

  sp.init();
  Serial.println("Setup Complete.");
}

void loop() {
  sp.run();
  pad.scan();
}



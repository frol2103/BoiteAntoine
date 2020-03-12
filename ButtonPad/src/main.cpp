
#include <Arduino.h>
#include "part/ButtonPad.h"


#include "step/Step.h"
#include "step/StepPeriod.h"
#include "step/MultiStep.h"
#include "game/SpeedPush.h"
#include "game/SimplePush.h"
#include "game/DrawingBPad.h"
#include <ShiftRegister74HC595.h>
#include "part/RgbLedArray.hpp"

#include "part/TriSelect.h"
#include <Wire.h>

TriSelect triselect = TriSelect();


#define SHIFT_REGISTER_DATA (0)
#define SHIFT_REGISTER_CLOCK (1)
#define SHIFT_REGISTER_LATCH (2)
ShiftRegister74HC595<1> sr(SHIFT_REGISTER_DATA, SHIFT_REGISTER_CLOCK, SHIFT_REGISTER_LATCH);
long iter=0;
long lastIter=0;

void pressButton(unsigned int col, unsigned int row, ButtonPad &pad){
  pad.LED_outputs[col][row]++; 
}

typedef Step* StepPP;
ButtonPad pad = ButtonPad();//(pressButton);//*btnselpins, *ledselpins, *btnreadpins, **colorpins);
StepPeriod s1  = StepPeriod();
StepPeriod s2  = StepPeriod();
MultiStep ms = MultiStep();
StepPP steps[2] = {&s1,&s2};

RgbLedArray rgbLedArray = RgbLedArray();

SpeedPush speedPush= SpeedPush(&pad);
SimplePush simplePush = SimplePush(&pad);
DrawingBPad drawingBPad = DrawingBPad(&pad);

GameStep *currentGame = &speedPush;

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
  Wire.begin();



  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("Starting Setup...");


  pad.setup();

  s2.customInit = initRandom;
  s2.customPeriodicAction = random;
  s1.customPeriodicAction = lightOn;
  
  ms.steps=steps;

  speedPush.init();
  simplePush.init();
  Serial.println("Setup Complete.");

  rgbLedArray.init();
}

void loop() {

  triselect.run();


  if(triselect.hasNewState()){
    if(triselect.state == 0){
      currentGame= &speedPush;
    } else if(triselect.state == 1) {
      currentGame = &simplePush;
    } else {
      currentGame = &drawingBPad;
    }
    currentGame->init();
  }
  currentGame->run();

  pad.scan();
  
  if(millis() - lastIter > 1000){
    lastIter=millis();
    iter ++;
    sr.setAllLow();
    sr.set(iter%8,HIGH);
  }
  
  rgbLedArray.run();
}



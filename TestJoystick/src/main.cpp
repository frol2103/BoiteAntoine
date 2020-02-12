#include <Arduino.h>

#include "Joystick.hpp"

#define JOYSTICK_MARGIN (200)

#define JOY_PIN_X (A0)
#define JOY_PIN_Y (A1)
 
Joystick j(JOY_PIN_X, JOY_PIN_Y);

 void setup() {
  Serial.begin(9600);
 }


  void loop() {
//    if(xMovement() == 1) Serial.print("UP ");
//    if(xMovement() == -1) Serial.print("DOWN ");   
//    if(yMovement() == 1) Serial.print("LEFT ");
//    if(yMovement() == -1) Serial.print("RIGHT ");
//    Serial.println("");
   j.loop();
   
 }
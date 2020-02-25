#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Jackpot.h"
#include "InTheBox.h"
#include "Joystick.hpp"
#include "Drawing.h"
#include <step/Step.h>
#include <Comm.h>

#include <ShiftRegister74HC595.h>
#include "part/DigitDisplay.h"

#define SHIFT_REGISTER_DATA (0)
#define SHIFT_REGISTER_CLOCK (1)
#define SHIFT_REGISTER_LATCH (2)

ShiftRegister74HC595<3> sr(49,50,48);
DigitDisplay dd(&sr);
  //SHIFT_REGISTER_DATA, SHIFT_REGISTER_CLOCK, SHIFT_REGISTER_LATCH);
long iter=-1;
long lastIter=-1;

long lastRead = 0;

int buttonState = 0;
int lastButtonState = 5;

void setup()
{


   pinMode(9, INPUT);
  Serial.begin(9600);
      sr.setAllLow();
    
  Serial.println("Hello");
}

void loop()
{

  
//Serial.println(analogRead(A1));
//delay(200);


if(
  millis() - lastIter > 1000
){
  lastIter=millis();
    iter++;
    dd.code[0]=iter%10;
    dd.code[1]=(iter+1)%10;
    dd.code[2]=(iter+2)%10;
    dd.code[3]=(iter+3)%10;

    sr.setAllLow();
    int pin =(iter%(24-13))+13;
    sr.set(pin,HIGH);

    Serial.print("pull up ");
    Serial.println(pin);


  }
  dd.run();
}
  



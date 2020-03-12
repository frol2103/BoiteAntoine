#include <Arduino.h>
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
#include <Wire.h> 

#include "SpeedClick.h"
#include <part/Button.h>
#include <Wire.h>



#define SHIFT_REGISTER_DATA (0)
#define SHIFT_REGISTER_CLOCK (1)
#define SHIFT_REGISTER_LATCH (2)

ShiftRegister74HC595<3> sr(23,24,22);
DigitDisplay dd(&sr);

long iter=-1;
long lastIter=-1;

long lastRead = 0;

int buttonState = 0;
int lastButtonState = 5;
bool showScore = false;

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 3
#define CLK_PIN 52  // or SCK
#define DATA_PIN 51 // or MOSI
#define CS_PIN 53   // or SS
#define BUTTON_PIN 30
#define BUTTON_PIN_SCREEN_3 32
#define CHANGE_GAME_BUTTON_PIN 31

#define JOY_PIN_X (A1)
#define JOY_PIN_Y (A0)
#define JOY_PIN_CLICK (36)

#define VOLTMETER_PIN (9)

 
Button buttonScreen1 = Button(BUTTON_PIN);
Button buttonScreen3 = Button(BUTTON_PIN_SCREEN_3);

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MdmaxScreen screen = MdmaxScreen(3, &mx);

 Joystick joystick = Joystick(JOY_PIN_X, JOY_PIN_Y,JOY_PIN_CLICK);
 Drawing drawing = Drawing(&screen, &joystick);
Jackpot jackpot = Jackpot(&screen, BUTTON_PIN);
InTheBox inTheBox = InTheBox(&screen, BUTTON_PIN);
SpeedClick speedClick = SpeedClick(&screen, &buttonScreen1, &buttonScreen3);

Game *games[] = {
    &jackpot,
    &inTheBox,
    &speedClick,
    &drawing,
};

int numberOfGames = 4;

int state = 0;
int previousState = -1;
int lastChangeGameButtonState = HIGH;
bool showingText = true;

void resetMatrix(void)
{
  screen.reset();
}

void runMatrixAnimation(void)
{
  if(previousState != state){
    screen.showText(games[state]->title());
    showingText = true;
    games[state] -> reset();
    previousState = state;
  }
  if (showingText)
  {
    showingText = !screen.showCurrentText();
  }
  else
  {
    games[state]->run();
  }
}

void receiveEvent(int howMany)
{

  showScore = true;
  unsigned int x = 0;
  x |= Wire.read();
  x |= Wire.read()<<8;
  
  dd.set(x);
  Serial.println(howMany); 
  Serial.println(x); 
}

void setup()
{
  Wire.begin(4);
  Wire.onReceive(receiveEvent); 
  Serial.begin(115200);

  pinMode(JOY_PIN_CLICK, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(CHANGE_GAME_BUTTON_PIN, INPUT_PULLUP);
  pinMode(VOLTMETER_PIN,OUTPUT);
   sr.setAllLow();
   mx.begin();
  for (int i = 0; i < numberOfGames; i++)
  {
    games[i]->init();
  }

    
  
}

void loop()
{
  buttonScreen1.run();
  buttonScreen3.run();

if(
  millis() - lastIter > 1000
){
  lastIter=millis();
  iter++;
  if(!showScore){   
      dd.code[0]=random(0,10);
      dd.code[1]=random(0,10);
      dd.code[2]=random(0,10);
      dd.code[3]=random(0,10);
  }
    sr.setAllLow();
    int pin =(iter%(16-13))+13;
    sr.set(pin,HIGH);

    int voltMeterValue = random(0,6)*(255/5);
    analogWrite(VOLTMETER_PIN, voltMeterValue);




  }
  dd.run();

  joystick.loop();
  int buttonState = digitalRead(CHANGE_GAME_BUTTON_PIN);
  if (lastChangeGameButtonState != buttonState)
  {
    if (buttonState == LOW)
    {
      state++;
      state%=numberOfGames;
    
      Serial.println("\nCHANGE_GAME");
    }
    lastChangeGameButtonState = buttonState;
  }
  runMatrixAnimation();
}                   


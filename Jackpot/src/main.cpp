#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Jackpot.h"
#include "InTheBox.h"
#include "Joystick.hpp"
#include "Drawing.h"
#include <step/Step.h>
#include <Comm.h>

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 3
#define CLK_PIN 13  // or SCK
#define DATA_PIN 11 // or MOSI
#define CS_PIN 10   // or SS
#define BUTTON_PIN 2
#define CHANGE_GAME_BUTTON_PIN 3

#define JOYSTICK_BUTTON 4
#define JOY_PIN_X (A0)
#define JOY_PIN_Y (A1)
 


MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MdmaxScreen screen = MdmaxScreen(3, &mx);

 Joystick joystick = Joystick(JOY_PIN_X, JOY_PIN_Y, JOYSTICK_BUTTON);
 Drawing drawing = Drawing(&screen, &joystick);
Jackpot jackpot = Jackpot(&screen, BUTTON_PIN);
InTheBox inTheBox = InTheBox(&screen, BUTTON_PIN);

Game *games[] = {
    &drawing,
    &jackpot,
    &inTheBox,
};

int numberOfGames = 3;

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

void setup()
{
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(CHANGE_GAME_BUTTON_PIN, INPUT_PULLUP);
  mx.begin();
  for (int i = 0; i < numberOfGames; i++)
  {
    games[i]->init();
  }
  Serial.begin(9600);
}

void loop()
{
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
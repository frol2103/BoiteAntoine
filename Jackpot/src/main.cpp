#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Jackpot.h"
#include "InTheBox.h"
#include "Joystick.hpp"
#include "Drawing.h"

#define DEBUG 1 // Enable or disable (default) debugging output

#if DEBUG
#define PRINT(s, v)     \
  {                     \
    Serial.print(F(s)); \
    Serial.print(v);    \
  } // Print a string followed by a value (decimal)
#define PRINTX(s, v)      \
  {                       \
    Serial.print(F(s));   \
    Serial.print(v, HEX); \
  } // Print a string followed by a value (hex)
#define PRINTB(s, v)      \
  {                       \
    Serial.print(F(s));   \
    Serial.print(v, BIN); \
  } // Print a string followed by a value (binary)
#define PRINTC(s, v)       \
  {                        \
    Serial.print(F(s));    \
    Serial.print((char)v); \
  } // Print a string followed by a value (char)
#define PRINTS(s)       \
  {                     \
    Serial.print(F(s)); \
  } // Print a string
#else
#define PRINT(s, v)  // Print a string followed by a value (decimal)
#define PRINTX(s, v) // Print a string followed by a value (hex)
#define PRINTB(s, v) // Print a string followed by a value (binary)
#define PRINTC(s, v) // Print a string followed by a value (char)
#define PRINTS(s)    // Print a string
#endif

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 3
#define CLK_PIN 13  // or SCK
#define DATA_PIN 11 // or MOSI
#define CS_PIN 10   // or SS
#define BUTTON_PIN 2
#define CHANGE_GAME_BUTTON_PIN 3

#define JOY_PIN_X (A0)
#define JOY_PIN_Y (A1)
 

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MdmaxScreen screen = MdmaxScreen(3, &mx);

 Joystick joystick = Joystick(JOY_PIN_X, JOY_PIN_Y);
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
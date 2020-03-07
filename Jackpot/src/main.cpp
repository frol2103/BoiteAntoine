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
#include <LiquidCrystal_I2C.h> 




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


#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
#define MAX_DEVICES 3
#define CLK_PIN 52  // or SCK
#define DATA_PIN 51 // or MOSI
#define CS_PIN 53   // or SS
#define BUTTON_PIN 30
#define CHANGE_GAME_BUTTON_PIN 31

#define JOY_PIN_X (A1)
#define JOY_PIN_Y (A0)
#define JOY_PIN_CLICK (36)

#define VOLTMETER_PIN (9)

 

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MdmaxScreen screen = MdmaxScreen(3, &mx);

 Joystick joystick = Joystick(JOY_PIN_X, JOY_PIN_Y,JOY_PIN_CLICK);
 Drawing drawing = Drawing(&screen, &joystick);
Jackpot jackpot = Jackpot(&screen, BUTTON_PIN);
InTheBox inTheBox = InTheBox(&screen, BUTTON_PIN);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

Game *games[] = {
   
    &jackpot,
    &inTheBox,
     &drawing,
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

    lcd.begin(16,2); // sixteen characters across - 2 lines
  lcd.backlight();
  // first character - 1st line
  lcd.setCursor(0,0);
  lcd.print("Antoinematic");
  // 8th character - 2nd line 
  lcd.setCursor(8,1);
  lcd.print("-----v1");
  
}

void loop()
{

if(
  millis() - lastIter > 1000
){
  lastIter=millis();
    iter++;
    dd.code[0]=random(0,10);
    dd.code[1]=random(0,10);
    dd.code[2]=random(0,10);
    dd.code[3]=random(0,10);

    sr.setAllLow();
    int pin =(iter%(16-13))+13;
    sr.set(pin,HIGH);

    int voltMeterValue = random(0,6)*(255/5);
    analogWrite(VOLTMETER_PIN, voltMeterValue);

    Serial.print("pull up ");
    Serial.println(pin);


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


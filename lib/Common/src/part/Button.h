#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "StateCounter.h"

class Button : public StateCounter
{
private:
    int _buttonPin; 
    char _lastButtonState = -1;
public:
    Button(int pin);
    ~Button();
    void run();
    bool clicked(){
        return _lastButtonState;
    }
};

Button::Button(int pin)
{
    _buttonPin = pin;
}

Button::~Button()
{
}

void Button::run(){
    char buttonState = digitalRead(_buttonPin);
    if (_lastButtonState != buttonState)
    {
        if (buttonState == LOW)
        {
            StateCounter::updateState();
        }
        _lastButtonState = buttonState;
    }
}


#endif
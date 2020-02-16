#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <Arduino.h>

#define JOYSTICK_MARGIN (200)
#define UP (2)
#define DOWN (1)
#define LEFT (8)
#define RIGHT (4)


class Joystick
{
public:
    typedef uint8_t JoystickPosition;
    class JoystickEventCallable{
    public:
        virtual void joystickPositionChange(JoystickPosition p){}
        virtual void joystickPressed(){}
    };

    Joystick(uint8_t _pinX, uint8_t _pinY, uint8_t _pinClick)
    {
        pinX = _pinX;
        pinY = _pinY;
        pinClick = _pinClick;
    }
    JoystickEventCallable *eventListener = NULL;

    void loop()
    {
    
        JoystickPosition pos = position();
        if (pos != lastPosition){
            lastPosition = pos;
            lastChange = millis();

            if(eventListener){
                eventListener -> joystickPositionChange(pos);
            }
        }
        int clicked=digitalRead(pinClick);
        if (clicked != lastClicked){
            lastClicked = clicked;
            if(clicked == LOW){
                Serial.println("Clicked");
                eventListener -> joystickPressed();
            }
        }
    }
    static int xPos(JoystickPosition pos){
        return 0 + (pos & LEFT)?1:0 + (pos & RIGHT)?-1:0;
    }
    static int yPos(JoystickPosition pos){
        return 0 + (pos & UP)?1:0 + (pos & DOWN)?-1:0;
    }

private:
    uint8_t pinX;
    uint8_t pinY;
    uint8_t pinClick;

    uint8_t lastPosition;
    int lastClicked;
    long lastChange;

    
    int position(uint8_t pin)
    {
        int value = analogRead(pin);
        if (value < JOYSTICK_MARGIN)
            return 1;
        if (value > (1024 - JOYSTICK_MARGIN))
            return 2;
        else
            return 0;
    }

    JoystickPosition position()
    {
        return position(pinX) | (position(pinY) << 2);
    }
};

#endif
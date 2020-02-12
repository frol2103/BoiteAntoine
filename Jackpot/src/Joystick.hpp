#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <Arduino.h>

#define JOYSTICK_MARGIN (200)
#define UP (1)
#define DOWN (2)
#define LEFT (8)
#define RIGHT (4)


class Joystick
{
public:
    typedef uint8_t JoystickPosition;
    class JoystickMovementCallable{
    public:
        virtual void joystickPositionChange(JoystickPosition p){}
    };

    Joystick(uint8_t _pinX, uint8_t _pinY)
    {
        pinX = _pinX;
        pinY = _pinY;
    }
    JoystickMovementCallable *onChangePosition = NULL;

    void loop()
    {
    
        JoystickPosition pos = position();
        if (pos != lastPosition){
            lastPosition = pos;
            lastChange = millis();

            if(onChangePosition){
                onChangePosition -> joystickPositionChange(pos);
            }
        }
    }
    static int xPos(JoystickPosition pos){
        return 0 + (pos & UP)?1:0 + (pos & DOWN)?-1:0;
    }
    static int yPos(JoystickPosition pos){
        return 0 + (pos & RIGHT)?1:0 + (pos & LEFT)?-1:0;
    }

private:
    uint8_t pinX;
    uint8_t pinY;

    uint8_t lastPosition;
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
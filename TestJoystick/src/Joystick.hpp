#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <Arduino.h>

#define JOYSTICK_MARGIN (200)
#define UP (1)
#define DOWN (2)
#define LEFT (8)
#define RIGHT (4)

// class JoystickMovementListener
// {
// public:
//     virtual movement(uint8_t movement);
// }


class Joystick
{
public:

    typedef uint8_t JoystickPosition;
    template<typename T>
    class JoystickMovementCallable{
    public:
        JoystickMovementCallable(T * _obj, void (T::*_f)(JoystickPosition)){
            obj = _obj;
            f = _f;
        }
        T * obj;
        void (T::*f)(Joystick::JoystickPosition);
        void call(JoystickPosition p){
            obj -> f(p);
        }
    };

    Joystick(uint8_t _pinX, uint8_t _pinY)
    {
        pinX = _pinX;
        pinY = _pinY;
    }

    void loop()
    {
    
        JoystickPosition pos = position();
        if (pos != lastPosition){
            lastPosition = pos;
            lastChange = millis();
            
        }
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
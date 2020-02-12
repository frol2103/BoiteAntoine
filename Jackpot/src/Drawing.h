#ifndef DRAWING_H
#define DRAWING_H

#include <Game.h>
#include "Joystick.hpp"


class Drawing : public Game, public Joystick::JoystickMovementCallable
{
public: 
    Drawing(MdmaxScreen *screen, Joystick* joystick);
    char* title(){return "Dessin";}
    void reset() { 
        Game::reset();
        joystick -> onChangePosition = (Joystick::JoystickMovementCallable *) this;   
    }
    void doRun(){
        screen -> reset();
        screen -> mx -> setPoint(selectionLeftRight.x, selectionLeftRight.y, true);

    };
    void joystickPositionChange(Joystick::JoystickPosition position){
        selectionLeftRight.x += Joystick::xPos(position);
        selectionLeftRight.y += Joystick::yPos(position);
        Serial.print(selectionLeftRight.x);
        Serial.print("-");
        Serial.println(selectionLeftRight.y);
    }



private:
    Joystick *joystick;
    MdmaxScreen::Position selectionLeftRight = MdmaxScreen::Position(0,0);
};


Drawing::Drawing(MdmaxScreen *_mx, Joystick * _joystick) : Game(_mx)
{
    joystick = _joystick;

}


#endif
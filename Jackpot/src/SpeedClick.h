#ifndef SPEED_CLICK_H
#define SPEED_CLICK_H

#include <Game.h>


class SpeedClick : public Game{
public: 
    Drawing(MdmaxScreen *screen, int buttonScreen1Pin,int buttonScreen2Pin);
    char* title(){return "Click course";}
    void reset() { 
        Game::reset();
        joystick -> eventListener = (Joystick::JoystickEventCallable *) this;   
        for(int i = 0; i < IMAGE_COLS ;i++){
            image[i] = 0;
        }
    }
    void doRun(){
        Game::doRun();
        screen -> mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
        screen -> mx -> clear();
        for(int i = 0; i < IMAGE_COLS ;i++){
            screen -> mx -> setColumn(i, image[i]);
        }
        bool blink = (iter / 100) % 2 == 0;
        if(mode == 0){
            screen->mx->setPoint(selectionLeftRight.y, selectionLeftRight.x, blink);
        } else {
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    screen->mx->setPoint(selectionLeftRight.y+i, selectionLeftRight.x+j, 
                        screen->mx->getPoint(selectionLeftRight.y+i, selectionLeftRight.x+j) ^ blink);
                }    
            }

        }
        
        screen -> mx -> control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
            

    };
    void joystickPositionChange(Joystick::JoystickPosition position){
        int factor = (mode == 1)? 4 : 1;
        int margin = factor -1 ;
        int possibleX = selectionLeftRight.x + Joystick::xPos(position) * factor;
        int possibleY = selectionLeftRight.y + Joystick::yPos(position) * factor;
        
        selectionLeftRight.x = max(0,min(IMAGE_COLS-1-margin, possibleX));
        selectionLeftRight.y = max(0,min(IMAGE_ROWS-1-margin, possibleY));

        Serial.print(selectionLeftRight.x);
        Serial.print("-");
        Serial.println(selectionLeftRight.y);

        byte ledSelection[2] = {0,0};
        for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    ledSelection[i/2] |= (image[selectionLeftRight.x+i] & 1 << (selectionLeftRight.y+j))?1 << (i%2*4 + j):0 ; 
                }    
            }
        send(Message(LED_BLOC,ledSelection));
        
    }
    void joystickPressed(){
        if (mode == 0)
        {
            image[selectionLeftRight.x] = image[selectionLeftRight.x] ^ 1 << selectionLeftRight.y;
        }
    }
    byte image[3*8];
    uint8_t mode = 0;



private:
    Joystick *joystick;
    MdmaxScreen::Position selectionLeftRight = MdmaxScreen::Position(0,0);
};


Drawing::Drawing(MdmaxScreen *_mx, Joystick * _joystick) : Game(_mx)
{
    joystick = _joystick;

}


#endif
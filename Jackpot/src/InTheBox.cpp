#include "Arduino.h"
#include "InTheBox.h"


int sign(int x){
    return (x > 0) - (x < 0);
}

InTheBox::InTheBox(MdmaxScreen *_mx, int buttonPin) : Game(_mx)
{
    _buttonPin = buttonPin;

}

void InTheBox::doRun()
{
    int minX = ((screen -> numberOfDevices * 8) - BOX_H) / 2; 
    int minY = (8 - BOX_V) / 2 ;
    int maxX = minX + BOX_H - 1;
    int maxY = minY + BOX_V - 1;

    if (digitalRead(_buttonPin) == LOW)
    {
         result(_x >= minX && _x <= maxX && _y >= minY && _y <= maxY);
    }

    if ((millis() - lastMove) > MOVE_PERIOD)
    {

        screen->mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
        screen->mx->clear();
        _showBox(minX, maxX, minY, maxY);
        _x = random(0, (8 * screen->numberOfDevices) - 1);
        _y = random(0, 7);
        screen->mx->setPoint(_y, _x, !screen->mx->getPoint(_y, _x));
        screen->mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
        lastMove = millis();
    }
}

void InTheBox::reset(){
    _x = 0;
    _y = 0;
    Game::reset();
    screen -> reset();
    
}

void InTheBox::_showBox(int minX, int maxX, int minY, int maxY){


    
    char sideColumn = 0;
    for (int i = minY - 1; i <= maxY + 1; i++){ sideColumn |= 1 << i;}
    char middleColumn = 1 << (minY - 1) | 1 << ( maxY + 1);

    for(int i = minX ; i <= maxX ; i++){
        screen -> mx -> setColumn(i, middleColumn);
    }
    screen -> mx -> setColumn(minX - 1, sideColumn);
    screen -> mx -> setColumn(maxX + 1, sideColumn);
        
    
    
}

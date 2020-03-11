#ifndef SPEED_CLICK_H
#define SPEED_CLICK_H

#include "Game.h"
#include <part/Button.h>

#include <part/StatePoper.h>



class SpeedClick : public Game{
public: 
    SpeedClick(MdmaxScreen *screen, Button * buttonScreen1,Button *buttonScreen2);
    char* title(){return "Course de click";}
    void reset() { 
        Game::reset();
        spB1->reset();
        spB2->reset();
        _count1=0;
        _count2=0;
    }
    void doRun();

private:
    StatePoper *spB1;
    StatePoper *spB2;
    Button *b1;
    Button *b2;
    int _count1 = 0;
    int _count2 = 0;
    void setScreen(int count, int colOffset);
};


SpeedClick::SpeedClick(MdmaxScreen *_mx, Button * buttonScreen1,Button *buttonScreen2) : Game(_mx)
{
    spB1 = new StatePoper(buttonScreen1);
    spB2 = new StatePoper(buttonScreen2);
}


void SpeedClick::doRun(){
  
    Game::doRun();
    screen -> mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

    if(spB1->hasNewState() && b1->clicked()){
        _count1++;
    }
    if(spB2->hasNewState() && b2->clicked()){
        _count2++;;
    }

    if(_count1 >= 64 || _count2 >= 64){
        if(_count1 < 64){ _count1 = 0;}
        if(_count2 < 64){ _count2 = 0;}
        result(true);
    }

    setScreen(_count1, 0);
    setScreen(0, 8);
    setScreen(_count2, 16);

    screen -> mx -> control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
        

};

void SpeedClick::setScreen(int count, int colOffset){
    for(int i = 0; i<64; i++){
        screen -> mx -> setPoint(i/8,colOffset+i%8,count>i);
    }
}
#endif
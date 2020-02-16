#ifndef Game_h
#define Game_h


#include <MdmaxScreen.h>

class Game
{
public:
    Game(MdmaxScreen *_screen){screen = _screen;}
    MdmaxScreen *screen;
    virtual void init(){
        reset();
    }
    virtual char* title(){return "GAME" ;};
    virtual void reset(){resultTime = 0 ; iter = 0; };
    void run();
    virtual void doRun(){
        iter +=1;
    };
    void result(bool _win){
        win = _win;
        resultTime = millis();
    }
protected:
    long resultTime = 0;
    boolean win;
    long iter = 0;

};

#endif
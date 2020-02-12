#ifndef Jackpot_h
#define Jackpot_h

#include <Game.h>

class Jackpot : public Game
{
public: 
    Jackpot(MdmaxScreen *screen, int buttonPin);
    char* title(){return "Jackpot";}
    void reset();
    void doRun();

private:
    unsigned long *_previousChangeTime;
    int *_graphicIndexes;
    int _buttonPin;
    bool _lastButtonState = 0;
    int _nbFixedGraphic = 0;
};

#endif
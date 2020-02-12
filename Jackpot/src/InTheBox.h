#ifndef InTheBox_h
#define InTheBox_h

#include <Game.h>

#define BOX_H 10
#define BOX_V 4
#define MOVE_PERIOD 250

class InTheBox : public Game
{
public:
    InTheBox(MdmaxScreen *screen, int buttonPin);
    char *title() { 
        return "Dans la boite"; 
        }
    void reset();
    void doRun();

private:
    int _buttonPin;
    void _showBox(int minX, int maxX, int minY, int maxY);
    int _x,_y;
    long lastMove = 0;
};

#endif
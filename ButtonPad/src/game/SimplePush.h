#ifndef SimplePush_h
#define SimplePush_h

#include "step/GameStep.h"
#include "../part/ButtonPad.h"


class SimplePush : GameStep, ButtonPad::EventListener
{

public:
    SimplePush(ButtonPad *_pad)
    {
        pad = _pad;
    }
    SimplePush()
    {
    }
    ButtonPad *pad;
    bool run()
    {
        if (millis() > (lastAction + period))
        {
            lastAction = millis();
            bool result = runAction(iter);
            iter++;
            return result;
        }
        return false;
    }
    void init()
    {
        for (int i = 0; i < 16; i++)
        {
            cellState[i] = random(0,3);
        }
        lastAction = 0;
        iter = 0;
        pad->eventListener = this;
    }

    bool runAction(long iter)
    {
       cellState[random(0,16)]++;
       updatePad();
    }

    void updatePad()
    {
        for (int i = 0; i < 16; i++)
        {
            pad->LED_outputs[i / 4][i % 4] = cellState[i]%3+1;
        }
    }

    void keyPressed(unsigned int col, unsigned int row, ButtonPad &pad)
    {
        int cellIndex = col * 4 + row;
        cellState[cellIndex]++;
        updatePad();
    }


private:
    unsigned long period = 500;
    unsigned long lastAction = 0;
    unsigned long iter = 0;
    unsigned int cellState[16];
    unsigned long cellStateSetIter[16];
};

#endif

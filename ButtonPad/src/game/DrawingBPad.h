#ifndef DRAWING_BPAD_H
#define DRAWING_BPAD_H

#include "step/GameStep.h"
#include "../part/ButtonPad.h"


class DrawingBPad : public GameStep, ButtonPad::EventListener
{

public:
    DrawingBPad(ButtonPad *_pad)
    {
        pad = _pad;
    }
    DrawingBPad()
    {
    }
    ButtonPad *pad;
    bool run()
    {

        return false;
    }
    void init()
    {
        for (int i = 0; i < 16; i++)
        {
            cellState[i] = 0;
        }
        pad->eventListener = this;
        updatePad();
    }


    void updatePad()
    {
        for (int i = 0; i < 16; i++)
        {
            pad->LED_outputs[i / 4][i % 4] = cellState[i]%4;
        }
    }

    void keyPressed(unsigned int col, unsigned int row, ButtonPad &pad)
    {
        int cellIndex = col * 4 + row;
        cellState[cellIndex]++;
        updatePad();
    }


private:

    unsigned int cellState[16];
    unsigned long cellStateSetIter[16];
};

#endif

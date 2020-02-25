#ifndef SpeedPush_h
#define SpeedPush_h

#include "step/GameStep.h"
#include "../part/ButtonPad.h"

#define RED_PERIOD (30)
#define GREEN_PERIOD (5)

class SpeedPush : GameStep, ButtonPad::EventListener
{

public:
    SpeedPush(ButtonPad *_pad)
    {
        pad = _pad;
    }
    SpeedPush()
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
            cellState[i] = 0;
            cellStateSetIter[i] = 0;
        }
        lastAction = 0;
        iter = 0;
        pad->eventListener = this;
    }

    bool runAction(long iter)
    {
        updateStates(iter);
        for(int i = 0; i<= (iter/10);i++){

        
        
        int r = randomFree();
        updateCell(r,GREEN);
    }
        updatePad();
        return false;
    }

    void updateStates(long iter)
    {
        for (int i = 0; i < 16; i++)
        {
            if (cellState[i] == GREEN && iter - cellStateSetIter[i] > GREEN_PERIOD)
            {
                updateCell(i, RED);
            }
            else if (cellState[i] == RED && iter - cellStateSetIter[i] > RED_PERIOD)
            {
                cellState[i] = 0;
                cellStateSetIter[i] = iter;
            }
        }
    }

    void keyPressed(unsigned int col, unsigned int row, ButtonPad &pad)
    {
        int cellIndex = col * 4 + row;
        if (cellState[cellIndex] == GREEN)
        {
            updateCell(cellIndex, 0);
        } 
        updatePad();
    }

    void updateCell(int index, int state)
    {
        cellState[index] = state;
        cellStateSetIter[index] = iter;
    }

    void updatePad()
    {
        for (int i = 0; i < 16; i++)
        {
            pad->LED_outputs[i / 4][i % 4] = (cellState[i] == 0) ? BLUE : cellState[i];
        }
    }

    int randomFree()
    {
        int r = random(16);
        for (int i = 0; i < 16; i++)
        {
            int candidate = (r + i) % 16;
            if (cellState[candidate] == 0)
            {
                return candidate;
            }
        }
        return 0;
    }

private:
    unsigned long period = 500;
    unsigned long lastAction = 0;
    unsigned long iter = 0;
    unsigned int cellState[16];
    unsigned long cellStateSetIter[16];
};

#endif
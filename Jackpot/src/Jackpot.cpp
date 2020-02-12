#include "Arduino.h"
#include "Jackpot.h"

Jackpot::Jackpot(MdmaxScreen *_mx, int buttonPin) : Game(_mx)
{
    _previousChangeTime = new unsigned long[screen->numberOfDevices];
    _graphicIndexes = new int[screen->numberOfDevices];
    _buttonPin = buttonPin;

}

void Jackpot::doRun()
{
    int buttonState = digitalRead(_buttonPin);
    if (_lastButtonState != buttonState)
    {
        if (buttonState == LOW)
        {
            _nbFixedGraphic++;
        }
        _lastButtonState = buttonState;
    }

    if (_nbFixedGraphic >= screen->numberOfDevices)
    {

        int firstGraphicIndex = _graphicIndexes[0];
        boolean _win = true;
        for (int i = 1; i < screen->numberOfDevices; i++)
        {
            if (firstGraphicIndex != _graphicIndexes[i])
            {
                _win = false;
            }
        }
        result(_win);
    }
    else
    {
        for (int i = _nbFixedGraphic; i < screen->numberOfDevices; i++)
        {
            if ((millis() - _previousChangeTime[i]) > (300UL + (i * 25)))
            {
                _previousChangeTime[i] = millis();
                _graphicIndexes[i] = (_graphicIndexes[i] + 1) % NUM_GRAPHICS;
            }
        }

        for (int i = 0; i < screen->numberOfDevices; i++)
        {
            screen->printGraphic(graphics[_graphicIndexes[i]], i * 8);
        }
    }
}

void Jackpot::reset(){
    Game::reset();
    _nbFixedGraphic = 0;
    

    screen -> reset(); 
    for (int i = 0; i < screen->numberOfDevices; i++)
    {
        _graphicIndexes[i] = i;
        _previousChangeTime[i] = 0;
    }
}

#include "Game.h"

void Game::run()
{
    if (resultTime != 0)
    {
        if (win)
        {
            screen->blink();
        }
        if ((millis() - resultTime) > ((win) ? 2000 : 1000))
        {
            reset();
        }
    }
    else
    {
        doRun();
    }
}
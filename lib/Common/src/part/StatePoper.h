#ifndef STATEPOPER_H
#define STATEPOPER_H

#include "StateCounter.h"

class StatePoper
{
private:
    StateCounter *obj;
    unsigned int lastPopedStateCount = 0;
public:
    StatePoper(StateCounter * _obj){
        obj = _obj;
    }

    bool hasNewState(){
        bool b = obj -> stateChangeCount() > lastPopedStateCount;
        lastPopedStateCount = obj->stateChangeCount();
        return b;
    }
};



#endif
#ifndef STATECOUNTER_H
#define STATECOUNTER_H

class StateCounter
{
private:
    unsigned int _stateChangeCount = 0;
public:
    unsigned int stateChangeCount(){
        return _stateChangeCount;
    };
    void updateState(){
        _stateChangeCount++;
    }
    
};



#endif
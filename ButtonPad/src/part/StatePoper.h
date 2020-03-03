#ifndef STATEPOPER
#define STATEPOPER

class StatePoper
{
private:
    unsigned int stateChangeCount = 0;
    unsigned int lastPopedStateCount = 0;
public:
    void updateState(){
        stateChangeCount++;
    }
    bool hasNewState(){
        bool b = stateChangeCount > lastPopedStateCount;
        lastPopedStateCount = stateChangeCount;
        return b;
    }
};



#endif
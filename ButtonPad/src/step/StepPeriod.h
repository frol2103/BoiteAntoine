#ifndef StepPeriod_h
#define StepPeriod_h

#include "Step.h"

void doNotring(){};
bool doNotringRetTrue(int i){return true;};

class StepPeriod : public Step
{

public:
    void init()
    {
        Step::init();
        iter = 0;
        lastAction = 0;
        customInit();
    }
    bool run()
    {
        customLoop();
        if (millis() > (lastAction + period)){
            lastAction = millis();
            bool result = customPeriodicAction(iter);
            iter++;
            return result;
        }
        return false;
    }
    StepPeriod() : Step() {}
    void (*customInit)() = doNotring;
    void (*customLoop)() = doNotring;
    bool (*customPeriodicAction)(int iter) = doNotringRetTrue;
    unsigned long period = 50;

private:
    long lastAction = 0;
    long iter = 0;
};

#endif
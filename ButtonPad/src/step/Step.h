#ifndef Step_h
#define Step_h

#include <Arduino.h>

class Step
{
public:
    typedef Step* Step_p;
    virtual bool run() {return true;};
    virtual void init(){stepStart = millis();};
    long stepStart;
};

#endif
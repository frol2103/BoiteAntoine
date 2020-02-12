#ifndef MultiStep_h
#define MultiStep_h

#include "Step.h"

#include "StepPeriod.h"

class MultiStep : public Step
{

public:
    int currentStep = 0;
    bool run()
    {
        if (currentStep < 2)
        {
            bool result = steps[currentStep]->run();
            if (result)
            {
                currentStep++;
            }
        }

        return false;
    }
    Step_p *steps = {};
};

#endif
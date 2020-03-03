#ifndef TRISELECT_H
#define TRISELECT_H

#include "StatePoper.h"

#define BUTTON_1_PIN (28)
#define BUTTON_2_PIN (29)


class TriSelect : public StatePoper
{
private:
    /* dat */
    
public:
    int state = -1;
    TriSelect(/* args */){};
    ~TriSelect(){};
    
    void run(){
        byte newState = readState();
        if(newState != state){
            state = newState;
            StatePoper::updateState();
            Serial.print("TriSelect state : ");
            Serial.println(state);
        }
    }
    int readState(){
        if(digitalRead(BUTTON_1_PIN) == HIGH){
            return 1;
        } else if( digitalRead(BUTTON_2_PIN) == HIGH){
            return 2;
        } else return 0;
    }
};


#endif